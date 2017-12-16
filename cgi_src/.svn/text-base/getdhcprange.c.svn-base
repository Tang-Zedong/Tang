#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc, char **varg)
{
	char lanip[16];
	char netmask[16];
	char startip[16];
	char endip[16];
	char cmd[256];
	char buf[128];
	char result[128];	
	FILE *fp=NULL;
	struct in_addr inlanip,inmask,instartip,inendip;
	unsigned long ullanip,ulmask,ulstartip,ulendip,ultmp1,ultmp2,ultmp3;

	memset(cmd,0,sizeof(cmd));
        sprintf(cmd,"ifconfig br0 2>/dev/null|sed -n \"/inet addr/p\"|sed \"s/ \\{1,\\}/,/g\"|sed \"s/[a-zA-Z:]//g\"|cut -d ',' -f 3|tr -d '\n'");
        fp=popen(cmd,"r");
	while(!feof(fp))
        {
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);

        	if(strlen(buf)<4)
		{
			continue;
		}

		break;
        } 
	pclose(fp);  	

	memcpy(lanip,buf,sizeof(lanip));
	if(lanip[0]=='\0')
	{
		printf("0.0.0.0,0.0.0.0;");
		return -1;
	}
	ullanip=inet_addr((const char *)lanip);
	
	memset(cmd,0,sizeof(cmd));
        sprintf(cmd,"ifconfig br0 2>/dev/null|sed -n \"/inet addr/p\"|sed \"s/ \\{1,\\}/,/g\"|sed \"s/[a-zA-Z:]//g\"|cut -d ',' -f 5|tr -d '\n'");
        fp=popen(cmd,"r");
	while(!feof(fp))
        {
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);

        	if(strlen(buf)<4)
		{
			continue;
		}

		break;
        } 
	pclose(fp); 

	memcpy(netmask,buf,sizeof(netmask));
	if(netmask[0]=='\0')
	{
		printf("0.0.0.0,0.0.0.0;");
		return -1;
	}
	ulmask=inet_addr((const char *)netmask);
	ultmp1=(ullanip&ulmask);
	ultmp2=(ullanip|(~ulmask));
	if(ullanip-ultmp1<=ultmp2-ullanip)
	{
		ulstartip=ullanip+1;
		ulendip=ultmp2-1;
	}
	else
	{
		ulstartip=ultmp1+1;
		ulendip=ullanip-1;
	}
	
	memcpy(&instartip,&ulstartip,4);
	memcpy(&inendip,&ulendip,4);
	//printf("lanip=%s,netmask=%s\n",lanip,netmask);
	memset(startip,0,sizeof(startip));
	memset(endip,0,sizeof(endip));
	memset(result,0,sizeof(result));
	sprintf(startip,"%s",inet_ntoa(instartip));
	sprintf(endip,"%s",inet_ntoa(inendip));
	sprintf(result,"%s,%s;",startip,endip);
	printf("%s",result);
	return 0;
} 
