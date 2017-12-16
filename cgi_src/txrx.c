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
	unsigned long long ullrxstart=0,ulltxstart=0;
	printf("Content-Type: text/html\r\n\r\n");
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
}
