#include <sys/types.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>
char *convertip(char *buf);
char *convertid(char *buf);



int main(int argc, char *argv[])  
{  
    FILE   *stream;  
    FILE   *wstream;
    int  count = 0,i = 0,j = 0,k = 0,flag = 0,count1 = 0,count2 = 0;
    char buf[128];
    char str[128];
    char *strid[40];
    char *strip[40];
    char stringid[40][6];
    char stringip[40][18];
    memset(str, 0, 128);
    memset(buf, 0, 128);
    if( argc > 2)
    {	
	if(*argv[5] == '0')
	{
		sprintf(str,"iperf -c %s -i %s -P %s -t %s 2>&1",argv[1],argv[2],argv[3],argv[4]);
		stream = popen(str, "r");
	}
	else
	{
		sprintf(str,"iperf -c %s -i %s -P %s -t %s -d 2>&1",argv[1],argv[2],argv[3],argv[4]);
                stream = popen(str, "r");
	}
    }
    else if(argc == 2)
    {
	sprintf(str,"iperf -s -i %s",argv[1]);
	stream = popen(str, "r");
    }
    else
    {
	stream = popen( "iperf -s", "r" );
    }
    wstream = fopen( "/tmp/iperflog", "w+");

    while(!feof(stream))
    {	
	 if(count == 16)
        {
                fseek(wstream,0L,SEEK_SET);
                count = 0;
        }
	fgets(buf,128,stream);
	i = strlen(buf);
	if(buf[0] == '[' &&  i > 60)
	{
		if(j == 39)
		{
			j = 0;
			flag = 1;
		}
		strip[j] = convertip(buf);
		strid[j] = convertid(buf);
		strcpy(stringip[j],strip[j]);
		strcpy(stringid[j],strid[j]);
//		printf("%s\n",stringip[j]);
//		printf("%s\n",stringid[j]);
		j++;
	}
	if(buf[0] == '[' && buf[1] != 'S' && i >= 49 && i <= 60)
	{
	count1 = i;
	buf[5] = '\0';
	if(flag == 0)
	{
	for(i = 0;i <= j;i++)
	{
		if(strcmp(buf,stringid[i]) == 0)
		{	
			k = strlen(stringip[i]);
			fputs(stringip[i],wstream);
			count2 = count1 + k;
			break;
		}
	}
	}
	else
	{
	for(i = 0;i <= 39;i++)
	{
		if(strcmp(buf,stringid[i]) == 0)
		{	
			k = strlen(stringip[i]);
			fputs(stringip[i],wstream);
			count2 = count1 + k;
			break;
		}
	}	
	}
	for( count2;count2 < 80;count2++)
	{
	buf[count1-1] = ' ';
	count1++;
	}
	buf[count1-1] = '\n';
//	printf("%s",buf+6);
	fputs(buf+6,wstream);
	fflush(wstream);
	memset(buf, 0, 128);
	count += 1;
	}
	else if(buf[0] == 'c')
	{
	fputs(buf,wstream);
        fflush(wstream);
        memset(buf, 0, 128);
	break;
	}
	else
	{
	memset(buf, 0, 128);
	continue;		
	}
     }

    pclose( stream );  
    fclose( wstream );
    
    return 0;
}   

char *convertip(char *buf)
{
	char *p;
	char *p1;
	p = strstr(buf,"with ");
	p = p+5;
	p1 = p;
	while(*p != ' ')
	{
		p++;
	}
	*p++ = ' ';
	*p++ = ' ';
	*p = '\0';
	return p1;
}
char *convertid(char *buf)
{
	char *p;
	char *p1;
	p = strchr(buf,'[');
	p1 = p;
	while(*p != ']')
	{
		p++;
	}
	*p++ = ']';
	*p = '\0';
	return p1;
}
