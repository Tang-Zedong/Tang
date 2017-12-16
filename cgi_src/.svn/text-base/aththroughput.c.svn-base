#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
int main()
{
	char cmd[512];
	char buf[512];
	char result[512];
	FILE *fp=NULL;
	unsigned long long ullrxstart=0,ullrxend=0,ullrxd=0,ulltxstart=0,ulltxend=0,ulltxd=0;
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"ifconfig ath0|sed -n  \"/RX bytes/p\"|sed -n \"s/ \\{1,\\}RX bytes://p\"|sed -n \"s/ (.*//p\"");
	fp=popen(cmd,"r");
	memset(buf,0,sizeof(buf));
	fgets(buf,sizeof(buf),fp);
	pclose(fp);
	ullrxstart=atoll(buf);
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"ifconfig ath0|sed -n \"/TX bytes/p\"|sed -n \"s/.*TX bytes://p\"|sed -n \"s/ (.*//p\"");
	fp=popen(cmd,"r");
	memset(buf,0,sizeof(buf));
	fgets(buf,sizeof(buf),fp);
	pclose(fp);
	ulltxstart=atoll(buf);
	sleep(2);	
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"ifconfig ath0|sed -n  \"/RX bytes/p\"|sed -n \"s/ \\{1,\\}RX bytes://p\"|sed -n \"s/ (.*//p\"");
	fp=popen(cmd,"r");
	memset(buf,0,sizeof(buf));
	fgets(buf,sizeof(buf),fp);
	pclose(fp);
	ullrxend=atoll(buf);
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"ifconfig ath0|sed -n \"/TX bytes/p\"|sed -n \"s/.*TX bytes://p\"|sed -n \"s/ (.*//p\"");
	fp=popen(cmd,"r");
	memset(buf,0,sizeof(buf));
	fgets(buf,sizeof(buf),fp);
	pclose(fp);
	ulltxend=atoll(buf);
	ullrxd=(ullrxend-ullrxstart)/2;
	ulltxd=(ulltxend-ulltxstart)/2;
	memset(result,0,sizeof(result));
	if((ullrxd>1024*1024)&&(ulltxd>1024*1024))
		sprintf(result,"RX=%lluMB/s,TX=%lluMB/s",ullrxd/(1024*1024),ulltxd/(1024*1024));
	else if((ullrxd<1024*1024)&&(ulltxd<1024*1024))
		sprintf(result,"RX=%lluKB/s,TX=%lluKB/s",ullrxd/1024,ulltxd/1024);
	else if((ullrxd>1024*1024)&&(ulltxd<1024*1024))
		sprintf(result,"RX=%lluMB/s,TX=%lluKB/s",ullrxd/(1024*1024),ulltxd/1024);
	else if((ullrxd<1024*1024)&&(ulltxd>1024*1024))
		sprintf(result,"RX=%lluKB/s,TX=%lluMB/s",ullrxd/1024,ulltxd/(1024*1024));
	printf("%s",result);
	return 0;
}
