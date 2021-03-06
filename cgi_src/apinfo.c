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
	int wlanconfig_count=0;
	char *data=NULL;
        char *start=NULL;
        char *end=NULL;
        char cvap[2];
        int ivap=0;
        data=getenv("QUERY_STRING");
        if(data==NULL)
        {
                printf("Content-Type: text/html\r\n\r\n");
                printf("Invalid parameter!");
                return 1;
        }
        start=data;
        while(*start!='=')
                start++;

        start++;
        end=start;

        while(*end!='&')
                end++;

        memcpy(cvap,start,end-start);
        ivap=atoi(cvap);
        ivap-=1;

	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"wlanconfig ath%d list 2>/dev/null|sed -n \"/ADDR/!p\"|sed \"s/ \\{1,\\}/,/g\"",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		wlanconfig_count++;
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
		while((*pstart!=','))
			pstart++;
			pstart++;

		while((*pstart!=','))
			pstart++;
			pstart++;
		pend=pstart;
		while((*pend!=','))
			pend++;
		memset(result,0,sizeof(result));
		memcpy(result,pstart,pend-pstart);
		printf("%s,",result);
	}	
	pclose(fp);
	if(wlanconfig_count<=1)
	return 0;

	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"iwconfig ath%d 2>/dev/null|sed \"s/ \\{1,\\}//g\"",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<10)
			continue;
		pstart=strstr(buf,"Signallevel=");
		if(pstart)
		{
			pstart+=strlen("Signallevel=");
			pend=pstart;
			while((*pend!='d'))
				pend++;
			memset(result,0,sizeof(result));
			memcpy(result,pstart,pend-pstart);
        	        printf("%s,",result);
		}

		pstart=strstr(buf,"Noiselevel=");
		if(pstart)
		{
			pstart+=strlen("Noiselevel=");
			pend=pstart;
			while((*pend!='d'))
				pend++;
			memset(result,0,sizeof(result));
			memcpy(result,pstart,pend-pstart);
        	        printf("%s,",result);
		}
	}	
	pclose(fp);

	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"ifconfig ath%d 2>/dev/null|sed \"s/ \\{1,\\}//g\"",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<10)
			continue;
		pstart=strstr(buf,"RXpackets:");
                if(pstart)
                {
                        pstart+=strlen("RXpackets:");
                        pend=pstart;
                        while((*pend!='e'))
                                pend++;
                        memset(result,0,sizeof(result));
                        memcpy(result,pstart,pend-pstart);
                        printf("%s,",result);
                }	
		
		pstart=strstr(buf,"TXpackets:");
                if(pstart)
                {
                        pstart+=strlen("TXpackets:");
                        pend=pstart;
                        while((*pend!='e'))
                                pend++;
                        memset(result,0,sizeof(result));
                        memcpy(result,pstart,pend-pstart);
                        printf("%s,",result);
                } 
      
		pstart=strstr(buf,"RXbytes:");
                if(pstart)
                {
                        pstart+=strlen("RXbytes:");
                        pend=pstart;
                        while((*pend!='('))
                                pend++;
                        memset(result,0,sizeof(result));
                        memcpy(result,pstart,pend-pstart);
                        printf("%s,",result);
                } 
      
		pstart=strstr(buf,"TXbytes:");
                if(pstart)
                {
                        pstart+=strlen("TXbytes:");
                        pend=pstart;
                        while((*pend!='('))
                                pend++;
                        memset(result,0,sizeof(result));
                        memcpy(result,pstart,pend-pstart);
                        printf("%s;",result);
                }       
	}
	pclose(fp);
	return 0;
}
