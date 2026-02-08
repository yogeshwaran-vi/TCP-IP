#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(int argc,char*argv[])
{
	int sockfd,newsfd;
	char rbuf[128];
	int ch=0,val=0;
	struct sockaddr_in s,c;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return 0;
	}
	printf("socket created...\n");

	s.sin_family=AF_INET;
	s.sin_port  =htons(atoi(argv[1]));
	s.sin_addr.s_addr=inet_addr("0.0.0.0");

	if(bind(sockfd,(struct sockaddr*)&s,sizeof(s))==0)
	{
		printf("bind addr success...\n");
	}
	else
	{
		perror("bind");
		return 0;
	}

	if(listen(sockfd,1)==0)
	{
		printf("server listening...\n");
	}
	else
	{
		perror("listen");
		return 0;
	}
	int len=sizeof(c);
	newsfd=accept(sockfd,(struct sockaddr*)&c,&len);
	if(newsfd<0)
	{
		perror("accept");
		return 0;
	}
	else
	{
		printf("New client connected...\n");
	}
	bzero(rbuf,128);	
	if(read(newsfd,rbuf,128)==0)
	{
		printf("client terminated...\n");
	}
	else
	{
		for(int i=0;rbuf[i]!='\0';i++)
		{
			if((rbuf[i]>='A' && rbuf[i]<='Z')||(rbuf[i]>='a' && rbuf[i]<='z'))
				++ch;
			else if(rbuf[i]>='0' && rbuf[i]<='9')
				++val;
		}
		write(newsfd,&ch,sizeof(ch));	
		write(newsfd,&val,sizeof(val));
		printf("received: %s\n",rbuf);
	}
	close(newsfd);
	close(sockfd);
}
