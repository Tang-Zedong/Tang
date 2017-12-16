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
	char cmd[512];
	char buf[512];
	int i=0;
	int is_tb5ca=0;
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"date +'%%Y-%%m-%%d %%H:%%M:%%S'");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
                fgets(buf,sizeof(buf),fp);
                if(buf[0]!=0)
                        printf("%s",trim(buf));
	}	
	pclose(fp);
	return 0;
}
