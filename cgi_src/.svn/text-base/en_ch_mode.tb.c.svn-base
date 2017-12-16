#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	char cmd[64];
	char buf[512];
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"cat /etc/ath/en_ch_mode.conf 2>/dev/null");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
		trim(buf);
		if(buf[0]!=0)
			printf("%s;",buf);
	}	
	pclose(fp);
/*	
	memset(cmd,0,sizeof(cmd));
        sprintf(cmd,"iwpriv ath0 get_mode 2>/dev/null|sed \"s/ \\{1,\\}/:/g\"|cut -d ':' -f 3");
        fp=popen(cmd,"r");
        while(!feof(fp))
        {
                memset(buf,0,sizeof(buf));
                fgets(buf,sizeof(buf),fp);
                trim(buf);
                if(buf[0]!=0)
                        printf("%s;",buf);
        } 
        pclose(fp);
*/
	return 0;
}
