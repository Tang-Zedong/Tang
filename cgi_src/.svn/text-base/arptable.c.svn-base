#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char cmd[512];
	char buf[512];
	char result[512];
	char *pstart=NULL;
	char *pend=NULL;
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	//sprintf(cmd,"arp -n 2>/dev/null|sed -n \"/Address/!p\"|sed -n \"/incomplete/!p\"|sed \"s/ \\{1,\\}/,/g\"");
	sprintf(cmd,"arp -n 2>/dev/null|sed -n \"/Address/!p\"|sed -n \"/incomplete/!p\"|sed \"s/[?()]//g\"|sed \"s/at//g\"|sed \"s/\\[ether\\]  on//g\"|sed \"s/ \\{1,\\}/,/g\"|sed \"s/,//\"");
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
	//	while((*pstart!=','))
	//		pstart++;
	//	pstart++;
		memset(result,0,sizeof(result));
		memcpy(result,pstart,17);
		printf("%s,",result);
		
		pstart+=18;
		//while((*pstart!=','))
		//	pstart++;
	//	pstart++;
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
