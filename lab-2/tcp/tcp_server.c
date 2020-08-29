#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int server_socket,client_socket,flag;
    char a[20],op,b[20],res[20],options[41]="enter +, -, *, or /\nor enter x to exit: ";
    float x,y,z;
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
    printf("waiting for client...\n");
    add=sizeof(other);
    client_socket=accept(server_socket,(struct sockaddr *)&other,&add);

    if(client_socket==-1)
    {
        printf("could not connect to client");
        return 0;
    }
    else
    {
        printf("connected to client\n\n");
    }
    

    while(1)
    {
        flag=1;
        while(flag)
        {
            send(client_socket,options,sizeof(options),0);
            recv(client_socket,&op,sizeof(op),0);
            flag=op!='+'&&op!='-'&&op!='*'&&op!='/'&&op!='x';
            if(flag) printf("invalid option '%c' recieved, waiting for new input\n",op);
            send(client_socket,&flag,sizeof(flag),0);
        }
        if(op=='x')
        {
            printf("recieved 'x' disconnecting...\n");
            break;
        }
        printf("operation recieved\n");
        recv(client_socket,a,sizeof(a),0);
        printf("number recieved\n");
        recv(client_socket,b,sizeof(b),0);
        printf("number recieved\n");
        
        x=atof(a);
        y=atof(b);
        switch(op)
        {
            case '+':
                z=x+y;
                break;
            case '-':
                z=x-y;
                break;
            case '*':
                z=x*y;
                break;
            case '/':
                z=x/y;
                break;
        }

        snprintf(res, sizeof res, "%f", z);
        send(client_socket,res,sizeof(res),0);
        printf("result sent\n\n");     
    }

    close(server_socket);
    return 0;
}