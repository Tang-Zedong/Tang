#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<sys/time.h>
#include<string.h>

#define SERVER_PORT 20000

#define BUFFER_SIZE 1024

int main(int argc,char **argv)
{
	int servfd,clifd;
	struct sockaddr_in servaddr,cliaddr;
	unsigned char recvbuf[BUFFER_SIZE];
	unsigned char ucspeed[32];
	int ret=-1;
	struct timeval tvstart,tvstop;
	unsigned long ultotalsize=0,ultime=0;
	char breuseaddr=1;
	socklen_t socklen=sizeof(cliaddr);
	double dspeed=0.0;

	if((servfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("create socket error!\n");
		exit(1);
	}
	setsockopt(servfd,SOL_SOCKET,SO_REUSEADDR,(const char *)&breuseaddr,sizeof(char));
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERVER_PORT);
	servaddr.sin_addr.s_addr=htons(INADDR_ANY);
	if(bind(servfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		printf("bind to port %d failure!\n",SERVER_PORT);
		exit(1);
	}
	if(listen(servfd,100)<0)
	{
		printf("listen fail!\n");
		exit(1);
	}
	while(1)
	{
		socklen=sizeof(cliaddr);
		clifd=accept(servfd,(struct sockaddr*)&cliaddr,&socklen);
		while(1)
		{
			ret=recv(clifd,recvbuf,BUFFER_SIZE,0);
			if(ret>0)
			{
				if(recvbuf[0]==0)
				{
					gettimeofday(&tvstart,NULL);
					ultotalsize=0;
					continue;
				}
				else if(recvbuf[0]==1)
				{
				//	ultotalsize+=1024;
					ultotalsize+=ret;
					continue;
				}
				else
				{
					gettimeofday(&tvstop,NULL);
					ultime=(tvstop.tv_sec-tvstart.tv_sec)*1000+(tvstop.tv_usec-tvstart.tv_usec)/1000;	
					dspeed=((double)((ultotalsize/ultime)*1000))/((double)(1024*1024));
					//printf("speed=%luMB/s\n",ulspeed);
					sprintf(ucspeed,"%fMB/s",dspeed);
					send(clifd,ucspeed,strlen(ucspeed),0);
					break;
				}
			}
				if(ret==0)
					break;
		}
		close(clifd);
	}
	close(servfd);		
	return 0;
}

