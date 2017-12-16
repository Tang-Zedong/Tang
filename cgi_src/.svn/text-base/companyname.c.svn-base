#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char buf[512];
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	fp=fopen("/mnt/companyname","r");
	if(fp)
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		printf("%s",buf);
		fclose(fp);
	}
	else
	{
		printf("Wireless");
	}
	return 0;
}
