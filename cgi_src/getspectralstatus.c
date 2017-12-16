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
        if( buf[0] == 0 ) break;
		if(strstr(buf,"SPECTRAL_EN=1"))
		{
			printf("1");
			pclose(fp);
        		return 0;
		}
	}	
	printf("0");
	pclose(fp);
	return 0;
}
