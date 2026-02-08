#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
int main()
{
	int sockfd;
	char data[128];
	struct sockaddr_in server;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return 0;
	}
	else
		printf("socket create successfully....!\n");
	
	server.sin_family = AF_INET;
	server.sin_port   = htons(8008);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(sockfd,(struct sockaddr*)&server,sizeof(server))==0)
		printf("connection establishment is success....!\n");
	else
	{
		perror("connect");
		return 0;
	}
	while(1)
	{
		printf("Enter the data:");
		scanf(" %[^\n]",data);
		write(sockfd,data,strlen(data)+1);
	}
}
