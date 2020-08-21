#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int client_socket,n;
    char buf[100];
    struct sockaddr_in client;

    client_socket=socket(AF_INET,SOCK_DGRAM,0);
    client.sin_family=AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr=INADDR_ANY;

    while(1)
    {
        printf("enter ur msg: ");
        gets(buf);
        sendto(client_socket,buf,sizeof(buf),0,(struct sockaddr*) &client,sizeof(client));
        printf("sent\n\n");
        if(strcmp(buf,"bye")==0) break;

        recvfrom(client_socket,buf,sizeof(buf),0, (struct sockaddr *) &client, &n); 
        printf("recieved: %s\n\n",buf);
        if(strcmp(buf,"bye")==0) break;
    }

    printf("disconnecting...\n");
    close(client_socket);
    return 0;
}
