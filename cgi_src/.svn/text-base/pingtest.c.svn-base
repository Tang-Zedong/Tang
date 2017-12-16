#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char *pquerystring=NULL;
	char *pstart=NULL;
	char remote_ip[24];
	char cmd[64];
	int ret=0;
	pquerystring=getenv("QUERY_STRING");
	printf("Content-Type: text/html\r\n\r\n");
	pstart=strstr(pquerystring,"pingip=");
	while(*pstart!='=')
		pstart++;
	pstart++;
	memset(remote_ip,0,sizeof(remote_ip));
	strcpy(remote_ip,pstart);
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"ping -c 1 %s>/dev/null 2>&1",remote_ip);
	ret=system(cmd);
	if(ret==0)
		printf("Alive!");
	else
		printf("Not alive!");
	return 0;
}
