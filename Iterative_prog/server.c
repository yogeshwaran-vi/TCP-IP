#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
int main()
{
/*	if(argc!=2)
	{
		printf("usage:./srv <port_address>\n");
		return 0;
	}*/
	int sockfd,newsfd;
	char readbuf[128];
	struct sockaddr_in server,client;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return 0;
	}
	else
		printf("Socket created successfully....!\n");
	
	server.sin_family = AF_INET;
	server.sin_port	  = htons(8080);
	server.sin_addr.s_addr=inet_addr("0.0.0.0");
	
	if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))==0)
		printf("Bind address is success....!\n");
	else
	{
		perror("Bind");
		return 0;
	}

	if(listen(sockfd,1)==0)
		printf("server listening<<<<<\n");
	else
	{
		perror("listen");
		return 0;
	}
	int len = sizeof(client);
	newsfd  = accept(sockfd,(struct sockaddr*)&client,&len);

	if(newsfd<0)
	{
		perror("accept");
		return 0;
	}

	printf("New client connected....!\n");
	while(1){
	bzero(readbuf,128);
	read(newsfd,readbuf,128);
	printf("Received: %s\n",readbuf);
	}
}
