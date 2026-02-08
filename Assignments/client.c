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
	int sockfd,ch,val;
	char wbuf[128];
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
	s.sin_addr.s_addr=inet_addr("127.0.0.1");

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
	}
//	read(sockfd,&ch,sizeof(ch));
//	read(sockfd,&val,sizeof(val));

//	printf("no.of.char:%d\n",ch);
//	printf("no.of.int :%d\n",val);
//	close(sockfd);
}
