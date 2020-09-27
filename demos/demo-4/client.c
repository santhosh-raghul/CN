#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int client_socket,flag=1;
    char buffer[100];
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));

    client_socket=socket(AF_INET,SOCK_STREAM,0);
    client.sin_family=AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr=INADDR_ANY;

    if(connect(client_socket,(struct sockaddr*)&client,sizeof(client))==-1)
    {
        printf("connection error\n");
        exit(0);
    }

    FILE *fp;
    fp=fopen("test.txt","r");
    if(fp==NULL)
    {
        printf("file doesnt exist\n");
        exit(1);
    }

    while(1)
    {
    fgets(buffer,sizeof(buffer),fp);
    if(feof(fp))
        flag=0;
    send(client_socket,&flag,sizeof(flag),0);
    write(client_socket,buffer,sizeof(buffer));
    }

    printf("file sent successfully\n");
    fclose(fp);
    close(client_socket);
    return 0;
}