AS = nasm
CC = i386-elf-gcc
LD = i386-elf-gcc

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

MAIN = header.o init.o
MEM = memory.o liballoc.o liballoc_support.o
KSCR = kscreen.o
ISR = exceptions_asm.o exceptions_c.o isr_asm.o isr_c.o int_asm.o int_c.o
SCHED = schedule_asm.o schedule_c.o
ALL = $(MAIN) $(MEM) $(KSCR) $(ISR) $(SCHED)


all: main memory kscreencode isrcode sched
	hdiutil attach ../vm/hdd.img
	$(CC) -T linker.ld -o kernel.bin -ffreestanding -O2 -nostdlib $(ALL) -lgcc
	cp kernel.bin /Volumes/OS/boot/
	rm $(ALL) kernel.bin
	bochs -qf ../vm/bochsrc

main: header.asm init.c
	$(AS) -felf -o header.o header.asm
	$(CC) -c init.c -o init.o $(CFLAGS)

memory:	mem/memory.c mem/liballoc.c mem/liballoc_support.c
	$(CC) -c mem/memory.c -o memory.o $(CFLAGS)
	$(CC) -c mem/liballoc.c -o liballoc.o $(CFLAGS)
	$(CC) -c mem/liballoc_support.c -o liballoc_support.o $(CFLAGS)

kscreencode: kscreen/kscreen.c
	$(CC) -c kscreen/kscreen.c -o kscreen.o $(CFLAGS)

isrcode: isr/exceptions.asm isr/exceptions.c isr/isr.asm isr/isr.c isr/int.asm isr/int.c
	$(AS) -felf -o exceptions_asm.o isr/exceptions.asm
	$(CC) -c isr/exceptions.c -o exceptions_c.o $(CFLAGS)
	$(AS) -felf -o isr_asm.o isr/isr.asm
	$(CC) -c isr/isr.c -o isr_c.o $(CFLAGS)
	$(AS) -felf -o int_asm.o isr/int.asm
	$(CC) -c isr/int.c -o int_c.o $(CFLAGS)

sched: schedule/schedule.asm schedule/schedule.c
	$(AS) -felf -o schedule_asm.o schedule/schedule.asm
	$(CC) -c ./schedule/schedule.c -o ./schedule_c.o $(CFLAGS)

clean:
	rm $(ALL) kernel.bin
