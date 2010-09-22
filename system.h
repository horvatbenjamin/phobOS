#ifndef __SYSTEM_H
#define __SYSTEM_H

typedef unsigned int size_t;
		/* system.c */
void *memcpy(void *dst,const void *src, size_t count);
void *memset(void *dest,char val, size_t count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
size_t strlen(const char *str);
unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

		/* gdt.c */
void gdt_install();
#endif
	
