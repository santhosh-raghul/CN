#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int client_socket,n,flag;
    char a[20],op,b[20],res[20],options[41];
    struct sockaddr_in client;

    client_socket=socket(AF_INET,SOCK_DGRAM,0);
    client.sin_family=AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr=INADDR_ANY;

    sendto(client_socket,&op,sizeof(op),0,(struct sockaddr*) &client,sizeof(client));

    while(1)
    {
        flag=1;
        while(flag)
        {
            recvfrom(client_socket,options,sizeof(options),0, (struct sockaddr *) &client, &n); 
            printf("%s",options);
            scanf(" %c",&op);
            sendto(client_socket,&op,sizeof(op),0,(struct sockaddr*) &client,sizeof(client));
            recvfrom(client_socket,&flag,sizeof(flag),0, (struct sockaddr *) &client, &n); 
        }
        if(op=='x')
        {
            printf("\ninput was 'x' disconnecting...\n");
            break;
        }
        printf("enter a number: ");
        scanf("%s",a);
        sendto(client_socket,a,sizeof(a),0,(struct sockaddr*) &client,sizeof(client));

        printf("enter a number: ");
        scanf("%s",b);
        sendto(client_socket,b,sizeof(b),0,(struct sockaddr*) &client,sizeof(client));

        recvfrom(client_socket,res,sizeof(res),0, (struct sockaddr *) &client, &n); 
        printf("result from server: %s\n\n",res);
    
    }

    close(client_socket);
    return 0;
}
