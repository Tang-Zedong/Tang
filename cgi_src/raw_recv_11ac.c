#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if.h>
#include <linux/in.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/reboot.h>


#include <pthread.h>
#include "raw_massupdate.h"

/*
#define BUFFER_MAX 1500
#define JACKY_DEBUG 0
*/
struct head_size
{
	unsigned long size_image_all;
	unsigned long size_data_send;
};



unsigned char remote_mac[ETH_HLEN];
unsigned char eth0_mac[ETH_HLEN];
char imageversion[MAXIMAGEVERSION_LEN];
volatile int discover_run=1;
struct sockaddr_ll sockaddr_ll_recv;

int discover_send(int sock)
{
	int sock_send;
	char send_buffer[BUFFER_MAX];
	struct ethhdr *eth_head_send;
	struct sockaddr_ll sockaddr_ll_send;
	char *payload_send=NULL;
	int payload_send_len=0;
	int send_len=0;
	int ret_send=0;
	int send_count=0;
	sock_send=sock;
	memcpy(&sockaddr_ll_send,&sockaddr_ll_recv,sizeof(sockaddr_ll_send));
	memset(send_buffer,0,sizeof(send_buffer));
	payload_send=send_buffer+ETH_HLEN;
	eth_head_send=(struct ethhdr *)send_buffer;

	eth_head_send->h_dest[0]=0xFF;
	eth_head_send->h_dest[1]=0xFF;
	eth_head_send->h_dest[2]=0xFF;
	eth_head_send->h_dest[3]=0xFF;
	eth_head_send->h_dest[4]=0xFF;
	eth_head_send->h_dest[5]=0xFF;
	memcpy(eth_head_send->h_source,eth0_mac,ETH_HLEN);
	payload_send_len=sprintf(payload_send,"%s",discoverstr);
	payload_send_len+=sprintf(payload_send+strlen(discoverstr),"%s",imageversion);
	eth_head_send->h_proto=htons(payload_send_len);
	send_len=payload_send_len+ETH_HLEN;
	sendto(sock_send,send_buffer,send_len,0,(struct sockaddr *)(&sockaddr_ll_send),sizeof(sockaddr_ll_send));
	//sendto(sock_send,send_buffer,send_len,0,(struct sockaddr *)(&sockaddr_ll_recv),sizeof(sockaddr_ll_recv));
}

int discover_thread(int sock)
{
	int sock_send;
	char send_buffer[BUFFER_MAX];
	struct ethhdr *eth_head_send;
	struct sockaddr_ll sockaddr_ll_send;
	char *payload_send=NULL;
	int payload_send_len=0;
	int send_len=0;
	int ret_send=0;
	int send_count=0;
	sock_send=sock;
	memcpy(&sockaddr_ll_send,&sockaddr_ll_recv,sizeof(sockaddr_ll_send));
	memset(send_buffer,0,sizeof(send_buffer));
	payload_send=send_buffer+ETH_HLEN;
	eth_head_send=(struct ethhdr *)send_buffer;

	eth_head_send->h_dest[0]=0xFF;
	eth_head_send->h_dest[1]=0xFF;
	eth_head_send->h_dest[2]=0xFF;
	eth_head_send->h_dest[3]=0xFF;
	eth_head_send->h_dest[4]=0xFF;
	eth_head_send->h_dest[5]=0xFF;
	memcpy(eth_head_send->h_source,eth0_mac,ETH_HLEN);
	payload_send_len=sprintf(payload_send,"%s",discoverstr);
	payload_send_len+=sprintf(payload_send+strlen(discoverstr),"%s",imageversion);
	eth_head_send->h_proto=htons(payload_send_len);
	send_len=payload_send_len+ETH_HLEN;
	while(discover_run)
	{
		sendto(sock_send,send_buffer,send_len,0,(struct sockaddr *)(&sockaddr_ll_send),sizeof(sockaddr_ll_send));
		sleep(5);
	}
	//sendto(sock_send,send_buffer,send_len,0,(struct sockaddr *)(&sockaddr_ll_recv),sizeof(sockaddr_ll_recv));
}

int main(int argc, char *argv[])
{
	int sock_getmac;
	int sock_recv;
	char send_buffer[BUFFER_MAX];
	char recv_buffer[BUFFER_MAX];
	struct ethhdr *eth_head_send;
	struct ethhdr *eth_head_recv;
	//	struct sockaddr_ll sockaddr_ll_recv;
	socklen_t addrlen=0;
	struct ifreq ifreq_param_getmac;
	struct ifreq ifreq_param_recv;
	char *payload_send=NULL;
	char *payload_recv=NULL;
	int payload_send_len=0;
	int payload_recv_len=0;
	int send_len=0;
	int recv_len=0;
	fd_set recv_fds;
	struct timeval tv;
	int ret_select=0;
	int ret_getmac=0;
	int ret_send=0;
	int recv_count=0;
	int discover_count=0;
	FILE* fp=NULL;
	pthread_t tid;
	char cmd[128];
	int ret_val = 0;

	struct head_size head_size_send;
	char new_mac[4096];
	char new_version[4096];
	/*
	static char *discoverstr="Creatcomm:Hello jacky! Do you want to firmware update?";
	static char *comfirmstr="Creatcomm:OK! Now,firmware update start!";
	static char *imageprefix="imagedata:";
	static char *imageendstr="Creatcomm:Your image is sent!Please check and update!";
	static char *imagemd5okstr="Creatcomm:Your image md5 is OK!";
	static char *imagemd5errstr="Creatcomm:Your image md5 is error!";
	static char *recv_imagename="recv_image";
	*/
	fp=fopen("/etc/rootfsversion","r");
	if(!fp)
	{
		printf("Can not get image version!\n");
		exit(-1);
	}
	memset(imageversion,0,sizeof(imageversion));
	fgets(imageversion,sizeof(imageversion),fp);
	fclose(fp);
	fp=NULL;

	//get mac start!
	if((sock_getmac=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		printf("create getmac socket error\n");
		exit(-1);
	}

	memset(&ifreq_param_getmac,0,sizeof(ifreq_param_getmac));
	strcpy(ifreq_param_getmac.ifr_name,"eth0");
	ret_getmac=ioctl(sock_getmac,SIOCGIFHWADDR,&ifreq_param_getmac);
	close(sock_getmac);
	if(ret_getmac==-1)
	{
		printf("get mac failed!\n");
		exit(-2);
	}
	memcpy(eth0_mac,ifreq_param_getmac.ifr_hwaddr.sa_data,ETH_HLEN);
	printf("my mac is %02x:%02x:%02x:%02x:%02x:%02x\n",eth0_mac[0],
		eth0_mac[1],
		eth0_mac[2],
		eth0_mac[3],
		eth0_mac[4],
		eth0_mac[5]);


	//recv start!
	memset(recv_buffer,0,sizeof(recv_buffer));
	payload_recv=recv_buffer+ETH_HLEN;
	eth_head_recv=(struct ethhdr *)recv_buffer;

	if((sock_recv=socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL)))<0)
	{
		printf("create socket error\n");
		exit(-3);
	}

	memset(&ifreq_param_recv,0,sizeof(ifreq_param_recv));
	memset(&sockaddr_ll_recv,0,sizeof(sockaddr_ll_recv));
	strcpy(ifreq_param_recv.ifr_name,"eth0");
	ioctl(sock_recv,SIOCGIFINDEX,&ifreq_param_recv);
	sockaddr_ll_recv.sll_ifindex=ifreq_param_recv.ifr_ifindex;

	bind(sock_recv,(struct sockaddr *)(&sockaddr_ll_recv),sizeof(sockaddr_ll_recv));

	if(pthread_create(&tid,NULL,(void *)discover_thread,(void *)sock_recv)==0)
	{
		pthread_detach(tid);
	}

	printf("send first discover\n");
	discover_send(sock_recv);
	while(1)
	{
		FD_ZERO(&recv_fds);
		FD_SET(sock_recv,&recv_fds);

		tv.tv_sec=5;
		tv.tv_usec=0;
		ret_select=select(sock_recv+1,&recv_fds,NULL,NULL,&tv);
		//ret_select=select(sock_recv+1,&recv_fds,NULL,NULL,NULL);
		if(ret_select<0)
			continue;
		else if(ret_select==0)
		{
			//if(discover_run)
			//	discover_send(sock_recv);
		}
		else
		{
			/*if(discover_run)
			{
			if(discover_count>100)
			{
			discover_send(sock_recv);
			discover_count=0;
			}
			}*/
		}

		if(FD_ISSET(sock_recv,&recv_fds))
		{
			addrlen=sizeof(&sockaddr_ll_recv);
			memset(recv_buffer,0,sizeof(recv_buffer));
			recv_len=recvfrom(sock_recv,recv_buffer,BUFFER_MAX,0,(struct sockaddr *)(&sockaddr_ll_recv),&addrlen);
#if JACKY_DEBUG
			printf("recv ok!\n");
			printf("dest mac:%02x:%02x:%02x:%02x:%02x:%02x\n",eth_head_recv->h_dest[0],
				eth_head_recv->h_dest[1],
				eth_head_recv->h_dest[2],
				eth_head_recv->h_dest[3],
				eth_head_recv->h_dest[4],
				eth_head_recv->h_dest[5]);

			printf("src mac:%02x:%02x:%02x:%02x:%02x:%02x\n",eth_head_recv->h_source[0],
				eth_head_recv->h_source[1],
				eth_head_recv->h_source[2],
				eth_head_recv->h_source[3],
				eth_head_recv->h_source[4],
				eth_head_recv->h_source[5]);
#endif
			if(discover_run==1)
			{
				if(!(eth_head_recv->h_dest[0]==eth0_mac[0]&&
					eth_head_recv->h_dest[1]==eth0_mac[1]&&
					eth_head_recv->h_dest[2]==eth0_mac[2]&&
					eth_head_recv->h_dest[3]==eth0_mac[3]&&
					eth_head_recv->h_dest[4]==eth0_mac[4]&&
					eth_head_recv->h_dest[5]==eth0_mac[5]))
				{
					//	printf("This packet is not wanted!\n");
					continue;
				}//--------------------------------------------
			}
			else
			{
				if(!(eth_head_recv->h_dest[0]==eth0_mac[0]&&
					eth_head_recv->h_dest[1]==eth0_mac[1]&&
					eth_head_recv->h_dest[2]==eth0_mac[2]&&
					eth_head_recv->h_dest[3]==eth0_mac[3]&&
					eth_head_recv->h_dest[4]==eth0_mac[4]&&
					eth_head_recv->h_dest[5]==eth0_mac[5]&&
					eth_head_recv->h_source[0]==remote_mac[0]&&
					eth_head_recv->h_source[1]==remote_mac[1]&&
					eth_head_recv->h_source[2]==remote_mac[2]&&
					eth_head_recv->h_source[3]==remote_mac[3]&&
					eth_head_recv->h_source[4]==remote_mac[4]&&
					eth_head_recv->h_source[5]==remote_mac[5]))
				{
					//	printf("This packet is not wanted!\n");
					continue;
				}//--------------------------------------------
			}
			/*		if(memcmp(payload_recv,comfirmstr,strlen(comfirmstr))==0)
			{
			printf("recv string from server:%s\n",comfirmstr);
			}
			*/
			if(strncmp(payload_recv,comfirmstr,strlen(comfirmstr))==0)
			{
				//memcpy(remote_mac,eth_head_recv->h_source,ETH_HLEN);
				printf("payload_recv=%s\n", payload_recv);
				memset(new_version, 0, sizeof(new_version));
				if(strlen(payload_recv) > strlen(comfirmstr)+strlen("NEW_VERSION:")){
					strcpy(new_version, payload_recv+strlen(comfirmstr)+strlen("NEW_VERSION:"));
				}
				if(strlen(new_version) > 0 ){
					sprintf(cmd, "echo \"%s\" > /mnt/.rootfsversion", new_version);
					system(cmd);
					system("/bin/make_version 2>&1");
                }else{
                    system("rm -rf /mnt/.rootfsversion > /dev/null 2>&1");
                }

				fp=fopen(recv_imagename,"w+");
				if(!fp)
				{
					printf("Can not open file %s !\n",recv_imagename);
					continue;
				}
				discover_run=0;
				//pthread_cancel(tid);
				memset(remote_mac,0,sizeof(remote_mac));
				memcpy(remote_mac,eth_head_recv->h_source,ETH_HLEN);
				system("/usr/bin/killall -9 systemguard>/dev/null 2>&1");
				system("brctl delif br0 eth0");
				system("ifconfig ath8 down 2>&1");
				system("ifconfig ath0 down 2>&1");
				printf("server mac:%02x:%02x:%02x:%02x:%02x:%02x\n",eth_head_recv->h_source[0],
					eth_head_recv->h_source[1],
					eth_head_recv->h_source[2],
					eth_head_recv->h_source[3],
					eth_head_recv->h_source[4],
					eth_head_recv->h_source[5]);


			}
			else if(strncmp(payload_recv,versionupdatestr,strlen(versionupdatestr))==0){
				printf("payload_recv=%s\n", payload_recv);
				memset(new_version, 0, sizeof(new_version));
				if(strlen(payload_recv) > strlen(versionupdatestr)+strlen("NEW_VERSION:")){
					strcpy(new_version, payload_recv+strlen(versionupdatestr)+strlen("NEW_VERSION:"));
				}
				if(strlen(new_version) > 0 ){
					sprintf(cmd, "echo \"%s\" > /mnt/.rootfsversion", new_version);
					system(cmd);
					system("/bin/make_version 2>&1");
				}
				sleep(3);
				printf("Now updating is end-------------------------!\n");
				reboot(RB_AUTOBOOT);
				return 0;

			}
			else if(strncmp(payload_recv,err_image,strlen(err_image))==0){
				printf("payload_recv=%s\n", payload_recv);
				printf("your image is not I wanted!\n");
				system("apdown");
				system("insmod /lib/modules/2.6.31/net/updateerr.ko");
				return -1;

			}
			else if(strncmp(payload_recv,macupdatestr,strlen(macupdatestr))==0){
				printf("payload_recv=%s\n", payload_recv);
				strncpy(new_mac, payload_recv+strlen(macupdatestr), sizeof(new_mac));
				printf("New mac is:%s\n", new_mac);
				printf("Now we update mac!\n");
				sprintf(cmd, "cp /bin/mac_update /tmp/mac_update");
				system(cmd);
				sprintf(cmd, "/tmp/mac_update %s &", new_mac);
				system(cmd);
				return 0;

			}
			else if(strncmp(payload_recv,updateokstr,strlen(updateokstr))==0)
			{
				printf("My image is already updated\n");
				printf("%d %s\n", __LINE__, payload_recv);
				memset(new_version, 0, sizeof(new_version));
				if(strlen(payload_recv) > strlen(updateokstr)+strlen("NEW_VERSION:")){
					strcpy(new_version, payload_recv+strlen(updateokstr)+strlen("NEW_VERSION:"));
				}
				if(strlen(new_version) > 0 ){
					sprintf(cmd, "echo \"%s\" > /mnt/.rootfsversion", new_version);
					system(cmd);
					system("/bin/make_version 2>&1");
				}
				system("/usr/bin/killall -9 systemguard>/dev/null 2>&1");
				system("apdown");
				system("insmod /lib/modules/2.6.31/net/updateok.ko");
				system("dd if=/etc/ath/.apcfg of=/dev/mtdblock4>/dev/null 2>&1");
				return 0;
			}
			else if(strncmp(payload_recv,imageprefix,strlen(imageprefix))==0)
			{
				memset(&head_size_send,0,sizeof(struct head_size));
				memcpy(&head_size_send,payload_recv+strlen(imageprefix),sizeof(struct head_size));
				if(fp)
				{
					//fwrite(payload_recv+strlen(imageprefix),recv_len-strlen(imageprefix)-ETH_HLEN,1,fp);
					fwrite(payload_recv+strlen(imageprefix)+sizeof(struct head_size),head_size_send.size_data_send,1,fp);
				}
				else
				{
					printf("recv image data,but fp==NULL!\n");
					continue;
				}
			}
			else if(strncmp(payload_recv,imageendstr,strlen(imageendstr))==0)
			{
				if(fp)
				{
					fclose(fp);
					fp=NULL;
					printf("image recv ok!\n");

					memset(send_buffer,0,sizeof(send_buffer));
					payload_send=send_buffer+ETH_HLEN;
					eth_head_send=(struct ethhdr *)send_buffer;

					memcpy(eth_head_send->h_dest,remote_mac,ETH_HLEN);
					memcpy(eth_head_send->h_source,eth0_mac,ETH_HLEN);

					payload_send_len=sprintf(payload_send,"%s",imagemd5okstr);
					eth_head_send->h_proto=htons(payload_send_len);
					send_len=payload_send_len+ETH_HLEN;
					ret_send=sendto(sock_recv,send_buffer,send_len,0,(struct sockaddr *)(&sockaddr_ll_recv),sizeof(sockaddr_ll_recv));
					//ret_send=sendto(sock_send,send_buffer,send_len,0,(struct sockaddr *)(&sockaddr_ll_send),sizeof(sockaddr_ll_send));
					printf("image comfirm:source mac=%02x:%02x:%02x:%02x:%02x:%02x,dest mac=%02x:%02x:%02x:%02x:%02x:%02x,eth_head_send->h_proto=%d,ret_send=%d\n",
						eth_head_send->h_source[0],
						eth_head_send->h_source[1],
						eth_head_send->h_source[2],
						eth_head_send->h_source[3],
						eth_head_send->h_source[4],
						eth_head_send->h_source[5],
						eth_head_send->h_dest[0],
						eth_head_send->h_dest[1],
						eth_head_send->h_dest[2],
						eth_head_send->h_dest[3],
						eth_head_send->h_dest[4],
						eth_head_send->h_dest[5],
						eth_head_send->h_proto,
						ret_send);
					break;
				}
				printf("recv imageendstr,bug fp==NULL\n");
				continue;
			}
		}
	}
	close(sock_recv);

	sprintf(cmd, "cp -fr /bin/fw_upgrade /tmp");
	system(cmd);
	sprintf(cmd, "/tmp/fw_upgrade -v /tmp/recv_image");
	ret_val=system(cmd);
	if(ret_val!=0)
	{
		printf("Fuck updating is error-------------------------!\n");
		system("apdown");
		system("insmod /lib/modules/2.6.31/net/updateerr.ko");
		return -1;
	}
	printf("Now updating is began!\n");
	//sprintf(cmd, "/tmp/fw_upgrade /tmp/recv_image &");
	sprintf(cmd, "/tmp/fw_upgrade -m /tmp/recv_image &");
	system(cmd);
	return 0;
	/*
	system("insmod /lib/modules/2.6.31/net/updating.ko");
	system("dd if=/tmp/recv_image of=/tmp/md5.txt bs=1 count=36>/dev/null 2>&1");
	system("dd if=/tmp/recv_image of=/tmp/image bs=1 skip=36>/dev/null 2>&1");
	system("rm /tmp/recv_image -fr>/dev/null 2>&1");
	if(system("cat /tmp/image|md5sum -c /tmp/md5.txt>/dev/null 2>&1")!=0)
	{
	printf("md5 check fail!\n");
	system("apdown");
	system("insmod /lib/modules/2.6.31/net/updateerr.ko");
	return -1;
	}
	printf("md5 check ok!\n");

	system("/usr/bin/killall -9 wdping.sh>/dev/null 2>&1");
	system("/usr/bin/killall -9 athguard>/dev/null 2>&1");
	system("/etc/ath/apdown>/dev/null 2>&1");
	system("/usr/bin/killall -9 server_mips>/dev/null 2>&1");
	system("/usr/bin/killall -9 jffs2_gcd_mtd5>/dev/null 2>&1");
	system("/usr/bin/killall -9 telnetd>/dev/null 2>&1");
	system("/usr/bin/killall -9 iperf>/dev/null 2>&1");
	system("/usr/bin/killall -9 setpower>/dev/null 2>&1");
	system("/usr/bin/killall -9 wtp_capwap>/dev/null 2>&1");
	system("/usr/bin/killall -9 cfg_srv>/dev/null 2>&1");
	system("sync");
	printf("Now updating is began!\n");
	system("umount /mnt");
	system("umount /");
	//system("echo \"11111111\">/tmp/freset");
	//system("dd if=/tmp/freset of=/dev/mtdblock4  bs=1 count=36>/dev/null 2>&1");
	system("cp /bin/busybox /tmp/busybox -fr");
	system("/tmp/busybox dd if=/tmp/image of=/dev/mtdblock3 bs=1 skip=6356992>/dev/null 2>&1");
	//system("dd if=/tmp/image of=/dev/mtdblock3 bs=1 skip=6356992>/dev/null 2>&1");
	//system("dd if=/tmp/image of=/dev/mtdblock2 bs=1 count=6356992>/dev/null 2>&1");
	system("/tmp/busybox dd if=/tmp/image of=/dev/mtdblock2 bs=1 count=6356992>/dev/null 2>&1");
	//system("/tmp/busybox sync");
	*/
	printf("Now updating is end-------------------------!\n");
	reboot(RB_AUTOBOOT);
	return 0;
}
