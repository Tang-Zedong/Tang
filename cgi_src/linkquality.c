#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char cmd[128];
	char buf[512];
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"iwconfig ath0|sed -n \"/Link Quality/p\"|sed \"s/.*Link Quality=//\"|sed \"s/\\/.*//\" 2>/dev/null");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(buf[0]!=0)
			printf("%s",buf);
	}	
	pclose(fp);
	return 0;
}
