CC:=gcc
CFLAGS=-m32 -c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -ggdb $<

LD:=ld
LDFLAGS=-melf_i386 -T linker.ld -o $@ $^

.PHONY: clean run debug .c.o

all: clean run

clean:
	if  test -f ./kernel.bin; then rm ./kernel.bin; fi
	if test -f ./harddisk.img; then rm ./harddisk.img; fi
	@rm *.o

.c.o:
	$(CC) $(CFLAGS)

loader.o:
	nasm -f elf -o loader.o loader.s
	
kernel.bin: loader.o kernel.o system.o screen.o gdt.o idt.o isrs.o irq.o
	$(LD) $(LDFLAGS)

harddisk.img: kernel.bin
	dd if=/dev/zero of="$@" bs=4k count=`echo 4*1024*1024/4096 | bc` 2>/dev/null
	mkfs.vfat "$@" 2>/dev/null
	syslinux "$@" 2>/dev/null
	mcopy -i "$@" /usr/lib/syslinux/mboot.c32 ::mboot.c32 2>/dev/null
	mcopy -i "$@" "$<" ::kernel.bin 2>/dev/null
	@echo "TIMEOUT 1 DEFAULT mboot.c32 kernel.bin" | mcopy -i "$@" - ::syslinux.cfg

run: harddisk.img
	qemu-system-x86_64 -cpu core2duo -m 256 -monitor stdio -hda $<

debug: harddisk.img
	qemu-system-i386 -cpu coreduo -m 256 -monitor stdio -S -s $<
