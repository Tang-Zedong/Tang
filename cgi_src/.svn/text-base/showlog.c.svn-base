#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char cmd[512];
	char buf[512];
	int i=0;
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"dmesg 2>/dev/null");
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
