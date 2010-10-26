#include "system.h"

unsigned char keymap[128];

void irq1_handler(struct regs *r){
	unsigned char scancode;
	scancode=inportb(0x60);
//	putch(keymap[scancode]);
	putch('.');

};

void keyboard_install(){
	irq_set_handler(1,irq1_handler);
};
