global loader           ; making entry point visible to linker
extern kmain            ; kmain is defined elsewhere
 
; setting up the Multiboot header - see GRUB docs for details
MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002           ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required
 
section .text
align 4
MultiBootHeader:
   dd MAGIC
   dd FLAGS
   dd CHECKSUM
 
; reserve initial kernel stack space
STACKSIZE equ 0x4000                  ; that's 16k.
 
loader:
   mov esp, stack+STACKSIZE           ; set up the stack
   push eax                           ; pass Multiboot magic number
   push ebx                           ; pass Multiboot info structure
 
   call  kmain                       ; call kernel proper
 
   cli
hang:
   hlt                                ; halt machine should kernel return
   jmp   hang

; Code for GDT
global gdt_set
extern gdtable_ptr
gdt_set:
    lgdt [gdtable_ptr]        ; Load the GDT
    mov ax, 0x10			; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
    ret

; END: Code for GDT

; Code for IDT
global idt_set
extern idtable_ptr
idt_set:
    lidt [idtable_ptr]
    ret

;END: code for idt

section .bss
align 4
stack:
resb STACKSIZE                     ; reserve 16k stack on a doubleword boundary 
