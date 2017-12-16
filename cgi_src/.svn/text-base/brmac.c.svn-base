#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char cmd[64];
	char buf[512];
	char result[512];
	char *pstart=NULL;
	char *pend=NULL;
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"brctl showmacs br0 2>/dev/null|sed -n \"/port/!p\"");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<10)
			continue;
		pstart=buf+4;
		memset(result,0,sizeof(result));
		memcpy(result,pstart,17);
		printf("%s,",result);

		pstart+=17;
		memset(result,0,sizeof(result));
		while((*pstart)!='0'&&
		      (*pstart)!='1'&&
		      (*pstart)!='2'&&
		      (*pstart)!='3'&&
		      (*pstart)!='4'&&
		      (*pstart)!='5'&&
		      (*pstart)!='6'&&
		      (*pstart)!='7'&&
		      (*pstart)!='8'&&
		      (*pstart)!='9')
			pstart++;
		pend=pstart;
		while((*pend)=='0'||
                      (*pend)=='1'||
                      (*pend)=='2'||
                      (*pend)=='3'||
                      (*pend)=='4'||
                      (*pend)=='5'||
                      (*pend)=='6'||
                      (*pend)=='7'||
                      (*pend)=='8'||
                      (*pend)=='9'||
		      (*pend)=='.')
                        pend++;
		
		memcpy(result,pstart,pend-pstart);
		printf("%s;",result);
	}	
	pclose(fp);
	return 0;
}
