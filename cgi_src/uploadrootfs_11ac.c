/*******************************************************************************
* Firemware Upgrade CGI
******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/reboot.h>
#include<sys/param.h>
#include<sys/types.h>
#include <sys/signal.h>
#include "mkimage.h"


char* trim(char strings[])
{
	int i=0;
	while(strings[i]!='\0'&&strings[i]!='\n'&&strings[i]!='\r'&&strings[i]!='\t')
		i++;
	strings[i]='\0';
	return strings;
}

#define RET_OK              0
#define RET_GENERNAL_ERR    -1
#define RET_OPEN_ERR        -2
#define LEN_MD5             36

#define GOTO_ERR(_code) do {                    \
	ret_val = (_code);  \
	goto _end;      \
}while(0);
#define IMAGE_ERR {\
	printf("\r\n");\
	fp=fopen("/usr/www/firmerror.html","r");\
	while(!feof(fp))\
{	\
	memset(waitbuf,0,1024);\
	fgets(waitbuf,1024,fp);\
	printf("%s",waitbuf);\
}\
	fclose(fp);\
	free(ucpbuf);\
	ucpbuf=NULL;	\
	GOTO_ERR(RET_GENERNAL_ERR);\
};

#define NUM_B 10
#define NUM_M 20

char *brand_table[NUM_B][NUM_M] = {\
{"dahua", "DH-PFM880E", "DH-PFM886-10", "DH-PFM886-20", "DH-PFM880-M", "DH-PFM885-I", "DH-PFM889-I", "DH-PFM889-IM"},\
{"haikang", "DS-3WF05C-5AC", "DS-3WF05A-5AC", "DS-3WF10A-5AC", "DS-3WF20A-5AC", "DS-3WF03C-25AC", "DS-3WF01C-2N"},\
{"yushi", "WLN-EB5HD-29E"},\
{"jinshi", "TB5J-JINSHI"},\
{"creatcomm", "TB5HP-18I", "TB5HS-17E", "TB5HP-25I", "TB5HD-29E", "TB8H", "TB2I", "TA2I", "TA8H"}\
};

int main()
{
	unsigned long lconlen=0;
	FILE *fp=NULL;
	unsigned char *ucpbuf=NULL;
	char cboundary[128];
	char cfilename[64];
	char cfullfilename[64];
	char cmd[128];
	char *cpstart=NULL;
	char *cpstop=NULL;
	char *cpubootstop=NULL;
	pid_t ret_pid=-1;
	int i=0;
	int j=0;
	char waitbuf[1024];
	char cubootlen[8];
	int iubootlen=0;
	int ret_val = 0;

	char str_type_node[8];
	char str_len_value[16];
	char str_value[4096];
	char str_board[4096];
	char str_brand[4096];
	char str_hardware[4096];
	char str_device_type[4096];
	char str_device_type_2[4096];
	char str_device_tmp[4096];

	unsigned int len_value = 0;
	unsigned int len_uboot = 0;
	unsigned int len_rootfs = 0;
	unsigned int len_kernel = 0;
	unsigned int len_device_type = 0;

	void *p_start;
	void *p_end;

	fp=fopen("/etc/rootfsversion","r");
	if(fp==NULL)
		GOTO_ERR(RET_GENERNAL_ERR);
	fseek(fp, 0L, SEEK_END);
	len_device_type = ftell(fp);
	if(len_device_type <= 0)
		GOTO_ERR(RET_GENERNAL_ERR);
	fseek(fp, 0L, SEEK_SET);
	if(len_device_type > sizeof(str_device_type)){
		fread(str_device_type,sizeof(str_device_type),1,fp);
	}else{
		fread(str_device_type,len_device_type,1,fp);
	}
	fclose(fp);
	fp = NULL;

	memset(str_device_type_2, 0, sizeof(str_device_type_2));
	strcpy(str_device_type_2, "!11AC");

	fp=fopen("/mnt/.rootfsversion","r");
	if(fp!=NULL){
		fseek(fp, 0L, SEEK_END);
		len_device_type = ftell(fp);
		if(len_device_type <= 0){
			memset(str_device_type_2, 0, sizeof(str_device_type_2));
			strcpy(str_device_type_2, "!11AC");
			fclose(fp);
		}else{        
			memset(str_device_type_2, 0, sizeof(str_device_type_2));
			fseek(fp, 0L, SEEK_SET);
			if(len_device_type > sizeof(str_device_type)){
				fread(str_device_type_2,sizeof(str_device_type_2),1,fp);
			}else{
				fread(str_device_type_2,len_device_type,1,fp);
			}
			fclose(fp);
		}
	}
    if(strstr(str_device_type_2, "!11AC") != NULL){
		memset(str_device_tmp, 0, sizeof(str_device_tmp));
		strcpy(str_device_tmp, "!11AC");
		if(strlen(str_device_type) > 0){
			i = 0; j =0;
			for(i=0; i < NUM_B; i++){
				for(j=0; j < NUM_M; j++){
					if(brand_table[i][j] == NULL) break;
					if(strstr(str_device_type, brand_table[i][j]) != NULL){
						memset(str_device_tmp, 0, sizeof(str_device_tmp));
						strcpy(str_device_tmp, brand_table[i][0]);
						break;
					}
				}
				if(strstr(str_device_tmp, "!11AC") == NULL){
					sprintf(str_device_type_2, "%s:%s", str_device_tmp, strstr(str_device_type, "_")+1);
					break;
				}
			}
		}
	}
	fp = NULL;

	system("rm /tmp/TB-v*");
	lconlen=atoi(getenv("CONTENT_LENGTH"));
	if(lconlen<=0)
	{
		GOTO_ERR(RET_GENERNAL_ERR);
	}
	ucpbuf=(unsigned  char*)malloc(lconlen+1);
	fread(ucpbuf,lconlen,1,stdin);
	cpstart=ucpbuf;
	cpstop=ucpbuf;
	while(*cpstop!='\r'&&cpstop<(ucpbuf+lconlen))
		cpstop++;
	memset(cboundary,0,sizeof(cboundary));
	memcpy(cboundary,cpstart,(cpstop-cpstart));
	while(strncmp(cpstart,"filename=",strlen("filename="))!=0&&cpstart<(ucpbuf+lconlen))
		cpstart++;
	cpstart=cpstart+strlen("filename=")+1;
	cpstop=cpstart;
	if(*(cpstart+1)==':'&&*(cpstart+2)=='\\')
	{
		while(*cpstop!='\"'&&cpstop<(ucpbuf+lconlen))
			cpstop++;
		cpstart=cpstop;
		while(*cpstart!='\\'&&cpstart<(ucpbuf+lconlen))
			cpstart--;
		cpstart++;
	}
	else
	{
		while(*cpstop!='\"'&&cpstop<(ucpbuf+lconlen))
			cpstop++;
	}
	memset(cfilename,0,sizeof(cfilename));
	memcpy(cfilename,cpstart,cpstop-cpstart);
	while(strncmp(cpstart,"Content-Type: application/octet-stream",strlen("Content-Type: application/octet-stream"))!=0&&cpstart<(ucpbuf+lconlen))
		cpstart++;
	cpstart=cpstart+strlen("Content-Type: application/octet-stream")+4;
	cpstop=cpstart;
	while(strncmp(cpstop,cboundary,strlen(cboundary))!=0&&cpstop<(ucpbuf+lconlen))
		cpstop++;
	cpstop=cpstop-2;
	if(cpstart>=(ucpbuf+lconlen))
	{
		free(ucpbuf);
		ucpbuf=NULL;
		IMAGE_ERR;
		printf("<html><head>\r\n");
		printf("</head><body>\r\n");
		printf("Upload wrong format file!\r\n");
		printf("</body></html>");
		GOTO_ERR(RET_GENERNAL_ERR);
	}
	/*
	if(strstr(cfilename,"TB-v")==NULL)
	{
	printf("<html><head>\r\n");
	printf("</head><body>\r\n");
	printf("File name is wrong!\r\n");
	printf("</body></html>");
	GOTO_ERR(RET_GENERNAL_ERR);
	}
	*/
	//getinfo from image head
	p_start = (void*)(cpstart)+LEN_MD5;
	p_end = p_start;
	{
		memset(str_type_node, 0, sizeof(str_type_node));
		memset(str_len_value, 0, sizeof(str_len_value));
		memset(str_value, 0, sizeof(str_value));
		strncpy(str_type_node, p_start, sizeof(str_type_node));
		p_start += 8;
		strncpy(str_len_value, p_start, sizeof(str_len_value));
		p_start += 16;
		len_value = atoi(str_len_value);
		strncpy(str_value, p_start, sizeof(str_value));
		p_start += len_value;

		if((strcmp(str_type_node, HEAD) != 0) || (strcmp(str_value, DATA_HEAD) != 0)){
			IMAGE_ERR;
		}

		p_start = (void*)(cpstart)+LEN_MD5;
		p_end = p_start;

		int count_node = 0;
		while(1){
			count_node += 1;
			if(count_node > 100){
				IMAGE_ERR;
			}

			memset(str_type_node, 0, sizeof(str_type_node));
			memset(str_len_value, 0, sizeof(str_len_value));
			memset(str_value, 0, sizeof(str_value));
			strncpy(str_type_node, p_start, sizeof(str_type_node));
			p_start += 8;
			strncpy(str_len_value, p_start, sizeof(str_len_value));
			p_start += 16;
			len_value = atoi(str_len_value);
			strncpy(str_value, p_start, sizeof(str_value));
			p_start += len_value;

			if((strcmp(str_type_node, END) == 0) && (strcmp(str_value, DATA_END) == 0)){
				break;
				p_end = p_start+len_uboot+len_rootfs+len_kernel;
				printf("len_image=      %d\n",p_end-p_start);
				printf("len_uboot=      %d\n",len_uboot);
				printf("len_rootfs=     %d\n",len_rootfs);
				printf("len_kernel=     %d\n",len_kernel);
				break;

			}else if(strcmp(str_type_node, UBOOT) == 0){
				len_uboot = atoi(str_value);
				continue;
			}else if(strcmp(str_type_node, ROOTFS) == 0){
				len_rootfs = atoi(str_value);
				continue;
			}else if(strcmp(str_type_node, KERNEL) == 0){
				len_kernel = atoi(str_value);
				continue;
			}else if(strcmp(str_type_node, BRAND) == 0){
				strcpy(str_brand,str_value);
				continue;
			}else if(strcmp(str_type_node, BOARD) == 0){
				strcpy(str_board,str_value);
				continue;
			}else if(strcmp(str_type_node, HW) == 0){
				strcpy(str_hardware,str_value);
				continue;
			}
		}
		if(((len_kernel <= 0) || (len_rootfs <= 0)) && (len_uboot <= 0)){
			IMAGE_ERR;
		}
		if( strstr(str_device_type_2, "!11AC") != NULL ){
			if(strstr(str_device_type, str_board) == NULL){
				IMAGE_ERR;
			}else if(strstr(str_device_type, str_hardware) == NULL){
				IMAGE_ERR;
			}

		}else{
			if((strstr(str_device_type_2, str_brand) == NULL) && (strstr(str_device_type_2, str_board) == NULL)){
				IMAGE_ERR;
			}
            if(strlen(str_brand) == 0){
			    if(strstr(str_device_type, str_board) == NULL){
				    IMAGE_ERR;
			    }else if(strstr(str_device_type, str_hardware) == NULL){
				    IMAGE_ERR;
			    }
            }
			sprintf(cmd, "echo \"%s\" > /mnt/.rootfsversion 2>&1", str_device_type_2);
			//system(cmd);
		}
	}

	memset(cfullfilename,0,sizeof(cfullfilename));
	sprintf(cfullfilename,"/tmp/%s",cfilename);
	fp=fopen(cfullfilename,"w");
	if(fp==NULL)
		GOTO_ERR(RET_GENERNAL_ERR);
	fwrite(cpstart,(cpstop-cpstart),1,fp);
	fclose(fp);
	memset(cmd,0,sizeof(cmd));

	sprintf(cmd, "fw_upgrade -v %s", cfullfilename);
	ret_val = system(cmd);

	if(ret_val !=0)
	{
		printf("\r\n");
		fp=fopen("/usr/www/firmerror.html","r");
		while(!feof(fp))
		{
			memset(waitbuf,0,1024);
			fgets(waitbuf,1024,fp);
			printf("%s",waitbuf);
		}
		fclose(fp);
		free(ucpbuf);
		ucpbuf=NULL;
		GOTO_ERR(RET_GENERNAL_ERR);
	}

	free(ucpbuf);
	ucpbuf=NULL;

	ret_pid=fork();
	if(ret_pid==-1)
	{
		printf("Update firmware failed!\n");
		exit(-1);
	}
	else if(ret_pid==0)
	{
		system("echo \"0\">/mnt/modify_flag");
		setsid();
		for(i=0;i<NOFILE;i++)
			close(i);

		sprintf(cmd, "cp -fr /bin/fw_upgrade /tmp");
		system(cmd);
		// sleep 3 for waiting push page to browser
		sleep(3);
		sprintf(cmd, "/tmp/fw_upgrade -f %s &", cfullfilename);
		system(cmd);
	}
	else
	{
		fp=fopen("/etc/ath/en_ch_mode.conf","r");
		memset(waitbuf,0,1024);
		fgets(waitbuf,1024,fp);
		fclose(fp);
		trim(waitbuf);
		if(strcmp(waitbuf,"System_Settings")==0)
		{
			system("/bin/cp /usr/www/Wait_ori.html /usr/www/Wait.html -fr");
		}
		else
		{
			system("/bin/cp /usr/www/Wait_ori.html /usr/www/Wait.html -fr");
			system("/bin/sed -i 's/enchmode=\"System_Settings\";/enchmode=\"System_Settings_EN\";/'  /usr/www/Wait.html");
		}
		printf("\r\n");
		fp=fopen("/usr/www/Wait.html","r");
		while(!feof(fp))
		{
			memset(waitbuf,0,1024);
			fgets(waitbuf,1024,fp);
			printf("%s",waitbuf);
		}
		fclose(fp);
	}
_end:
	return ret_val;
}
