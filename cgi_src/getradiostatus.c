#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int radio_on = 0;
    int radio_on_2 = 0;
    char cmd[512];
    char buf[512];
    int i=0;
    FILE *fp=NULL;
    printf("Content-Type: text/html\r\n\r\n");
    fp=fopen("/dev/mtdblock4","r");
    while(!feof(fp))
    {
        memset(buf,0,sizeof(buf));
        fgets(buf,sizeof(buf),fp);
        if(strstr(buf,"RADIO_ON=1")){
            radio_on = 1;
        }
        if(strstr(buf,"RADIO_ON_2=1"))
        {
            radio_on_2 = 1;
        }
    }
    printf("%d,%d;", radio_on, radio_on_2);
    pclose(fp);
    return 0;
}
