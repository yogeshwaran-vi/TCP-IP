#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(int argc,char**argv)
{
	int sockfd;
	char wbuf[128],rcv[128];
	struct sockaddr_in s;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return 0;
	}
	printf("socket created...\n");
	
	s.sin_family=AF_INET;
	s.sin_port  =htons(atoi(argv[1]));
	s.sin_addr.s_addr=inet_addr("192.168.4.120");
//	inet_pton(AF_INET,"192.168.4.120",s.sin_addr.s_addr);

	if(connect(sockfd,(struct sockaddr*)&s,sizeof(s))==0)
	{
		printf("connection established...\n");
	}
	else
	{
		perror("connect");
		return 0;
	}
	while(1){
	printf("Enter the data:");
	scanf(" %[^\n]",wbuf);
	write(sockfd,wbuf,strlen(wbuf)+1);
	bzero(rcv,128);
	read(sockfd,rcv,sizeof(rcv));
	printf("result: %s\n",rcv);
	}
}
