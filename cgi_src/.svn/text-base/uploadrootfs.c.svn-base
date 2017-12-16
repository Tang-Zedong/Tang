/*******************************************************************************
 * Firemware Upgrade CGI
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/reboot.h>
#include<sys/param.h>
#include<sys/types.h>
#include <sys/signal.h>


char* trim(char strings[])
{
        int i=0;
        while(strings[i]!='\0'&&strings[i]!='\n'&&strings[i]!='\r'&&strings[i]!='\t')
                i++;
        strings[i]='\0';
        return strings;
}


int main()
{
	unsigned long lconlen=0;
	FILE *fp=NULL;
	unsigned char *ucpbuf=NULL;
	char cboundary[128];
	char cfilename[64];
	char cfullfilename[64];
	char cmd[128];
	char *cpstart=NULL;
	char *cpstop=NULL;
	char *cpubootstop=NULL;
	pid_t ret_pid=-1;
	int i=0;
	char waitbuf[1024];
	char cubootlen[8];
	int iubootlen=0;
	int ret_val = 0;

	system("rm /tmp/TB-v*");
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
	while(strncmp(cpstart,"Content-Type: application/octet-stream",strlen("Content-Type: application/octet-stream"))!=0&&cpstart<(ucpbuf+lconlen))
	cpstart++;
	cpstart=cpstart+strlen("Content-Type: application/octet-stream")+4;
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
	if(strstr(cfilename,"TB-v")==NULL)
	{
		printf("<html><head>\r\n");
		printf("</head><body>\r\n");
		printf("File name is wrong!\r\n");
		printf("</body></html>");
		return -1;
	}
	memset(cfullfilename,0,sizeof(cfullfilename));
	sprintf(cfullfilename,"/tmp/%s",cfilename);
	fp=fopen(cfullfilename,"w");
	if(fp==NULL)
		return -1;
	fwrite(cpstart,(cpstop-cpstart),1,fp);
	fclose(fp);
	memset(cmd,0,sizeof(cmd));

	sprintf(cmd, "fw_upgrade -v %s", cfullfilename);
	ret_val = system(cmd);

	if(ret_val !=0)
	{
		printf("\r\n");
		fp=fopen("/usr/www/firmerror.html","r");
		while(!feof(fp))
       		{	
			memset(waitbuf,0,1024);
			fgets(waitbuf,1024,fp);
			printf("%s",waitbuf);
		}
		fclose(fp);
		free(ucpbuf);
		ucpbuf=NULL;	
		return -1;
	}

	free(ucpbuf);
	ucpbuf=NULL;	

	ret_pid=fork();
	if(ret_pid==-1)
	{
		printf("Update firmware failed!\n");
		exit(-1);
	}
	else if(ret_pid==0)
	{
		system("echo \"0\">/mnt/modify_flag");
		setsid();
		for(i=0;i<NOFILE;i++)
			close(i);

		sprintf(cmd, "cp -fr /bin/fw_upgrade /tmp");
		system(cmd);
		// sleep 3 for waiting push page to browser
		sleep(3);
		sprintf(cmd, "/tmp/fw_upgrade %s &", cfullfilename);
		system(cmd);
	}
	else
	{
		fp=fopen("/etc/ath/en_ch_mode.conf","r");
		memset(waitbuf,0,1024);
		fgets(waitbuf,1024,fp);
		fclose(fp);
		trim(waitbuf);
		if(strcmp(waitbuf,"System_Settings")==0)
		{
			system("/bin/cp /usr/www/Wait_ori.html /usr/www/Wait.html -fr");
		}
		else
		{
			system("/bin/cp /usr/www/Wait_ori.html /usr/www/Wait.html -fr");
			system("/bin/sed -i 's/enchmode=\"System_Settings\";/enchmode=\"System_Settings_EN\";/'  /usr/www/Wait.html");	
		}		
		printf("\r\n");
		fp=fopen("/usr/www/Wait.html","r");
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
