AS = nasm
CC = i386-elf-gcc
LD = i386-elf-gcc

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

MAIN = header.o kernel.o
MEM = memory.o liballoc.o liballoc_support.o
KSCR = kscreen.o
ALL = $(MAIN) $(MEM) $(KSCR)

all: main memory kscreen
	hdiutil attach ../vm/hdd.img
	$(CC) -T linker.ld -o kernel.bin -ffreestanding -O2 -nostdlib $(ALL) -lgcc
	cp kernel.bin /Volumes/NO\ NAME/boot/
	rm $(ALL) kernel.bin
	bochs -qf ../vm/bochsrc
	
main: header.asm kernel.c
	$(AS) -felf -o header.o header.asm
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)

memory:	mem/memory.c mem/liballoc.c mem/liballoc_support.c
	$(CC) -c mem/memory.c -o memory.o $(CFLAGS)
	$(CC) -c mem/liballoc.c -o liballoc.o $(CFLAGS)
	$(CC) -c mem/liballoc_support.c -o liballoc_support.o $(CFLAGS)

kscreen: kscreen/kscreen.c
	$(CC) -c kscreen/kscreen.c -o kscreen.o $(CFLAGS)

clean:
	rm $(ALL) kernel.bin