#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int server_socket,client_socket;
    char buffer[20]="hello client!";
    struct sockaddr_in server,other;
    socklen_t add;
    memset(&server,0,sizeof(server));
    memset(&other,0,sizeof(other));

    server_socket=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(9000);
    server.sin_addr.s_addr=INADDR_ANY;

    bind(server_socket,(struct sockaddr *)&server,sizeof(server));
    listen(server_socket,10);
    add=sizeof(other);
    client_socket=accept(server_socket,(struct sockaddr *)&other,&add);

    send(client_socket,buffer,sizeof(buffer),0);
    printf("message sent\n");
    
    close(server_socket);
    return 0;
}