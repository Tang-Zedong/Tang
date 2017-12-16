#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	char *pquerystring,*pstart,*pstr;
	char dual[8];
	char server[32];
	char thread[8];
	char testtime[12];
	char interval[8];
	char cmd[128];
	int  count = 0;
	char buf[128];
	memset(buf,0,128);
	pquerystring=getenv("QUERY_STRING"); 
//	printf(---------------------%s-------------------\n",pquerystring);
	pstart=strstr(pquerystring,"dual=");

		pstr=pstart;
		while(*pstr != '\0')
		{
        		if(*pstr == '&')
			{
				*pstr = ' ';
			}
        		pstr++;
		} 
//		printf("---------------------%s-------------------\n",pstart);
		memset(dual,0,sizeof(dual));
		memset(server,0,sizeof(server));
		memset(thread,0,sizeof(thread));
		memset(testtime,0,sizeof(testtime));
		memset(interval,0,sizeof(interval));
        	memset(cmd,0,sizeof(cmd));
		//system("killall -9 iperf");
		//system("killall -9 iperflog");
		system(">/tmp/iperflog");
		sscanf(pstart,"dual=%s server=%s thread=%s testtime=%s interval=%s",dual,server,thread,testtime,interval);
//		printf("---------------------%s\t%s\t%s\t%s\t%s\t-------------------\n",dual,server,thread,testtime,interval);
	        sprintf(cmd,"iperflog %s %s %s %s %s",server,interval,thread,testtime,dual);
		system(cmd);	
		return 0;
}
