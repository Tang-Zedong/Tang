#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PARAMETER_LEN 8


int main()
{

    char *pstart=NULL;
    char *pend=NULL;
    char *qdata=NULL;
    char *qstart=NULL;
    char *qend=NULL;
    char cvap[PARAMETER_LEN];
    int ivap=0;
    int para_len=0;

    char cmd[512];
    char buf[4096];
    int i=0;
    FILE *fp=NULL;
    printf("Content-Type: text/html\r\n\r\n");

    //----------------------get parameter----------------------------
    qdata=getenv("QUERY_STRING");
    if(qdata != NULL)
    {
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
        }else{
            ivap=1;
        }
    }else{
        ivap=1;
    }
    ivap-=1;


    memset(cmd,0,sizeof(cmd));
    if(ivap != 0){
        sprintf(cmd,"iwpriv wifi1 getCountryID|sed \"s/.*ID://g\"|sed \"s/ //g\"|tr -d '\n'");
    }else{
        sprintf(cmd,"iwpriv wifi0 getCountryID|sed \"s/.*ID://g\"|sed \"s/ //g\"|tr -d '\n'");
    }
    fp=popen(cmd,"r");
    memset(buf,0,sizeof(buf));
    fgets(buf,sizeof(buf),fp);
    printf("%s;",buf);
    pclose(fp);

    memset(cmd,0,sizeof(cmd));
    if(ivap != 0){
        sprintf(cmd,"cat /etc/ath/ath.conf|sed -n \"/FREQUENCY_2/p\" |sed \"s/RT2_FREQUENCY_2=//g\"");
    }else{
        sprintf(cmd,"cat /etc/ath/ath.conf|sed \"s/FREQUENCY_2//g\"|sed -n \"/FREQUENCY/p\" |sed \"s/RT2_FREQUENCY=//g\"");
    }
    fp=popen(cmd,"r");
    while(!feof(fp))
    {
        memset(buf,0,sizeof(buf));
        fgets(buf,sizeof(buf),fp);
        printf("%s",buf);
    }
    pclose(fp);
    return 0;
}
