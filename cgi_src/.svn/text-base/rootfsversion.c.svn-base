#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char cmd[64];
	char buf[512];
    char rootfsversion[512];
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"cat /etc/rootfsversion 2>/dev/null");
	//sprintf(cmd,"cat ./ztang 2>/dev/null");
	fp=popen(cmd,"r");
	while(!feof(fp))
	{
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),fp);
        if(buf[0]!=0){
            sscanf(buf, "%*[^_]_%s", rootfsversion);
			//printf("%s", buf);
            printf("%s", rootfsversion);
        }
	}	
	pclose(fp);
	return 0;
}
