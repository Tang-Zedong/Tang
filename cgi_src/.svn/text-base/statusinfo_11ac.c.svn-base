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
    int have_value=0;

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

	//-----------------channelwidth---------------------------------
	/*	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"iwpriv ath%d get_mode|sed \"s/ath.*://g\" 2>/dev/null",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
	memset(buf,0,sizeof(buf));
	fgets(buf,sizeof(buf),fp);
	if(buf[0]!=0)
	printf("channelwidth=%s;",trim(buf));
	break;
	}
	pclose(fp);
	*/

	memset(cmdflag40m,0,sizeof(cmdflag40m));
	sprintf(cmdflag40m,"cat /etc/ath/disable40.conf 2>/dev/null");
	fp=popen(cmdflag40m,"r");
	while(!feof(fp))
	{
		memset(bufflag40m,0,sizeof(bufflag40m));
		fgets(bufflag40m,sizeof(bufflag40m),fp);
		if(bufflag40m[0]=='0'||bufflag40m[0]=='1')
		{
			break;
		}
	}
	pclose(fp);
	/*
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"iwpriv ath%d get_mode|sed \"s/ath.*://g\" 2>/dev/null",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
	memset(buf,0,sizeof(buf));
	fgets(buf,sizeof(buf),fp);
	if(buf[0]!=0)
	{
	if(bufflag40m[0]=='1')
	{
	if(strncmp(buf,"11NAHT40PLUS",strlen("11NAHT40PLUS"))==0||strncmp(buf,"11NAHT40MINUS",strlen("11NAHT40MINUS"))==0)
	{
	printf("channelwidth=11NAHT20;");
	}
	else if(strncmp(buf,"11NGHT40PLUS",strlen("11NGHT40PLUS"))==0||strncmp(buf,"11NGHT40MINUS",strlen("11NGHT40MINUS"))==0)
	{
	printf("channelwidth=11NGHT20;");
	}
	else
	{
	printf("channelwidth=11NGHT20;");
	}		
	}
	else
	{
	printf("channelwidth=%s;",buf);
	}
	}
	}
	pclose(fp);
	*/

	char channel_width[512];
	fp=fopen("/dev/mtdblock4","r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if ( ivap == 0 ){
			if(strstr(buf,"CHANNEL_WIDTH=")){
				memset(channel_width,0,sizeof(channel_width));
				snprintf(channel_width, strlen(buf)-strlen("CHANNEL_WIDTH="), "%s", buf+strlen("CHANNEL_WIDTH="));
				break;
			}
		}else{
			if(strstr(buf,"CHANNEL_WIDTH_2=")){
				memset(channel_width,0,sizeof(channel_width));
				snprintf(channel_width, strlen(buf)-strlen("CHANNEL_WIDTH_2="), "%s", buf+strlen("CHANNEL_WIDTH_2="));
				break;
			}

		}
	}
	printf("channelwidth=%s;",channel_width);
	fclose(fp);
	//----------------------get connected status--------------------------------
	/*        memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"iwconfig ath%d|sed -n \"/Not-Associated/p\" 2>/dev/null",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
	memset(buf,0,sizeof(buf));
	fgets(buf,sizeof(buf),fp);
	if(strstr(buf,"Not-Associated"))
	{
	connected=0;
	}
	}
	pclose(fp);
	*/
	memset(cmd,0,sizeof(cmd));

	sprintf(cmd,"iwconfig ath%d|sed -n \"/Bit Rate/p\" 2>/dev/null",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strstr(buf,"0 kb/s"))
		{
			connected=0;
		}
	}
	pclose(fp);
	//-----------------rateshow---------------------------------------
	if(connected==1)
	{
		memset(cmd,0,sizeof(cmd));
		sprintf(cmd,"wlanconfig ath%d list 2>/dev/null|sed -n \"2p\"|sed \"s/ \\{1,\\}/X/g\"|cut -d 'X' -f 4",ivap);
		fp=popen(cmd,"r");
		while(!feof(fp))
		{
			memset(buf,0,sizeof(buf));
			fgets(buf,sizeof(buf),fp);
			if(buf[0]!=0)
			{
				printf("rateshow=%s;",trim(buf));
				break;
			}
			else
				printf("rateshow=;");
		}
		pclose(fp);
	}
	else
	{
		printf("rateshow=;");
	}
	//--------------signallevel---------------------------------------

    have_value=0;
	if(connected==1)
	{
		memset(cmd,0,sizeof(cmd));
		sprintf(cmd,"iwconfig ath%d|sed -n \"/Signal/p\"|sed \"s/ \\{1,\\}/X/g\"|cut -d 'X' -f 5|cut -d '=' -f 2 2>/dev/null",ivap);
		fp=popen(cmd,"r");
		while(!feof(fp))
		{
			memset(buf,0,sizeof(buf));
			fgets(buf,sizeof(buf),fp);
            if(buf[0]!=0){
				printf("signallevel=%s;",trim(buf));
                have_value = 1;
                break;
            }
		}
        if(have_value == 0){
		    printf("signallevel=;");
        }
		pclose(fp);
	}
	else
	{
		printf("signallevel=-96(-96/-96);");
	}
	//--------------noisefloor----------------------------------------
    have_value = 0;
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"iwconfig ath%d 2>/dev/null|sed -n \"/Noise level/p\"|sed \"s/.*Noise level=//\"|sed \"s/ dBm.*//\"",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
        if(buf[0]!=0){
			printf("noisefloor=%s;",trim(buf));
            have_value = 1;
            break;
        }
	}
    if(have_value == 0){
		printf("noisefloor=;");
    }
	pclose(fp);
	//--------------linkquality--------------------------------------
    have_value = 0;
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"iwconfig ath%d|sed -n \"/Link Quality/p\"|sed \"s/.*Link Quality=//\"|sed \"s/\\/.*//\" 2>/dev/null",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
        if(buf[0]!=0){
			printf("linkquality=%s;",trim(buf));
            have_value = 1;
            break;
        }
	}
    if(have_value == 0){
		printf("linkquality=;");
    }
	pclose(fp);
	//--------------stachannel---------------------------------------
    have_value = 0;
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"iwconfig ath%d 2>/dev/null|sed -n \"/Frequency/p\"|sed \"s/.*Frequency://g\"|sed \"s/ GHz.*//g\"",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<3&&(buf[0]>'9'||buf[0]<'0'))
			continue;
        if(buf[0]!=0){
			printf("stachannel=%s;",trim(buf));
            have_value = 1;
            break;
        }
	}
    if(have_value == 0){
		printf("stachannel=;");
    }
	pclose(fp);
	//-------------distance------------------------------------------
	memset(cmd,0,sizeof(cmd));
	//sprintf(cmd,"cat /proc/distance 2>/dev/null");
	if(ivap < 8){
		sprintf(cmd,"iwpriv wifi0 get_acktimeout|sed \"s/wifi0     get_acktimeout://g\"|tr -d '\n'|tr -d '\r'");
	}else{
		sprintf(cmd,"iwpriv wifi1 get_acktime_ol|sed \"s/wifi1     get_acktime_ol://g\"|tr -d '\n'|tr -d '\r'");
	}
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(buf[0]!=0)
		{
			//printf("distance=%s;",trim(buf));
			acktime=atoi(trim(buf));
			distance=(acktime-38)*150;
			printf("distance=%d;",distance);
			have_distance=1;
		}
	}
	pclose(fp);
	if(have_distance==0)
	{
		printf("distance=;");
	}
	//----------------------------has fake sta?--------------------------
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"wlanconfig ath%d list 2>/dev/null",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strstr(buf,"/0M"))
		{
			fakesta++;
		}
	}
	pclose(fp);
	//------------connection-----------------------------------------
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"wlanconfig ath%d list 2>/dev/null",ivap);
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strlen(buf)<10)
			continue;
		connection++;
	}
	pclose(fp);
	if(connection>0)
		connection--;
	if(fakesta==connection)
		printf("connection=0;");
	else
	{
		if(connection-fakesta>=0)
			printf("connection=%d;",connection-fakesta);
		else
			printf("connection=0;");
	}
	//-------------time----------------------------------------------	
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"date|sed \"s/ \\{1,\\}/,/g\" 2>/dev/null");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(buf[0]!=0)
			printf("time=%s;",trim(buf));
	}
	/*
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"cat /proc/tdma 2>/dev/null");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
	memset(buf,0,sizeof(buf));
	fgets(buf,sizeof(buf),fp);
	if(buf[0]!=0)
	{
	printf("tdma=%s;",trim(buf));
	have_tdma=1;
	}
	}
	pclose(fp);
	if(have_tdma==0)
	{
	printf("tdma=;");
	}
	*/
	//-------------get wan ip--------------------------------------
	fp=fopen("/dev/mtdblock4","r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strstr(buf,"WAN_IF"))
		{
			memset(wan_if,0,sizeof(wan_if));
			sprintf(wan_if,"%s",buf+strlen("WAN_IF="));
			//printf("wan_if=%s;",wan_if);
			break;
		}
	}
	fclose(fp);
	fp=fopen("/dev/mtdblock4","r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strstr(buf,"AP_IMODE=bridge"))
		{
			is_bridge=1;
			break;
		}
	}
	fclose(fp);
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"ifconfig %s|sed -n \"/inet addr/p\"|sed \"s/ \\{1,\\}/X/g\"|cut -d 'X' -f 3|sed \"s/addr://g\"|tr -d '\n'",trim(wan_if));
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(buf[0]!=0)
		{
			if(!is_bridge)
			{
				printf("wanip=%s;",trim(buf));
				have_wanip=1;
			}
			break;
		}
	}
	pclose(fp);
	if(have_wanip==0)
	{
		printf("wanip=;");
	}
	//-------------------wan mac------------------------------------
	fp=fopen("/dev/mtdblock4","r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(strstr(buf,"WAN_IF"))
		{
			memset(wan_if,0,sizeof(wan_if));
			sprintf(wan_if,"%s",buf+strlen("WAN_IF="));
			//printf("wan_if=%s;",wan_if);
			break;
		}
	}
	fclose(fp);
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"ifconfig %s|sed -n \"/HWaddr/p\"|sed \"s/ \\{1,\\}/X/g\"|cut -d 'X' -f 5|tr -d '\n'",trim(wan_if));
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if(buf[0]!=0)
		{
			printf("wanmac=%s;",trim(buf));
			have_wanmac=1;
			break;
		}
	}
	pclose(fp);
	if(have_wanmac==0)
	{
		printf("wanmac=;");
	}
	//return 0;
	//-------------------80211 mode------------------------------------
/*
	if(ivap == 0){
		printf("80211mode=%s;","bgn");
	}else{
		memset(cmd,0,sizeof(cmd));
		sprintf(cmd,"iwconfig ath%d|sed -n \"/802.11/p\" 2>/dev/null",ivap);
		fp=popen(cmd,"r");
		while(!feof(fp))
		{
			memset(buf,0,sizeof(buf));
			fgets(buf,sizeof(buf),fp);
			if(strstr(buf,"802.11na")){
				printf("80211mode=%s;","11an");break;
			}else if(strstr(buf,"802.11ac")){


				FILE *fp_2=NULL;
				memset(cmd,0,sizeof(cmd));
				sprintf(cmd,"iwpriv ath%d get_pure11ac|sed -n \"/get_pure11ac:/p\" 2>/dev/null",ivap);
				fp_2=popen(cmd,"r");
				while(!feof(fp_2))
				{
					memset(buf,0,sizeof(buf));
					fgets(buf,sizeof(buf),fp_2);
					if(strstr(buf,"get_pure11ac:0"))
					{
						printf("80211mode=%s;","11an11ac");break;
					}else if(strstr(buf,"get_pure11ac:1"))
					{
						printf("80211mode=%s;","11ac");break;
					}
				}
				pclose(fp_2);break;
			}
		}
		pclose(fp);
	}
*/

    have_value = 0;
	if(1){
		memset(cmd,0,sizeof(cmd));
		sprintf(cmd,"iwpriv ath%d get_mode |sed -n \"/get_mode:/p\" |sed \"s/.*get_mode://g\" 2>/dev/null", ivap);
		fp=popen(cmd,"r");
		while(!feof(fp))
		{
			memset(buf,0,sizeof(buf));
			fgets(buf,sizeof(buf),fp);
            if(buf[0]!=0){
			    printf("80211mode=%s;",trim(buf));
                have_value = 1;
                break;
            }
		}
        if(have_value == 0){
		    printf("80211mode=;");
        }
		pclose(fp);
	}
	//-------------------tdma info------------------------------------
	if(ivap == 0){
		printf("tdma=%s;","0");
	}else{
		memset(cmd,0,sizeof(cmd));
		sprintf(cmd,"iwpriv wifi1 get_tdma_en|sed -n \"/get_tdma_en/p\" 2>/dev/null");
		fp=popen(cmd,"r");
		while(!feof(fp))
		{
			memset(buf,0,sizeof(buf));
			fgets(buf,sizeof(buf),fp);
			if(strstr(buf,"get_tdma_en:0"))
			{
				printf("tdma=%s;","0");break;
			}else if(strstr(buf,"get_tdma_en:1"))
			{
				printf("tdma=%s;","1");break;
			}
		}
		pclose(fp);
	}
	//-------------------ap_mode info------------------------------------
	fp=fopen("/dev/mtdblock4","r");
	char ap_mode[512];
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		if( ivap == 0 ){
			if(strstr(buf,"WIRELESS_MODE=")){
		        memset(ap_mode,0,sizeof(ap_mode));
				snprintf(ap_mode, strlen(buf)-strlen("WIRELESS_MODE="), "%s", buf+strlen("WIRELESS_MODE="));
			}else if(strstr(buf,"AP_STARTMODE=repeater")){
		        memset(ap_mode,0,sizeof(ap_mode));
				sprintf(ap_mode, "%s", "repeater");break;
			}
		}else{
			if(strstr(buf,"WIRELESS_MODE_2=")){
		        memset(ap_mode,0,sizeof(ap_mode));
				snprintf(ap_mode, strlen(buf)-strlen("WIRELESS_MODE_2="), "%s", buf+strlen("WIRELESS_MODE_2="));
			}else if(strstr(buf,"AP_STARTMODE_2=repeater")){
		        memset(ap_mode,0,sizeof(ap_mode));
				sprintf(ap_mode, "%s", "repeater");break;
			}
		}
	}	
	printf("apmode=%s;",ap_mode);
	fclose(fp);
	return 0;
}

