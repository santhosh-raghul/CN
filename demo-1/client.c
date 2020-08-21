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
    char buf[20]="hello server!";
    struct sockaddr_in client;

    client_socket=socket(AF_INET,SOCK_DGRAM,0);
    client.sin_family=AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr=INADDR_ANY;

    sendto(client_socket,buf,sizeof(buf),0,(struct sockaddr*) &client,sizeof(client));
    printf("message \"%s\" sent\n",buf);
    close(client_socket);
    return 0;
}