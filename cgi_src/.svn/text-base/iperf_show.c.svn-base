#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
		FILE *fp = fopen("/tmp/iperflog","r");
		int count = 0;
		char buf[128];
		char buf1[128];
		char buf2[20];
		char buf3[8];	
		char *pbuf;
		char *pbuf1;
		char *pbuf2;
		int i = 0,j = 0,k = 0;
		float num;
		memset(buf,0,128);
		memset(buf1,0,128);
		memset(buf2,0,20);
		memset(buf3,0,8);
		if(fp == NULL)
		{
			printf("Content-Type: text/html\r\n\r\n");
			printf("open file error\n");
			exit(1);	
		}
		else
		{
			printf("Content-Type: text/html\r\n\r\n");
			while(count < 16)
			{
				
				fgets(buf,128,fp);
				if(buf[0] == 'c')
				{
				printf("%s",buf);
				break;
				}
				if(feof(fp))
				{
					break;
				}
				pbuf = buf;
				pbuf1 = buf1;
				j = 0;
				k = 0;
				for(i = 0;i < 3;i++)
				{
				while(!(*pbuf == ' ' && *(pbuf+1) == ' '))
				{
					*pbuf1++ = *pbuf;
					if(i == 1)
					{
						buf2[j++] = *pbuf;
					}
					pbuf++;
				}
				*pbuf1++ = ',';
				pbuf = pbuf + 2;
				}
				buf2[j] = '\0';
			//	printf("%s\n", buf2);
				while(!(*pbuf == ' ' && *(pbuf+1) == ' '))
                                {
                                        *pbuf1++ = *pbuf++;
                                }
				
				*pbuf1++ = ',';
				pbuf2 = strstr(buf2," 0.0-");
				if( pbuf2)
				{
					pbuf2 = pbuf2 + 5;
				if(*pbuf2 == ' ')
				{
					pbuf2++;
				}
				while(*pbuf2 != ' ')
				{
					buf3[k++] = *pbuf2++;  
				}
				buf3[k] = '\0';
			//	printf("---------------------------------%s--------------------------\n",buf3);
				num = atof(buf3);
			//	printf("---------------------------------%d--------------------------\n",num);
			//	if(count == 0)
			//	{
			//		inter = num;			
			//	}
					if(num > 9.0)
					{
					strcpy(pbuf1,"sum");
					pbuf1 = pbuf1+3;
					}
					else
					{
					strcpy(pbuf1,"nosum");
					pbuf1 = pbuf1 +5;	
					}
				}
				else
				{
					strcpy(pbuf1,"nosum");
					pbuf1 = pbuf1 +5;
				}
				*pbuf1++ = ';';
				*pbuf1 = '\0';
				printf("%s",buf1); 
				memset(buf,0,128);
				memset(buf1,0,128);
				memset(buf2,0,20);
				memset(buf3,0,8);
				count++ ;
			}
			
		}
		fclose(fp);
		return 0;
}
