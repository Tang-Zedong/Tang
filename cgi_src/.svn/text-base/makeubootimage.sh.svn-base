#!/bin/sh -x
UBOOT=$1
ROOTFS=$2
KERNEL=$3
UBOOT_LEN=`ls -l $UBOOT |sed "s/ \{1,\}/X/g"|cut -d 'X' -f 5`
echo "hasuboot">>tmp
echo "$UBOOT_LEN">>tmp
cat $UBOOT>>tmp
dd if=$ROOTFS of=rootfs-tmp bs=6356992 conv=sync
cat rootfs-tmp>>tmp
cat $KERNEL>>tmp
cat tmp|md5sum>md5
cat tmp>>md5

