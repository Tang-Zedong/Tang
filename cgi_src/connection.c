#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char cmd[128];
	char buf[512];
	char result[512];
	FILE *fp=NULL;
	int connection=0;
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"wlanconfig ath0 list 2>/dev/null");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<10)
			continue;
		connection++;	
	}	
	pclose(fp);
	if(connection>0)
		connection--;
	printf("%d",connection);
	return 0;
}
