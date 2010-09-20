#!/bin/bash
rm ./kernel.bin
rm ./*.o

nasm -f elf -o loader.o loader.s
gcc -m32 -o kernel.o -c kernel.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs
ld -melf_i386  -T linker.ld -o kernel.bin loader.o kernel.o
