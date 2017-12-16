#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PARAMETER_LEN 8
int main()
{
	char cmd[512];
	char buf[512];
	char result[512];
	char *pstart=NULL;
	char *pend=NULL;
	FILE *fp=NULL;
	char *qdata=NULL;
        char *qstart=NULL;
        char *qend=NULL;
        char wanmode[PARAMETER_LEN];
	char wanmode_flag=0;
	char port[PARAMETER_LEN];
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
	
	memset(wanmode,0,sizeof(wanmode));
	memcpy(wanmode,qstart,qend-qstart);

	qend++;
	qstart=qend;
	if(strncmp(qstart,"port",strlen("port"))==0)
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
		memset(port,0,sizeof(port));
		memcpy(port,qstart,qend-qstart);
	}
	else
	{
		noparameter=1;		
	}
	
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	if(strcmp(wanmode,"pppoe")==0)
	{
		sprintf(cmd,"ifconfig ppp0 2>/dev/null|sed -n \"/inet addr/p\"|sed \"s/[a-zA-Z:]//g\"|sed \"s/ \\{3,\\}//g\"|sed \"s/ \\{1,\\}/,/g\"|sed \"s/,.*,/,/g\"");
	}
	else
	{
		sprintf(cmd,"ifconfig %s 2>/dev/null|sed -n \"/inet addr/p\"|sed \"s/[a-zA-Z:]//g\"|sed \"s/ \\{3,\\}//g\"|sed \"s/ \\{1,\\}/,/g\"|sed \"s/,.*,/,/g\"",port);
	}
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		memset(result,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<10)
		{
			sprintf(result,"0.0.0.0,0.0.0.0,");
		}
		else
		{
			sprintf(result,"%s,",buf);
			break;
		}
	}	
	pclose(fp);
	printf("%s",result);

	memset(cmd,0,sizeof(cmd));
	if(strcmp(wanmode,"pppoe")==0)
	{
		sprintf(cmd,"ifconfig ppp0|sed -n \"/inet addr/p\"|sed \"s/.*P-t-P://g\"|sed \"s/ .*//g\"");
	}
	else
	{
		sprintf(cmd,"route|sed -n \"/default/p\"|sed \"s/ \\{1,\\}/,/g\"|sed \"s/default,//g\"|sed \"s/,.*//g\"");
	}

	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		memset(result,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<4)
		{
			sprintf(result,"0.0.0.0;");
		}
		else
		{
			sprintf(result,"%s;",buf);
			break;
		}
	}
	pclose(fp);
	printf("%s",result);

	return 0;
}
