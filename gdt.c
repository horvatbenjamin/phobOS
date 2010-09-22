#include "system.h"

struct gdt_entry{
	unsigned short limit0_15;
	unsigned short base0_15;
	unsigned char base16_23;
	unsigned char access;
	unsigned char limit16_19_flags;
	unsigned char base24_31;
} __attribute__((packed));

struct gdt_pointer{
	unsigned short limit;
	unsigned int base;
} __attribute((packed));

struct gdt_entry gdtable[3];
struct gdt_pointer gdtable_ptr;
extern void gdt_set();

void gdt_add_entry(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran){
    // Setup the descriptor base address
    gdtable[num].base0_15 = (base & 0xFFFF);
    gdtable[num].base16_23 = (base >> 16) & 0xFF;
    gdtable[num].base24_31 = (base >> 24) & 0xFF;

//	memcpy(&gdtable[num].base0_15,&base,4);
//	memcpy(&gdtable[num].base16_23,&base+4,2);
//	memcpy(&gdtable[num].base24_31,&base+6,2);

    // Setup the descriptor limits
    gdtable[num].limit0_15 = (limit & 0xFFFF);
    gdtable[num].limit16_19_flags = ((limit >> 16) & 0x0F);

//	memcpy(&gdtable[num].limit0_15,&limit,4);
//	memcpy(&gdtable[num].limit16_19_flags,&limit+4,1);

	// Set up the access and flags
    gdtable[num].limit16_19_flags |= (gran & 0xF0);
//	memcpy(*(gdtable[num].limit16_19_flags)+1,);
    gdtable[num].access = access;
}

void gdt_install(){
    // Set up the GDT pointer and limit
    gdtable_ptr.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdtable_ptr.base = (unsigned int)&gdtable;

    // Null descriptor, i think it is for debug... (?!)
    gdt_add_entry(0, 0, 0, 0, 0);
	
	// http://wiki.osdev.org/GDT
	// Entry for Code Segment
	// 0x9A: 10011010
    gdt_add_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Entry for Data Segment.
	// 0x92: 10010010
	gdt_add_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Activate changes :)
	gdt_set();
}


