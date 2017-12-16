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
	char language[512];
	char buf[512];
	FILE *fp=NULL;
	printf("Content-Type: text/html\r\n\r\n");
	fp=fopen("/dev/mtdblock4","r");
        while(!feof(fp))
        {
                memset(buf,0,sizeof(buf));
                fgets(buf,sizeof(buf),fp);
                if(strstr(buf,"WEB_LANGUAGE"))
                {
                        memset(language,0,sizeof(language));
                        sprintf(language,"%s",buf+strlen("WEB_LANGUAGE="));
                        break;
                }
       }
       fclose(fp);
       printf("%s",trim(language));
       return 0;
}
