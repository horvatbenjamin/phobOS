#!/bin/bash
rm ./kernel.bin
rm ./*.o

nasm -f elf -o loader.o loader.s
gcc -m32 -o kernel.o -c kernel.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -ggdb
gcc -m32 -o system.o -c system.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -ggdb
gcc -m32 -o screen.o -c screen.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -ggdb
gcc -m32 -o gdt.o -c gdt.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -ggdb
gcc -m32 -o idt.o -c idt.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -ggdb
gcc -m32 -o isrs.o -c isrs.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -ggdb
gcc -m32 -o irq.o -c irq.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -ggdb

ld -melf_i386  -T linker.ld -o kernel.bin loader.o kernel.o system.o screen.o gdt.o idt.o isrs.o irq.o
