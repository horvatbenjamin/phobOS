#include "system.h"
#include "screen.h"

void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
	   // Load error: Some error message
   }
 
   char * boot_loader_name =(char*) ((long*)mbd)[16];
 
   // Print a letter to screen to see everything is working:
   char txt[]="Hello World!!!\nMasodik sor\nHarmadik...";
   char *ptr_txt=&txt[0];
   int a=1,b=0;;
   char t='0';
   gdt_install();
   idt_install();
   isrs_install();
   irq_install();
   timer_install();
   keyboard_install();
   init_video();
   puts(ptr_txt);
   _IDT_DEBUG_();
   for(;;){		// SYSTEM IDLE PROCESS
	   __asm__ __volatile__ ("HLT");
   };
} 
