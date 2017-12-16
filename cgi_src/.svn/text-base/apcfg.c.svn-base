#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
int main()
{
	FILE *fp=NULL;
	char cbuf[1024];
	char cfilename[64];
	struct stat sb;
	int rs=0;
	char *pbuff=NULL;
        char *pstart=NULL;
        char *pstop=NULL;
        char cipaddr[16];
        char session_path[32];
        unsigned long long ulltime_current;
        unsigned long long ulltime_record;
        unsigned long long ulltimeout;
	int i=0;

	        pbuff=getenv("REMOTE_ADDR");
        memset(cipaddr,0,sizeof(cipaddr));
        pstart=pbuff;
        while(!(*pstart>='0'&&*pstart<='9'))
                pstart++;
        pstop=pstart;
        while((*pstop>='0'&&*pstop<='9')||(*pstop=='.'))
                pstop++;
        memcpy(cipaddr,pstart,pstop-pstart);
        ulltime_current=time(NULL);
        memset(session_path,0,sizeof(session_path));
        sprintf(session_path,"/tmp/%s",cipaddr);
        fp=fopen(session_path,"r");
        if(fp==NULL)
        {
                         printf("Content-Type:text/html\r\n");
                         printf("<HTML><HEAD>\r\n");
                         printf("</head><body>\r\n");
                         printf("You should login at first!\r\n");
                         printf("</body></html>");
                         exit(1);
       }
       else
       {
                fscanf(fp,"%llu",&ulltime_record);
                fclose(fp);
       }


	system("cat /tmp/.apcfg|md5sum>/tmp/apcfg");
	system("cat /tmp/.apcfg>>/tmp/apcfg");
	//sprintf(cfilename,"/tmp/.apcfg");
	sprintf(cfilename,"/tmp/apcfg");
	stat(cfilename,&sb);
	printf("Content-Disposition:attachment;filename=\"apcfg\";");
	printf("Content-Length:%lu;",sb.st_size);
	printf("Content-Type:application/octet-stream\n\n");
	if(fp=fopen(cfilename,"r+b"))
	{
		do{
			rs=fread(cbuf,1,sizeof(cbuf),fp);
			for(i=0;i<rs;i++)
				cbuf[i]+='9';	
			fwrite(cbuf,rs,1,stdout);
		}while(!feof(fp));
		fclose(fp);
	}
}
