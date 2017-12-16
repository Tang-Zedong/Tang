#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int narg,char* varg[])
{
	char buf[1024];
	int i=0;
	if(narg<2)
	{
		printf("usage: trim string\n");
		exit(1);
	}
	memset(buf,0,sizeof(buf));
	for(i=0;i<sizeof(buf);i++)
	{
		if(varg[1][i]!='\0'&&varg[1][i]!='\n'&&varg[1][i]!='\r'&&varg[1][i]!='\t')
			buf[i]=varg[1][i];
		else
		{
			buf[i]='\0';
			break;
		}
	}
	printf("%s",buf);
}
