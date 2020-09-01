#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int server_socket,client_socket,flag=1;
    char buffer[100];
    struct sockaddr_in server, other;
    socklen_t addr_size;
    memset(&server,0,sizeof(server));
    memset(&other,0,sizeof(other));

    server_socket=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(9009);
    server.sin_addr.s_addr=INADDR_ANY;

    if(bind(server_socket,(struct sockaddr*)&server,sizeof(server))==-1)
    {
        printf("connection error\n");
        exit(0);
    }
    listen(server_socket,5);
    addr_size=sizeof(other);
    client_socket=accept(server_socket,(struct sockaddr*)&other,&addr_size);

    FILE *fp;
    fp=fopen("test1.txt","w");

    while(flag)
    {
        recv(client_socket,&flag,sizeof(flag),0);
        read(client_socket,buffer,sizeof(buffer));
        fprintf(fp,"%s",buffer);
    }

    printf("file recieved successfully\n");
    printf("data saved in test1.txt\n");
    fclose(fp);
    close(server_socket);
    return 0;
}