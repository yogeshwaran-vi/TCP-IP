#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
int newsfd;
void*thread(void*);
int main(int argc,char**argv)
{
	int sockfd;
	struct sockaddr_in s,c;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return 0;
	}
	printf("socket created...\n");
	s.sin_family=AF_INET;
	s.sin_port=htons(atoi(argv[1]));
	s.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr*)&s,sizeof(s))<0)
	{
		perror("bind");
		return 0;
	}
	if(listen(sockfd,5)<0)
	{
		perror("listen");
		return 0;
	}
	printf("server listening on host\n");
	socklen_t len=sizeof(c);
	while(1)
	{
		newsfd=accept(sockfd,(struct sockaddr*)&c,&len);
		if(newsfd>=0)
		{
			printf("connection success\n");
		}
		else
		{
			perror("accept");
			return 0;
		}
		int *p=malloc(sizeof(int));
		*p=newsfd;
		pthread_t t1;
		pthread_create(&t1,0,thread,p);
		pthread_detach(t1);
	}
}
void*thread(void*p)
{
	int fd = *(int*)p;
	free(p);

	char rbuf[128],wbuf[128];
	int n;
	while(1)
	{
		n = read(fd,rbuf,sizeof(rbuf)-1);
		if(n<=0)
		{
			printf("client disconnect\n");
			break;
		}
		rbuf[n]='\0';
		printf("received:%s\n",rbuf);
	}

	return 0;
}
