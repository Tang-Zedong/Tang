#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PARAMETER_LEN 8
int main()
{
	char cmd[128];
	char buf[512];
	char result[512];
	char *pstart=NULL;
	char *pend=NULL;
	FILE *fp=NULL;
	char *qdata=NULL;
        char *qstart=NULL;
        char *qend=NULL;
        char cvap[PARAMETER_LEN];
        int ivap=0;
	char cchannel[PARAMETER_LEN];
	int ichannel_is_2g=0;
	int para_len=0;
	int noparameter=0;

	qdata=getenv("QUERY_STRING");
        if(qdata==NULL)
        {
                printf("Content-Type: text/html\r\n\r\n");
                printf("No parameter!");
                return 1;
        }

	qstart=qdata;
        while(*qstart!='=')
                qstart++;

        qstart++;
        qend=qstart;
	
	para_len=0;
        while(*qend!='&'&&para_len<PARAMETER_LEN)
	{
                qend++;
		para_len++;
	}
	
	if(para_len>PARAMETER_LEN)
	{
                printf("Content-Type: text/html\r\n\r\n");
                printf("Can not parse the parameter!");
                return 1;
	}
	
	memset(cchannel,0,sizeof(cchannel));
	memcpy(cchannel,qstart,qend-qstart);
	if(strcmp(cchannel,"2g")==0)
		ichannel_is_2g=1;
	else
		ichannel_is_2g=0;

	qend++;
	qstart=qend;
	if(qstart[0]=='v'&&qstart[1]=='a'&&qstart[2]=='p')
	{
        	while(*qstart!='=')
               		qstart++;
        	qstart++;
        	qend=qstart;

		para_len=0;
	        while(*qend!='&'&&para_len<PARAMETER_LEN)
		{
       	        	qend++;
			para_len++;
		}
			
		if(para_len>PARAMETER_LEN)
		{
                	printf("Content-Type: text/html\r\n\r\n");
                	printf("Can not parse the parameter!");
                	return 1;
		}
		memset(cvap,0,sizeof(cvap));
		memcpy(cvap,qstart,qend-qstart);
		ivap=atoi(cvap);	
	}
	else
	{
		ivap=1;
		noparameter=1;		
	}
	ivap-=1;	
	
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"wlanconfig ath%d list channel 2>/dev/null|sed \"s/ \\{1,\\}/,/g\"",ivap);
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
		//printf("%s,",result);

		pstart=pend+1;
		while((*pstart!=','))
			pstart++;
		pstart++;
		pend=pstart;
		while((*pend!=','))
			pend++;
		if(noparameter==0)
		{	
			if(pstart[0]=='2')
			{
				if(ichannel_is_2g==1)
				{
					printf("%s,",result);
				}
				else
				{
					continue;
				}
			}
			else
			{
				if(ichannel_is_2g==0)
				{
					printf("%s,",result);
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
					printf("%s,",result);
		}	
	
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
