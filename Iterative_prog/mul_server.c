#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
int main(int argc,char**argv)
{
	int sockfd,newsfd;
	char readbuf[128],wbuf[128];
	struct sockaddr_in server,client;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return 0;
	}
	printf("socket created successfully....!\n");
	server.sin_family = AF_INET;
	server.sin_port   = htons(atoi(argv[1]));
	server.sin_addr.s_addr = inet_addr("0.0.0.0");

	if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))==0)
	{
		printf("Binding address is successfull....!\n");
	}
	else
	{
		perror("bind");
		return 0;
	}

	if(listen(sockfd,1)==0)
	{
		printf("server listening>>>>>\n");
	}
	else
	{
		perror("listen");
		return 0;
	}
	int len=sizeof(client);
	while(1)
	{
		newsfd=accept(sockfd,(struct sockaddr*)&client,&len);
		if(newsfd<0)
		{
			perror("accept");
			return 0;
		}
		else
		{
			printf("client-%d connected....!\n",(newsfd-3));
		}
		if(fork()==0)
		{
			while(1)
			{
				bzero(readbuf,128);
				if(read(newsfd,readbuf,128)==0)
				{
					printf("client-%d terminated...!\n",(newsfd-3));
					break;
				}
				printf("received:%s\n",readbuf);
				printf("your turn\n");
				scanf("%s",wbuf);
				write(newsfd,wbuf,strlen(wbuf)+1);
			}
		}
	}
}
