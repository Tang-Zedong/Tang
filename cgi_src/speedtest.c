#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char cmd[64];
	char buf[512];
	FILE *fp=NULL;
	char *pquerystring=NULL;
	char *pstart=NULL;
	char remote_ip[24];
	pquerystring=getenv("QUERY_STRING");
	printf("Content-Type: text/html\r\n\r\n");
	pstart=strstr(pquerystring,"speedip=");
	while(*pstart!='=')
		pstart++;
	pstart++;
	memset(remote_ip,0,sizeof(remote_ip));
	strcpy(remote_ip,pstart);
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"client_mips %s",remote_ip);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		printf("%s",buf);
	}	
	pclose(fp);
	return 0;
}
