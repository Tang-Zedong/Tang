#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/reboot.h>
#include<sys/param.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	unsigned long lconlen=0;
	FILE *fp=NULL;
	unsigned char *ucpbuf=NULL;
	char cboundary[128];
	char cfilename[32];
	char cfullfilename[64];
	char *cpstart=NULL;
	char *cpstop=NULL;
	char *cpbak=NULL;
	pid_t ret_pid=-1;
	int i=0;
	char waitbuf[1024];
	char cmd[1024];

	lconlen=atoi(getenv("CONTENT_LENGTH"));
	if(lconlen<=0)
	{
		return -1;
	}
	ucpbuf=(unsigned  char*)malloc(lconlen+1);
	fread(ucpbuf,lconlen,1,stdin);
	cpstart=ucpbuf;
	cpstop=ucpbuf;
	while(*cpstop!='\r'&&cpstop<(ucpbuf+lconlen))
		cpstop++;
	memset(cboundary,0,sizeof(cboundary));
	memcpy(cboundary,cpstart,(cpstop-cpstart));
	while(strncmp(cpstart,"filename=",strlen("filename="))!=0&&cpstart<(ucpbuf+lconlen))
		cpstart++;	
	cpstart=cpstart+strlen("filename=")+1;
	cpstop=cpstart;
	if(*(cpstart+1)==':'&&*(cpstart+2)=='\\')
	{
		while(*cpstop!='\"'&&cpstop<(ucpbuf+lconlen))
			cpstop++;
		cpstart=cpstop;
		while(*cpstart!='\\'&&cpstart<(ucpbuf+lconlen))
			cpstart--;
		cpstart++;
	}
	else
	{
		while(*cpstop!='\"'&&cpstop<(ucpbuf+lconlen))
                        cpstop++;
	}
	memset(cfilename,0,sizeof(cfilename));
	memcpy(cfilename,cpstart,cpstop-cpstart);
	cpbak=cpstart;
	while(strncmp(cpstart,"Content-Type: text/plain",strlen("Content-Type: text/plain"))!=0&&cpstart<(ucpbuf+lconlen))
	cpstart++;
	if(cpstart<ucpbuf+lconlen)
	{
		cpstart=cpstart+strlen("Content-Type: text/plain")+4;
	}
	else
	{
		cpstart=cpbak;
		while(strncmp(cpstart,"Content-Type: application/octet-stream",strlen("Content-Type: application/octet-stream"))!=0&&cpstart<(ucpbuf+lconlen))
			cpstart++;
		cpstart=cpstart+strlen("Content-Type: application/octet-stream")+4;
	}
	cpstop=cpstart;
	while(strncmp(cpstop,cboundary,strlen(cboundary))!=0&&cpstop<(ucpbuf+lconlen))
		cpstop++;
	cpstop=cpstop-2;
	if(cpstart>=(ucpbuf+lconlen))
	{
		free(ucpbuf);
		ucpbuf=NULL;	
		printf("<html><head>\r\n");
		printf("</head><body>\r\n");
		printf("Upload wrong format file!\r\n");
		printf("</body></html>");
		return -1;
	}
	//if(strcmp(cfilename,"apcfg")!=0)
	if(0)
	{
		free(ucpbuf);
                ucpbuf=NULL;
		printf("<html><head>\r\n");
		printf("</head><body>\r\n");
		printf("File name is wrong!\r\n");
		printf("</body></html>");
		return -1;
	}

	for(i=0;i<cpstop-cpstart;i++)
	{
		cpstart[i]-='9';
	}
	
	fp=fopen("/tmp/md5.txt","w");
        if(fp==NULL)
                return -1;
        fwrite(cpstart,36,1,fp);
        fclose(fp);

        cpstart+=36;
	
	memset(cfullfilename,0,sizeof(cfullfilename));
	sprintf(cfullfilename,"/tmp/%s",cfilename);
	fp=fopen(cfullfilename,"w");
	if(fp==NULL)
		return -1;
	fwrite(cpstart,(cpstop-cpstart),1,fp);
	fclose(fp);	
	
	memset(cmd,0,sizeof(cmd));
        sprintf(cmd,"cat %s|md5sum -c /tmp/md5.txt>/dev/null 2>&1",cfullfilename);

	//if((cpstart[0]&0xff)!=0xfa||(cpstart[1]&0xff)!=0xf3||(cpstart[2]&0xff)!=0x00||(cpstart[3]&0xff)!=0x21)
	if(system(cmd)!=0)
        {
                free(ucpbuf);
                ucpbuf=NULL;
		printf("\r\n");
		fp=fopen("/usr/www/conferror.html","r");
                while(!feof(fp))
                {
                        memset(waitbuf,0,1024);
                        fgets(waitbuf,1024,fp);
                        printf("%s",waitbuf);
                }
                fclose(fp);
                //printf("<html><head>\r\n");
                //printf("</head><body>\r\n");
                //printf("File format is wrong!\r\n");
                //printf("</body></html>");
                return -1;
        }
	free(ucpbuf);
	ucpbuf=NULL;	
	
	ret_pid=fork();
	if(ret_pid==-1)
	{
		exit(-1);
	}
	else if(ret_pid==0)
	{
		setsid();
		for(i=0;i<NOFILE;i++)
			close(i);
		fp=fopen("/dev/nvram","r");
		if(fp)
		{
			fclose(fp);
            sprintf(cmd, "dd if=%s of=/dev/nvram conv=sync > /dev/null 2>&1", cfullfilename);
            system(cmd);
			//system("dd if=/tmp/apcfg of=/dev/nvram conv=sync> /dev/null 2>&1");
		}
		else
		{
            sprintf(cmd, "dd if=%s of=/dev/mtdblock4 conv=sync > /dev/null 2>&1", cfullfilename);
            system(cmd);
			//system("dd if=/tmp/apcfg of=/dev/mtdblock4 conv=sync> /dev/null 2>&1");
		}
		sleep(3);
		reboot(RB_AUTOBOOT);	
	}
	else
	{
		printf("\r\n");
		 fp=fopen("/usr/www/ConfigureWait.html","r");
                while(!feof(fp))
                {
                        memset(waitbuf,0,1024);
                        fgets(waitbuf,1024,fp);
                        printf("%s",waitbuf);
                }
                fclose(fp);
	}
	return 0;
}
