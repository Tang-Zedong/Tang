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
	sprintf(cmd,"route 2>/dev/null|sed -n \"/Kernel/!p\"|sed -n \"/Destination/!p\"|sed \"s/ \\{1,\\}/,/g\"");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<10)
			continue;
		pstart=buf;
		pend=pstart;
		while((*pend!=','))
			pend++;
		memset(result,0,sizeof(result));
		memcpy(result,pstart,pend-pstart);
		printf("%s,",result);

		pstart=pend+1;
		pend=pstart;
		while((*pend!=','))
			pend++;
		memset(result,0,sizeof(result));
		memcpy(result,pstart,pend-pstart);
		printf("%s,",result);
	
		pstart=pend+1;
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
		while((*pstart!=','))
			pstart++;
		pstart++;
		while((*pstart!=','))
			pstart++;
		pstart++;
		while((*pstart!=','))
			pstart++;
		pstart++;
		pend=pstart;
		while((*pend!='0'))
			pend++;
		pend++;
		memset(result,0,sizeof(result));
		memcpy(result,pstart,pend-pstart);
		printf("%s;",result);
	}	
	pclose(fp);
	return 0;
}
