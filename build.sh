#!/bin/bash
rm ./kernel.bin
rm ./*.o

nasm -f elf -o loader.o loader.s
gcc -m32 -o kernel.o -c kernel.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
gcc -m32 -o system.o -c system.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
gcc -m32 -o screen.o -c screen.c -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -fno-builtin

ld -melf_i386  -T linker.ld -o kernel.bin loader.o kernel.o system.o screen.o
