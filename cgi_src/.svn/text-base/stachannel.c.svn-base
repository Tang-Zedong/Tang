#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PARAMETER_LEN 8

int main()
{
	char cmd[64];
	char buf[512];
        char cvap[PARAMETER_LEN];
	char *pstart=NULL;
        char *pend=NULL;
        char *qdata=NULL;
        char *qstart=NULL;
        char *qend=NULL;
        int ivap=0;
	int para_len=0;
	int noparameter=0;
	FILE *fp=NULL;

	qdata=getenv("QUERY_STRING");
        if(qdata==NULL)
        {
                printf("Content-Type: text/html\r\n\r\n");
                printf("No parameter!");
                return 1;
        }

        qstart=qdata;
        para_len=0;
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



        if(para_len>PARAMETER_LEN)
        {
                printf("Content-Type: text/html\r\n\r\n");
                printf("Can not parse the parameter!");
                return 1;
        }

	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"iwconfig ath%d 2>/dev/null|sed -n \"/Frequency/p\"|sed \"s/.*Frequency://g\"|sed \"s/ GHz.*//g\"",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<3)
			continue;
		if(buf[0]!=0)
			printf("%s",buf);
	}	
	pclose(fp);
	return 0;
}
