#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char cmd[128];
	char buf[512];
	char result[512];
	char *pstart=NULL;
	char *pend=NULL;
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"wlanconfig ath8 list channel 2>/dev/null|sed \"s/ \\{1,\\}/,/g\"");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<10)
			continue;
		pstart=buf;
		while((*pstart!=','))
			pstart++;
		pstart++;
		pend=pstart;
		while((*pend!=','))
			pend++;
		memset(result,0,sizeof(result));
		memcpy(result,pstart,pend-pstart);
		printf("%s,",result);

		pstart=pend+1;
		while((*pstart!=','))
			pstart++;
		pstart++;
		pend=pstart;
		while((*pend!=','))
			pend++;
	
		memset(result,0,sizeof(result));
		memcpy(result,pstart,pend-pstart);
		printf("%s,",result);
		
		pstart=pend+1;
		while((*pstart!=','))
			pstart++;
		pstart++;
		pend=pstart;
		while((*pend!=','))
			pend++;
		memset(result,0,sizeof(result));
		memcpy(result,pstart,pend-pstart);
		printf("%s,",result);		
		while((*pstart!=','))
			pstart++;
		pstart++;
		while((*pstart!=','))
			pstart++;
		pstart++;
		pend=pstart;
		if(*(pstart+1)=='U')
			printf("U");
		else if(*(pstart+1)=='L')
			printf("L");
		if(*(pstart+4)=='U')
			printf("U");
		else if(*(pstart+4)=='L')
			printf("L");
		printf(";");
	}	
	pclose(fp);
	return 0;
}
