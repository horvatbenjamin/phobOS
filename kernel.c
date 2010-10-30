#include "system.h"
#include "screen.h"

//Useful: http://www.gnu.org/software/grub/manual/multiboot/html_node/multiboot.h.html

void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
	   // Load error: Some error message
   }
 
   char * boot_loader_name =(char*) ((long*)mbd)[16];
   unsigned long lowmem_size=((unsigned long*)mbd)[1];
   unsigned long highmem_size=((unsigned long*)mbd)[2];

   init_video();
   puts("PhobOS booting...\n");
   puts("Booted by: ");
   puts(boot_loader_name);
   puts("\n");
   putint(lowmem_size);
   puts(" kiB low memory and ");
   putint(highmem_size);
   puts(" kiB high memory (total: ");
   putint(lowmem_size+highmem_size);
   puts(" kiB or ");
   putint((lowmem_size+highmem_size)/1024);
   puts(" MiB)\n");

   puts("Loading Global Descriptor Table...\t\t\t\t\t");
   gdt_install();
   puts("[OK]\n");
   puts("Loading Interrupt Descriptor Table...\t\t\t\t\t");
   idt_install();
   puts("[OK]\n");
   puts("Initializing Interrupt Services Routines(CPU Exceptions)...\t\t");
   isrs_install();
   puts("[OK]\n");
   puts("Initializing and enabling IRQ handlers...\t\t\t\t");
   irq_install();
   puts("[OK]\n");
   puts("Initializing IRQ handler for: IRQ0 ");
   timer_install();
   puts("IRQ1 ");
   keyboard_install();
   puts("\t\t\t\t[OK]\n");

   puts("\nBooting sequence completed...\n\n");
   // _IDT_DEBUG_();
   for(;;){		// SYSTEM IDLE PROCESS
	   __asm__ __volatile__ ("HLT");
   };
};
