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
		printf("usage:./srv <port address>\n");
		return 0;
	}
	int sockfd,newsfd;
	char read_buf[128];
	struct sockaddr_in s,c;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return 0;
	}
	printf("socket created successfully...\n");
	s.sin_family    = AF_INET;
	s.sin_port      = htons(atoi(argv[1]));
	s.sin_addr.s_addr = INADDR_ANY;	
	if(bind(sockfd,(struct sockaddr*)&s,sizeof(s))==0)
	{
		printf("binding successfully..\n");
	}
	else
	{
		perror("bind");
		return 0;
	}

	socklen_t clen = sizeof(c);
	while(1){
	int n=recvfrom(sockfd,read_buf,sizeof(read_buf),0,(struct sockaddr*)&c,&clen);
	printf("recvfrom:%s\n",read_buf);
	}
}
