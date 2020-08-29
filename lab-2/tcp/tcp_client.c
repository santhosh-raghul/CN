#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int client_socket,flag;
    char a[20],op,b[20],res[20],options[41];
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
    else
    {
        printf("connected to server\n\n");
    }
    

    while(1)
    {
        flag=1;
        while(flag)
        {
            recv(client_socket,options,sizeof(options),0);
            printf("%s",options);
            scanf(" %c",&op);
            send(client_socket,&op,sizeof(op),0);
            recv(client_socket,&flag,sizeof(flag),0);
        }
        if(op=='x')
        {
            printf("\ninput was 'x' disconnecting...\n");
            break;
        }
        printf("enter a number: ");
        scanf("%s",a);
        send(client_socket,a,sizeof(a),0);

        printf("enter a number: ");
        scanf("%s",b);
        send(client_socket,b,sizeof(b),0);

        recv(client_socket,res,sizeof(res),0);
        printf("result from server: %s\n\n",res);
    }
    
    close(client_socket);
    return 0;
}