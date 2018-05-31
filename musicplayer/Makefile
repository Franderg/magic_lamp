# source /opt/poky/2.3.3/environment-setup-cortexa7hf-neon-vfpv4-poky-linux-gnueabi

SRC = musicplayer
DST = $(SRC)
CC = arm-poky-linux-gnueabi-gcc

SYSROOT = --sysroot=/opt/poky/2.3.3/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi/


all: main

main:
		$(CC) -O2 ${SYSROOT} -o $(DST) $(SRC).c -mfloat-abi=hard -lmpg123 -lao

clean:
		rm $(DST)*
