#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int server_socket;
    char buf[20];
    struct sockaddr_in server,other;
    socklen_t add;

    server_socket=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(9009);
    server.sin_addr.s_addr=INADDR_ANY;

    bind(server_socket,(struct sockaddr*) &server,sizeof(server));
    add=sizeof(other);

    recvfrom(server_socket,buf,sizeof(buf),0,(struct sockaddr*) &other,&add);
    printf("message \"%s\" recieved\n",buf);
    close(server_socket);
    return 0;
}