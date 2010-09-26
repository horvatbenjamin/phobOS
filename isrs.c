#include "system.h"

extern void isr0();

extern void isr_unhandled();
//...

void isrs_install(){
	int x;
	idt_add_entry(0, (unsigned)isr0,0x80,0x8E);	//
	for(x=1;x<254;x++) idt_add_entry(x,(unsigned)isr_unhandled,0x80,0x8E);
};

unsigned char *exeption_messages[]={
	"Division by zero"
};

void fault_handler(struct regs *r){
	if(r->exeption_no < 32){
		puts(exeption_messages[r->exeption_no]);
		puts(" Exeption occured... System Halted!\n");
		for(;;);
	};
	puts("Unhandled exeption! System halted\n");
	for(;;);
};
