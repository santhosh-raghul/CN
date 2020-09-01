#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int server_socket,flag=1,c;
    char buffer[100],filename[30];
    struct sockaddr_in server, other;
    socklen_t addr_size;

    server_socket=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(9009);
    server.sin_addr.s_addr=INADDR_ANY;

    if(bind(server_socket,(struct sockaddr*)&server,sizeof(server))==-1)
    {
        printf("connection error\n");
        exit(0);
    }
    addr_size=sizeof(other);

    recvfrom(server_socket,&flag,sizeof(flag),0,(struct sockaddr*) &other,&addr_size);
    if(flag==0)
    {
        printf("file transfer failed\n");
        exit(1);
    }
    else
        printf("starting file transfer\n");

    recvfrom(server_socket,filename,sizeof(filename),0,(struct sockaddr*) &other,&addr_size);
    
    FILE *fp;
    fp=fopen(filename,"wb");

    // read(server_socket,&c,sizeof(c));
    recvfrom(server_socket,&c,sizeof(c),0,(struct sockaddr*) &other,&addr_size);
    while(c!=EOF)
    {
		fputc(c,fp);
		// printf("%d\n",c);
        // read(server_socket,&c,sizeof(c));
        recvfrom(server_socket,&c,sizeof(c),0,(struct sockaddr*) &other,&addr_size);
    }

    printf("file recieved successfully\n");
    printf("recieved file saved as %s\n",filename);
    fclose(fp);
    close(server_socket);
    return 0;
}