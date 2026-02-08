#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(int argc,char**argv)
{
	int sockfd,newsfd;
	fd_set rdset,testset;
	printf("%ld\n",sizeof(rdset));
	char rbuf[128];
	struct sockaddr_in s,c;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return 0;
	}
	printf("socket create successfully...\n");
	s.sin_family=AF_INET;
	s.sin_port=htons(atoi(argv[1]));
	s.sin_addr.s_addr=inet_addr("0.0.0.0");

	if(bind(sockfd,(struct sockaddr*)&s,sizeof(s))==0)
	{
		printf("bind success...\n");
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
	socklen_t len=sizeof(c);
	FD_ZERO(&rdset);

	FD_SET(sockfd,&rdset);
	int i;
	while(1)
	{
		testset = rdset;
		select(100,&testset,0,0,0);

		for(i=3;i<100;i++)
		{
			if(FD_ISSET(i,&testset))
			break;
		}
		if(sockfd==i)
		{
			newsfd=accept(sockfd,(struct sockaddr*)&c,&len);
			printf("new client-%d connected...\n",newsfd-sockfd);
			FD_SET(newsfd,&rdset);
		}
		else
		{
			bzero(rbuf,128);
			if(read(i,rbuf,sizeof(rbuf))==0)
			{
				printf("client-%d terminated...",i-sockfd);
			}
			printf("Receive:%s\n",rbuf);
		}
	}
}
