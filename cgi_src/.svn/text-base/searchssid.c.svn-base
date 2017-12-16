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
	int noparameter=0;
	int para_len=0;

	qdata=getenv("QUERY_STRING");
        if(qdata==NULL)
        {
                printf("Content-Type: text/html\r\n\r\n");
                printf("No parameter!");
                return 1;
        }
	qstart=qdata;
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
	sprintf(cmd,"iwpriv ath%d kickmac ff:ff:ff:ff:ff:ff 2>/dev/null && iwlist ath%d scanning 2>/dev/null|sed \"s/ \\{1,\\}//g\"",ivap,ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		pstart=strstr(buf,"Address:");
		if(pstart)
		{
			memset(result,0,sizeof(result));
			pstart+=strlen("Address:");
			memcpy(result,pstart,17);
			printf("%s,",result);
			continue;
		}

		pstart=strstr(buf,"ESSID:");
		if(pstart)
		{
			memset(result,0,sizeof(result));
			pstart+=strlen("ESSID:\"");
			pend=pstart;
			while((*pend)!='"')
				pend++;
			memcpy(result,pstart,pend-pstart);
			printf("%s,",result);
			continue;
		}
		
	/*	pstart=strstr(buf,"Channel");
		if(pstart)
		{
			memset(result,0,sizeof(result));
			pstart+=strlen("Channel");
			pend=pstart;
			while((*pend)!=')')
				pend++;
			memcpy(result,pstart,pend-pstart);
			printf("%s,",result);
		}
		else
*/
		{
			pstart=strstr(buf,"Frequency:");
			if(pstart)
			{
				memset(result,0,sizeof(result));
				pstart+=strlen("Frequency:");
				pend=pstart;
				while((*pend)!='G')
					pend++;
				memcpy(result,pstart,pend-pstart);
				printf("%s,",result);
			}
		}

		pstart=strstr(buf,"Signallevel=");
		if(pstart)
		{
			memset(result,0,sizeof(result));
			pstart+=strlen("Signallevel=");
			pend=pstart;
			while((*pend)!='d')
				pend++;
			memcpy(result,pstart,pend-pstart);
			printf("%s;",result);
			continue;
		}
	}	
	pclose(fp);
	return 0;
}
