#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *f=NULL;
	u_int32_t sync=0;
	int devflag=0;
	f=fopen("/dev/nvram","r");
	if(f)
	{
		fread(&sync,4,1,f);
		fclose(f);
	}
	else
	{
		f=fopen("/dev/mtdblock4","r");
		if(f)
		{
			fread(&sync,4,1,f);
			fclose(f);
			devflag=1;
		}
		else
		{
			return 1;
		}
	}
	printf("%x\n",sync);
	if(sync!=0xfaf30021)
	{
		if(devflag==0)
		{
			system("dd if=/etc/ath/.apcfg of=/dev/nvram");
		}
		else
		{
			system("dd if=/etc/ath/.apcfg of=/dev/mtdblock4");
		}
		system("echo \"1\">/etc/ath/checkfactory");
	}
	else
	{
		system("rm /etc/ath/checkfactory");
	}
	return 0;
}
