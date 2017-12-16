#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char cmd[512];
	char buf[512];
	int i=0;
	int is_tb5ca=0;
    int is_11ac_specific=0;
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	fp=fopen("/etc/rootfsversion","r");
	memset(buf,0,sizeof(buf));
	fgets(buf,sizeof(buf),fp);
	fclose(fp);
	if(strstr(buf,"TB5CA-CPE")||strstr(buf,"TB2E-CPE")||strstr(buf,"TB2E-Bridge")||strstr(buf,"TB2E-Basestation")||strstr(buf,"TB8G-CPE")||strstr(buf,"TB8G-Bridge")||strstr(buf,"TB8G-Basestation")||strstr(buf,"TB5HD-29E")||strstr(buf,"TB5HP-25I")||strstr(buf,"TB5HS-17E")||strstr(buf,"TB5HP-18I")||strstr(buf,"DS-3WF03C-25AC")||strstr(buf,"DS-3WF20A-5AC")||strstr(buf,"DS-3WF10A-5AC")||strstr(buf,"DS-3WF05A-5AC")||strstr(buf,"DS-3WF05C-5AC")||strstr(buf,"DH-PFM880-M")||strstr(buf,"DH-PFM886-20")||strstr(buf,"DH-PFM886-10")||strstr(buf,"DH-PFM880E")||strstr(buf,"TB5H")||strstr(buf,"TB8H")||strstr(buf,"WLN-EB5HD-29E")||strstr(buf,"MK8H"))
	{
		is_tb5ca=1;
	}
	if(strstr(buf,"TA8H")||strstr(buf,"DH-PFM889-IM")||strstr(buf,"DH-PFM880-M")||strstr(buf,"TB8H")||strstr(buf,"DS-3WF03C-25AC"))
	{
		is_11ac_specific=1;
	}
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"ifconfig 2>/dev/null|sed -n \"/Link encap/p\"|sed \"s/ \\{1,\\}//g\"|sed \"s/Link.*//g\"");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<3)
			continue;
		for(i=0;i<10&&buf[i]!='\0';i++)
		{
			if(buf[i]=='\r'||buf[i]=='\n')
			{
				buf[i]='\0';
				break;
			}
		}
		if(is_tb5ca==1)
		{		
			if(strcmp(buf,"eth1")==0)
			{
				continue;
			}	
		}
        if(is_11ac_specific == 1){
            if(strcmp(buf,"ath0") == 0){
                continue;
            }
        }
		printf("%s;",buf);
	}	
	pclose(fp);
	return 0;
}
