#ifndef __SYSTEM_H
#define __SYSTEM_H

	/* structures */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int exeption_no, err_code;    /* 'push byte #' and error_codes */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};
////////////
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

		/* idt.c */
void idt_install();
void _IDT_DEBUG_();

		/* isrs.c */
void isrs_install();

#endif
	
