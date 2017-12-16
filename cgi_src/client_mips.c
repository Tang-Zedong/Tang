#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

#define SERVER_PORT 20000
#define BUFFER_SIZE 1024

int main(int argc,char **argv)
{
	int servfd,clifd,length=0;
	unsigned long i=0;
	struct sockaddr_in servaddr,cliaddr;
	unsigned char sendbuf[BUFFER_SIZE],startbuf[BUFFER_SIZE],stopbuf[BUFFER_SIZE],recvbuf[32];
	socklen_t socklen=sizeof(servaddr);
	if(argc!=2)
	{
		printf("This tool has 2 parameters!\n");
		exit(1);
	}
	memset(sendbuf,0,BUFFER_SIZE);	
	memset(sendbuf,1,BUFFER_SIZE);
	memset(stopbuf,2,BUFFER_SIZE);
	if((clifd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("create socket error!\n");
		exit(1);
	}
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERVER_PORT);
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	if(connect(clifd,(struct sockaddr*)&servaddr,socklen)<0)
	{
		printf("Can`t connect to %s!\n",argv[1]);
		exit(1);
	}
	send(clifd,startbuf,BUFFER_SIZE,0);
	for(i=0;i<5000;i++)
	send(clifd,sendbuf,BUFFER_SIZE,0);
	send(clifd,stopbuf,BUFFER_SIZE,0);
	memset(recvbuf,0,sizeof(recvbuf));
	recv(clifd,recvbuf,sizeof(recvbuf),0);
	close(clifd);
	printf("%s\n",recvbuf);		
	return 0;
}
