void clear_screen(unsigned char *vmem){
	int x;
	for(x=0;x<80*40;x++){
		vmem[2*x]=' ';
	};
};

void print(unsigned char *vmem,char *text){
	int row=0,column=0,counter=0;

	while (*(text+counter)!='\0'){
		if(*(text+counter)=='\n'){
			column=0;
			row++;
			counter++;
		};
		vmem[2*column+160*row]=text[counter];
		vmem[2*column+1+160*row]=0x07;
		counter++;
		column++;
	};
};

void kmain( void* mbd, unsigned int magic )
{
   if ( magic != 0x2BADB002 )
   {
	   // Load error: Some error message
   }
 
   char * boot_loader_name =(char*) ((long*)mbd)[16];
 
   // Print a letter to screen to see everything is working:
   unsigned char *videoram = (unsigned char *) 0xb8000;
   clear_screen(videoram);
   char txt[]="Hello World!!!\nMasodik sor\nHarmadik...\0";
   char *ptr_txt=&txt[0];
   print(videoram,ptr_txt);
} 
