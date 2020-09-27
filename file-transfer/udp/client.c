#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

int main()
{
    int client_socket,flag=1,c,i=0;
    char buffer[100],send_file[30],save_as[30];
    struct sockaddr_in client;

    client_socket=socket(AF_INET,SOCK_DGRAM,0);
    client.sin_family=AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr=INADDR_ANY;
    
    printf("enter file name to be sent: ");
    scanf("%s",send_file);

    FILE *fp;
    fp=fopen(send_file,"rb");
    if(fp==NULL)
    {
        printf("file doesnt exist\n");
        flag=0;
        sendto(client_socket,&flag,sizeof(flag),0,(struct sockaddr*) &client,sizeof(client));

        exit(1);
    }

    printf("enter new file name to save the sent file as: ");
    scanf("%s",save_as);

    sendto(client_socket,&flag,sizeof(flag),0,(struct sockaddr*) &client,sizeof(client));
    sendto(client_socket,save_as,sizeof(save_as),0,(struct sockaddr*) &client,sizeof(client));


	clock_t start,end;
	double cpu_time_used;
	start=clock();
	while((c=fgetc(fp))!=EOF)
    {
    	i++;
		// printf("%d\n",c);
        sleep(0);
        // write(client_socket,&c,sizeof(c));
        sendto(client_socket,&c,sizeof(c),0,(struct sockaddr*) &client,sizeof(client));
	}
	c=EOF;
    sendto(client_socket,&c,sizeof(c),0,(struct sockaddr*) &client,sizeof(client));
    end=clock();

    flag=0;
    sendto(client_socket,&flag,sizeof(flag),0,(struct sockaddr*) &client,sizeof(client));

    printf("file sent successfully\n");
    cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC*1000;
	printf("total time taken for file transfer is %lfms\n",cpu_time_used);
	printf("total time taken for one transfer (latency) is %lfms\n",cpu_time_used/i);
    fclose(fp);
    close(client_socket);
    return 0;
}
