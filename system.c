#include "system.h"

void *memcpy(void *dst,const void *src, size_t count){
	const char *src_ptr=(const char *)src;
	char *dst_ptr=(char *)dst;
	for(;count!=0;count--)*dst_ptr++=*src_ptr++;
	return dst_ptr;
};

void *memset(void *dst, char val, size_t count){
	char *dst_ptr=(char *)dst;
	for(;count!=0;count--)*dst_ptr++=val;
	return dst_ptr;
};

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count){
	unsigned short *dst_ptr=dest;
	for(;count!=0;count--)*dst_ptr++=val;
	return dst_ptr;
};

size_t strlen(const char *str){
	size_t count;
	for(count=0;*str!='\0';str++)count++;
	return count;
};

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */

unsigned char inportb (unsigned short _port){
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
};

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data){
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
};
