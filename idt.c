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

void idt_add_entry(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags){
    // Setup the descriptor base address
    idtable[num].base0_15 = (base & 0xFFFF);
    idtable[num].base16_31 = (base >> 16) & 0xFFFF;
	idtable[num].selector = selector;
	
	// Set the zero flag to zero
	idtable[num].zero = 0;

	idtable[num].flags = flags;
}

void idt_install(){
    idtable_ptr.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtable_ptr.base = (unsigned int)&idtable;

    // Initialize memory
	memset(&idtable, 0, sizeof(struct idt_entry) * 256);

	//Add entries to table
    idt_set();
}

void _IDT_DEBUG_(){
	unsigned int x=0;
	for(x=0;x<255*sizeof(struct idt_entry);x++)putch((char)*(char*)(idtable+x));
}
