ifneq ($(strip $(TOOLPREFIX)),)
CROSS:=$(TOOLPREFIX)
endif

CC              =$(CROSS)gcc -lpthread
STRIP           =$(CROSS)strip
LD              =$(CROSS)ld
AR              =$(CROSS)ar

#cgibin=apcfg apinfo arptable arptest athstalist aththroughput brmac channellist channellist_5g modifyflag_reset channelwidth connection distance en_ch_mode linkquality noisefloor pingtest rateshow routetable searchssid signallevel speedtest stachannel stainfo tdma time txrx uploadconf uploadrootfs uploadpic uploadpic2 getif statusinfo companyname modifyflag iperf_show iperf_test wanstatus getscanfreq showlog picupload pic2upload getacstatus timeinfo getwirelessmode getspectralstatus getnetworkstatus
cgibin=getradiostatus apcfg apinfo arptable arptest athstalist aththroughput brmac channellist channellist_5g modifyflag_reset channelwidth en_ch_mode  pingtest routetable searchssid  stainfo  txrx uploadconf uploadrootfs uploadpic uploadpic2 getif companyname modifyflag statusinfo iperf_show iperf_test wanstatus getscanfreq showlog picupload pic2upload getacstatus timeinfo getwirelessmode getspectralstatus getnetworkstatus getwirelessmode2 tdma_11ac rootfsversion getapcfgstatus catch_log
userbin=checkfactory trim iperflog raw_recv getdhcprange

all: $(cgibin) $(userbin) installall

ifeq ($(BOARD_TYPE),ap135)
raw_recv: raw_recv_11ac.c
		$(CC) $^ $(LDFLAGS) -o $@
uploadrootfs: uploadrootfs_11ac.c
		$(CC) $^ $(LDFLAGS) -o $@
statusinfo: statusinfo_11ac.c
		$(CC) $^ $(LDFLAGS) -o $@
txrx: txrx_11ac.c
		$(CC) $^ $(LDFLAGS) -o $@
else
raw_recv: raw_recv.c
		$(CC) $^ $(LDFLAGS) -o $@
uploadrootfs: uploadrootfs.c
		$(CC) $^ $(LDFLAGS) -o $@
statusinfo: statusinfo.c
		$(CC) $^ $(LDFLAGS) -o $@
txrx: txrx.c
		$(CC) $^ $(LDFLAGS) -o $@
endif

installall:
	$(STRIP) $(cgibin) $(userbin)
	cp $(cgibin) $(INSTALL_ROOT)/usr/www/cgi-bin/
	cp $(userbin) $(INSTALL_ROOT)/bin/
clean:
	rm $(cgibin) $(userbin) -fr
