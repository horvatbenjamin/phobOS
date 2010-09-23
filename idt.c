#include "system.h"

struct idt_entry{
	unsigned short base0_15;
	unsigned short selector;
	unsigned char zero;
	unsigned char flags;
	unsigned short base16_31;
} __attribute__((packed));

struct idt_pointer{
	unsigned short limit;
	unsigned int base;
} __attribute((packed));

struct idt_entry idtable[256];
struct idt_pointer idtable_ptr;

extern void idt_set();

void idt_install(){
    idtable_ptr.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtable_ptr.base = (int)&idtable;

    // Initialize memory
	memset(&idtable, 0, sizeof(struct idt_entry) * 256);

	//Add entries to table
	
    idt_set();
}

