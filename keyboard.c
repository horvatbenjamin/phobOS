#include "system.h"

unsigned char keymap[128]=	{0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t',
							 'q','w','e','r','t','y','u','i','o','p','[',']','\n',0 /* 29:Lctrl */,'a','s',
							 'd','f','g','h','j','k','l',';','\'','`',0 /* 42:Lshift */,'\\','z','x','c','v',
							 'b','n','m',',','.','/',0 /* 54 Rshift */,0 /* 55 prtscr */,0 /* alt */,' '};

/* http://terpconnect.umd.edu/~nsw/ench250/scancode.htm */

void irq1_handler(struct regs *r){
	unsigned char scancode;
	scancode=inportb(0x60);
	if(scancode+128 < 254){
		putch(keymap[scancode]);
	};
};

void keyboard_install(){
	irq_set_handler(1,irq1_handler);
};
