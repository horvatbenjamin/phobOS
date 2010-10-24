#include "system.h"


extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();
//....

void *irq_handlers[16]={
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

void irq_set_handler(unsigned char irq,void (*handler)(struct regs *r)){
	irq_handlers[irq]=handler;
};

void irq_remove_handler(unsigned char irq){
	irq_handlers[irq]=0;
};

// remaps IRQ0-15 to IDT entries 32 to 47
void irq_remap(){
	outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
};

void irq_install(){
	irq_remap();
	idt_add_entry(32,(unsigned long)_irq0,0x08,0x8E);
	idt_add_entry(33,(unsigned long)_irq1,0x08,0x8E);
	idt_add_entry(34,(unsigned long)_irq2,0x08,0x8E);
	idt_add_entry(35,(unsigned long)_irq3,0x08,0x8E);
	idt_add_entry(36,(unsigned long)_irq4,0x08,0x8E);
	idt_add_entry(37,(unsigned long)_irq5,0x08,0x8E);
	idt_add_entry(38,(unsigned long)_irq6,0x08,0x8E);
	idt_add_entry(39,(unsigned long)_irq7,0x08,0x8E);
	idt_add_entry(40,(unsigned long)_irq8,0x08,0x8E);
	idt_add_entry(41,(unsigned long)_irq9,0x08,0x8E);
	idt_add_entry(42,(unsigned long)_irq10,0x08,0x8E);
	idt_add_entry(43,(unsigned long)_irq11,0x08,0x8E);
	idt_add_entry(44,(unsigned long)_irq12,0x08,0x8E);
	idt_add_entry(45,(unsigned long)_irq13,0x08,0x8E);
	idt_add_entry(46,(unsigned long)_irq14,0x08,0x8E);
	idt_add_entry(47,(unsigned long)_irq15,0x08,0x8E);
	__asm__ __volatile__ ("sti");
};

void irq_handler(unsigned long ret_addr,struct regs *r){
	puts("\nIRQ!\n");
	void (*handler)(struct regs *r);
	handler=irq_handlers[r->exception_no-32];
	if(handler) handler(r);
	if(r->exception_no>=40) outportb(0xA0,0x20);
	outportb(0x20,0x20);
	puts("END!\n");
};
