#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int server_socket,flag;
    char a[20],op,b[20],res[20],options[41]="enter +, -, *, or /\nor enter x to exit: ";
    float x,y,z;
    char buf[100];
    struct sockaddr_in server,other;
    socklen_t add;

    server_socket=socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_port=htons(9009);
    server.sin_addr.s_addr=INADDR_ANY;

    printf("waiting for client...\n\n");
    bind(server_socket,(struct sockaddr*) &server,sizeof(server));
    add=sizeof(other);

    recvfrom(server_socket,&op,sizeof(op),0,(struct sockaddr*) &other,&add);

    while(1)
    {
        flag=1;
        while(flag)
        {
            sendto(server_socket,options,sizeof(options),0,(const struct sockaddr *) &other,add); 
            recvfrom(server_socket,&op,sizeof(op),0,(struct sockaddr*) &other,&add);
            flag=op!='+'&&op!='-'&&op!='*'&&op!='/'&&op!='x';
            if(flag) printf("invalid option '%c' recieved,waiting for new input\n",op);
            sendto(server_socket,&flag,sizeof(flag),0,(const struct sockaddr *) &other,add); 
        }
        if(op=='x')
        {
            printf("recieved 'x' disconnecting...\n");
            break;
        }
        printf("operation recieved\n");
        recvfrom(server_socket,a,sizeof(a),0,(struct sockaddr*) &other,&add);
        printf("number recieved\n");
        recvfrom(server_socket,b,sizeof(b),0,(struct sockaddr*) &other,&add);
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

        snprintf(res,sizeof res,"%f",z);
        sendto(server_socket,res,sizeof(res),0,(const struct sockaddr *) &other,add); 
        printf("result sent\n\n");     
    }

    close(server_socket);
    return 0;
}
