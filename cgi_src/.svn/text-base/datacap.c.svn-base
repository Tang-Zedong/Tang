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
#define BUFFER_MAX 1500

typedef struct {
        u_int32_t did;
        u_int16_t status;
        u_int16_t len;
        u_int32_t data;
} p80211item_uint32_t;
typedef struct {                        
        u_int32_t msgcode;
        u_int32_t msglen; 
#define WLAN_DEVNAMELEN_MAX 16
        u_int8_t devname[WLAN_DEVNAMELEN_MAX];
        p80211item_uint32_t hosttime;
        p80211item_uint32_t mactime;
        p80211item_uint32_t channel;
        p80211item_uint32_t rssi;
        p80211item_uint32_t sq;
        p80211item_uint32_t signal;
        p80211item_uint32_t noise;
        p80211item_uint32_t rate;
        p80211item_uint32_t istx;
        p80211item_uint32_t frmlen;
} wlan_ng_prism2_header;


int main()
{
	int sock_recv;
	unsigned char recv_buffer[BUFFER_MAX];
	struct ethhdr *eth_head_recv;
	struct ifreq ifreq_param_recv;
	struct sockaddr_ll sockaddr_ll_recv;
	fd_set recv_fds;	
	struct timeval tv;
        int ret_select=0;
	int recv_len=0;
	socklen_t addrlen=0;
	wlan_ng_prism2_header *recv_hdr=NULL;

	memset(recv_buffer,0,sizeof(recv_buffer));

        if((sock_recv=socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL)))<0)
        {
                printf("create socket error\n");
                exit(-3);
        }

        memset(&ifreq_param_recv,0,sizeof(ifreq_param_recv));
        memset(&sockaddr_ll_recv,0,sizeof(sockaddr_ll_recv));
        strcpy(ifreq_param_recv.ifr_name,"ath0");
        ioctl(sock_recv,SIOCGIFINDEX,&ifreq_param_recv);
        sockaddr_ll_recv.sll_ifindex=ifreq_param_recv.ifr_ifindex;
	bind(sock_recv,(struct sockaddr *)(&sockaddr_ll_recv),sizeof(sockaddr_ll_recv));
	while(1)
        {
                FD_ZERO(&recv_fds);
                FD_SET(sock_recv,&recv_fds);

                tv.tv_sec=5;
                tv.tv_usec=0;
                ret_select=select(sock_recv+1,&recv_fds,NULL,NULL,&tv);
		if(ret_select<0)
                        continue;
                else if(ret_select==0)
                {

		}
		else
		{

		}	

		if(FD_ISSET(sock_recv,&recv_fds))
                {
                        addrlen=sizeof(&sockaddr_ll_recv);
                        memset(recv_buffer,0,sizeof(recv_buffer));
                        recv_len=recvfrom(sock_recv,recv_buffer,BUFFER_MAX,0,(struct sockaddr *)(&sockaddr_ll_recv),&addrlen);
			recv_hdr=(wlan_ng_prism2_header *)recv_buffer;
			if(recv_hdr->msgcode==68&&recv_hdr->frmlen.data>24)
			printf("msgcode=%d,msglen=%d,channel=%d,signal=%d,frmlen=%d,mac=%02x:%02x:%02x:%02x:%02x:%02x\n",recv_hdr->msgcode,recv_hdr->msglen,recv_hdr->channel.data,recv_hdr->signal.data,recv_hdr->frmlen.data,recv_buffer[154],recv_buffer[155],recv_buffer[156],recv_buffer[157],recv_buffer[158],recv_buffer[159]);
/*	printf("recv:%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",recv_buffer[0],
											       recv_buffer[1],
											       recv_buffer[2],
											       recv_buffer[3],
											       recv_buffer[4],
											       recv_buffer[5],
											       recv_buffer[6],
											       recv_buffer[7],
											       recv_buffer[8],
											       recv_buffer[9],
											       recv_buffer[10],
											       recv_buffer[11],
											       recv_buffer[12],
											       recv_buffer[13],
											       recv_buffer[14],
											       recv_buffer[15],
											       recv_buffer[16],
											       recv_buffer[17],
											       recv_buffer[18],
											       recv_buffer[19],
											       recv_buffer[20],
											       recv_buffer[21],
											       recv_buffer[22],
											       recv_buffer[23],
											       recv_buffer[24],
											       recv_buffer[25],
											       recv_buffer[26],
											       recv_buffer[27],
											       recv_buffer[28],
											       recv_buffer[29],
											       recv_buffer[30],
											       recv_buffer[31],
											       recv_buffer[32],
											       recv_buffer[33],
											       recv_buffer[34],
											       recv_buffer[35],
											       recv_buffer[36],
											       recv_buffer[37],
											       recv_buffer[38],
											       recv_buffer[39],
											       recv_buffer[40],
											       recv_buffer[41],
											       recv_buffer[42],
											       recv_buffer[43],
											       recv_buffer[44],
											       recv_buffer[45],
											       recv_buffer[46],
											       recv_buffer[47],
											       recv_buffer[48],
											       recv_buffer[49],
											       recv_buffer[50],
											       recv_buffer[51],
											       recv_buffer[52],
											       recv_buffer[53],
											       recv_buffer[54],
											       recv_buffer[55],
											       recv_buffer[56],
											       recv_buffer[57],
											       recv_buffer[58],
											       recv_buffer[59],
											       recv_buffer[60],
											       recv_buffer[61],
											       recv_buffer[62],
											       recv_buffer[63],
											       recv_buffer[64],
											       recv_buffer[65],
											       recv_buffer[66],
											       recv_buffer[67],
											       recv_buffer[68],
											       recv_buffer[69],
											       recv_buffer[70],
											       recv_buffer[71],
											       recv_buffer[72],
											       recv_buffer[73],
											       recv_buffer[74],
											       recv_buffer[75],
											       recv_buffer[76],
											       recv_buffer[77],
											       recv_buffer[78],
											       recv_buffer[79],
											       recv_buffer[80],
											       recv_buffer[81],
											       recv_buffer[82],
											       recv_buffer[83],
											       recv_buffer[84],
											       recv_buffer[85],
											       recv_buffer[86],
											       recv_buffer[87],
											       recv_buffer[88],
											       recv_buffer[89],
											       recv_buffer[90],
											       recv_buffer[91],
											       recv_buffer[92],
											       recv_buffer[93],
											       recv_buffer[94],
											       recv_buffer[95],
											       recv_buffer[96],
											       recv_buffer[97],
											       recv_buffer[98],
											       recv_buffer[99],
											       recv_buffer[100],
											       recv_buffer[101],
											       recv_buffer[102],
											       recv_buffer[103],
											       recv_buffer[104],
											       recv_buffer[105],
											       recv_buffer[106],
											       recv_buffer[107],
											       recv_buffer[108],
											       recv_buffer[109],
											       recv_buffer[110],
											       recv_buffer[111],
											       recv_buffer[112],
											       recv_buffer[113],
											       recv_buffer[114],
											       recv_buffer[115],
											       recv_buffer[116],
											       recv_buffer[117],
											       recv_buffer[118],
											       recv_buffer[119],
											       recv_buffer[120],
											       recv_buffer[121],
											       recv_buffer[122],
											       recv_buffer[123],
											       recv_buffer[124],
											       recv_buffer[125],
											       recv_buffer[126],
											       recv_buffer[127],
											       recv_buffer[128],
											       recv_buffer[129],
											       recv_buffer[130],
											       recv_buffer[131],
											       recv_buffer[132],
											       recv_buffer[133],
											       recv_buffer[134],
											       recv_buffer[135],
											       recv_buffer[136],
											       recv_buffer[137],
											       recv_buffer[138],
											       recv_buffer[139],
											       recv_buffer[140],
											       recv_buffer[141],
											       recv_buffer[142],
											       recv_buffer[143],
											       recv_buffer[144],
											       recv_buffer[145],
											       recv_buffer[146],
											       recv_buffer[147],
											       recv_buffer[148],
											       recv_buffer[149],
											       recv_buffer[150],
											       recv_buffer[151],
											       recv_buffer[152],
											       recv_buffer[153],
											       recv_buffer[154],
											       recv_buffer[155],
											       recv_buffer[156],
											       recv_buffer[157],
											       recv_buffer[158],
											       recv_buffer[159],
											       recv_buffer[160],
											       recv_buffer[161],
											       recv_buffer[162],
											       recv_buffer[163],
											       recv_buffer[164],
											       recv_buffer[165],
											       recv_buffer[166],
											       recv_buffer[167],
											       recv_buffer[168],
											       recv_buffer[169],
											       recv_buffer[170],
											       recv_buffer[171],
											       recv_buffer[172],
											       recv_buffer[173],
											       recv_buffer[174],
											       recv_buffer[175],
											       recv_buffer[176],
											       recv_buffer[177],
											       recv_buffer[178],
											       recv_buffer[179],
											       recv_buffer[180]);
			*/
			
		}
	}
}
