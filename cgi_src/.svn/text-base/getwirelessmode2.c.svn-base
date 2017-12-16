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
	fp=fopen("/dev/mtdblock4","r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strstr(buf,"WIRELESS_MODE_2=sta"))
		{
			printf("0");
			pclose(fp);
        		return 0;
		}
		else if(strstr(buf,"WIRELESS_MODE_2=ap"))
		{
			printf("1");
			pclose(fp);
        		return 0;
		}
		else if(strstr(buf,"WIRELESS_MODE_2=repeater"))
		{
			printf("2");
			pclose(fp);
        		return 0;
		}
	}	
	printf("0");
	pclose(fp);
	return 0;
}
