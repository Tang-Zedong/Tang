#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PARAMETER_LEN 8

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
	char cmd[128];
	char buf[512];
	char cmdflag40m[128];
	char bufflag40m[512];
	int connection=0;
	FILE *fp=NULL;

	char *pstart=NULL;
	char *pend=NULL;
	char *qdata=NULL;
	char *qstart=NULL;
	char *qend=NULL;
	char cvap[PARAMETER_LEN];
	int ivap=0;
	int para_len=0;
	int connected=1;
	int fakesta=0;
	char wan_if[8];
	int have_wanip=0;
	int have_wanmac=0;
	int have_distance=0;
	int have_tdma=0;
	int is_bridge=0;
	int acktime=0;
	int distance=0.0;

	unsigned long long ullrxstart=0,ulltxstart=0;
	char result[512];

	printf("Content-Type: text/html\r\n\r\n");
	//----------------------get parameter----------------------------
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
	}
	ivap-=1;

	if(0){

		memset(cmd,0,sizeof(cmd));
		sprintf(cmd,"ifconfig eth0 2>/dev/null|sed -n  \"/RX bytes/p\"|sed -n \"s/ \\{1,\\}RX bytes://p\"|sed -n \"s/ (.*//p\"");
		fp=popen(cmd,"r");
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		pclose(fp);
		//ullrxstart=atoll(buf);
		ulltxstart=atoll(buf);
		memset(cmd,0,sizeof(cmd));
		sprintf(cmd,"ifconfig eth0 2>/dev/null|sed -n \"/TX bytes/p\"|sed -n \"s/.*TX bytes://p\"|sed -n \"s/ (.*//p\"");
		fp=popen(cmd,"r");
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		pclose(fp);
		ullrxstart=atoll(buf);
		//ulltxstart=atoll(buf);
		memset(result,0,sizeof(result));
		sprintf(result,"{\"rx\":\"%llu\",\"tx\":\"%llu\"}",ullrxstart,ulltxstart);
		printf("%s",result);
		return 0;
	}else{
		memset(cmd,0,sizeof(cmd));
		sprintf(cmd,"ifconfig ath%d 2>/dev/null|sed -n  \"/RX bytes/p\"|sed -n \"s/ \\{1,\\}RX bytes://p\"|sed -n \"s/ (.*//p\"", ivap);
		fp=popen(cmd,"r");
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		pclose(fp);
		ullrxstart=atoll(buf);
		//ulltxstart=atoll(buf);
		memset(cmd,0,sizeof(cmd));
		sprintf(cmd,"ifconfig ath%d 2>/dev/null|sed -n \"/TX bytes/p\"|sed -n \"s/.*TX bytes://p\"|sed -n \"s/ (.*//p\"", ivap);
		fp=popen(cmd,"r");
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		pclose(fp);
		//ullrxstart=atoll(buf);
		ulltxstart=atoll(buf);
		memset(result,0,sizeof(result));
		sprintf(result,"{\"rx\":\"%llu\",\"tx\":\"%llu\"}",ullrxstart,ulltxstart);
		printf("%s",result);
		//printf("%s ivap=%s",result, ivap);
		return 0;

	}

	if(1){
		memset(cmd,0,sizeof(cmd));
		sprintf(cmd,"iwpriv ath%d get_mode |sed -n \"/get_mode:/p\" |sed \"s/.*get_mode://g\" 2>/dev/null", ivap);
		fp=popen(cmd,"r");
		while(!feof(fp))
		{
			memset(buf,0,sizeof(buf));
			fgets(buf,sizeof(buf),fp);
			if(buf[0]!=0){
				printf("80211mode=%s;",trim(buf));break;
			}
		}
		pclose(fp);
	}
}

