#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
volatile int flag=0;
int main(int argc,char*argv[])
{
	int sockfd,newsfd,val[2];
	char rbuf[128],op;
	char wbuf[128];
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
	while(1){
	bzero(rbuf,128);
	bzero(val,8);
	read(newsfd,rbuf,128);
//	printf("%s\n",rbuf);
	int k=0;
	for(int i=0;rbuf[i]!='\0';i++)
	{

		if(rbuf[i]>='0' && rbuf[i]<='9')
		{
			val[k] = val[k] * 10 + (rbuf[i]-'0');
		}
		else
		{
			op=rbuf[i];
			k++;
			flag=1;
		}
	}
//	printf("%d %c %d\n",val[0],op,val[1]);
	int result=0;
	if(op=='+')
	{
		result=val[0] + val[1];
	}
	if(op=='-')
	{
		result=val[0] - val[1];
	}
	if(op=='*')
	{
		result=val[0] * val[1];
	}
	if(op=='/')
	{
		if(val[1]==0)
		{
			printf("floating pointing exception\n");
			printf("invalid calculation\n");
		}
		else
			result=val[0] / val[1];
	}
	if(op=='%')
	{
		result=val[0] % val[1];
	}
	write(newsfd,&result,sizeof(result));
	}
}
