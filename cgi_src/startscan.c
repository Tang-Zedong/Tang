#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char cmd[512];
	char buf[512];
	int i=0;
	FILE *fp=NULL,*fp_save=NULL;
	int freq=0,rssi=0;
	pid_t ret_pid=-1;
	int try_count=0;
	printf("Content-Type: text/html\r\n\r\n");
try_again:
	system("killall athssd");
	system("rm /tmp/startscan.log -fr");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"cd /tmp/&&athssd -a -i wifi0 -j ath0 -c 5&");
	ret_pid=fork();
	if(ret_pid==-1)
	{
		exit(-1);
	}
	if(ret_pid==0)
	{
		system("spectraltool -i wifi0 priority 1");
		system("spectraltool -i wifi0 startscan");
		sleep(60);
		system("spectraltool -i wifi0 priority 0");
		system("spectraltool -i wifi0 stopscan");
		system("killall  athssd");
		sleep(2);	
	}
	else
	{
		fp_save=fopen("/tmp/startscan.log","w+");
		fp=popen(cmd,"r");
		while(!feof(fp))
		{
			memset(buf,0,sizeof(buf));
			fgets(buf,sizeof(buf),fp);
			if(strncmp(buf,"Found interference",strlen("Found interference"))==0)
			{
				sscanf(buf,"Found interference in freq %d,spectral_rssi=%d",&freq,&rssi);	
				//if(freq<3000&&freq>2000)
				if(freq>4000&&freq<7000)
				fprintf(fp_save,"%d,%d;",freq,rssi);
			}	
		}	
		pclose(fp);
		fclose(fp_save);
	}
	
	if(ret_pid==0)
	{
		fp_save=fopen("/tmp/startscan.log","r");
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp_save);
		fclose(fp_save);
		if(strlen(buf)<4&&try_count<2)
		{
			try_count++;
			goto try_again;
		}
	}
	return 0;
}
