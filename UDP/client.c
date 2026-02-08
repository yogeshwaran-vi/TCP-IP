#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(int argc,char**argv)
{
	if(argc!=2)
	{
		printf("usage:./cln <port address>\n");
		return 0;
	}
	int sockfd;
	char w_buf[128];
	struct sockaddr_in s;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return 0;
	}
	printf("socket created successfully...\n");
	s.sin_family    = AF_INET;
	s.sin_port      = htons(atoi(argv[1]));
	s.sin_addr.s_addr = inet_addr("127.0.0.1");
	while(1)
	{
		printf("Enter The Data...\n");
		scanf(" %[^\n]",w_buf);
		
		sendto(sockfd,w_buf,strlen(w_buf)+1,0,(struct sockaddr*)&s,sizeof(s));
	}
}
