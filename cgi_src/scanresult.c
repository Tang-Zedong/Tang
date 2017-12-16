#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char buf[1024];
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	fp=fopen("/tmp/startscan.log","r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fread(buf,1,sizeof(buf),fp);
		printf("%s",buf);
	}
	if(fp)			
	fclose(fp);
	return 0;
}
