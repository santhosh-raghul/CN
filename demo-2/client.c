#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int client_socket;
    char buffer[20];
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));

    client_socket=socket(AF_INET,SOCK_STREAM,0);
    client.sin_family=AF_INET;
    client.sin_port=htons(9000);
    client.sin_addr.s_addr=INADDR_ANY;

    if(connect(client_socket,(struct sockaddr *)&client,sizeof(client))==-1)
    {
        printf("connection failed!\n");
        return 0;
    }

    recv(client_socket,buffer,sizeof(buffer),0);
    printf("message from server: %s\n",buffer);

    close(client_socket);
    return 0;
}