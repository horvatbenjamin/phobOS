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
STACKSIZE equ 0x8000                  ; that's 32k.
 
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
	cli
    lgdt [gdtable_ptr]        ; Load the GDT
	mov eax, cr0
	or al,1
	mov cr0,eax
;    mov ax, 0x10			; 0x10 is the offset in the GDT to our data segment
;    mov ds, ax
;    mov es, ax
;    mov fs, ax
;    mov gs, ax
;    mov ss, ax
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

;CPU Exeption handlers

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

global isr_unhandled

isr0:
	cli
	push byte 0 ;dummy errorcode
	push byte 0 ;exeption code
	jmp _isr_common

isr1:
	push byte 0
	push byte 1
	jmp _isr_common

isr2:
	push byte 0
	push byte 2
	jmp _isr_common

isr3:
	push byte 0
	push byte 3
	jmp _isr_common

isr4:
	push byte 0
	push byte 4
	jmp _isr_common

isr5:
	push byte 0
	push byte 5
	jmp _isr_common

isr6:
	push byte 0
	push byte 6
	jmp _isr_common

isr7:
	push byte 0
	push byte 7
	jmp _isr_common

isr8:
	push byte 8
	jmp _isr_common

isr9:
	push byte 0
	push byte 9
	jmp _isr_common

isr10:
	push byte 10
	jmp _isr_common

isr11:
	push byte 11
	jmp _isr_common

isr12:
	push byte 12
	jmp _isr_common

isr13:
	push byte 13
	jmp _isr_common

isr14:
	push byte 14
	jmp _isr_common

isr15:
	push byte 0
	push byte 15
	jmp _isr_common

isr16:
	push byte 0
	push byte 16
	jmp _isr_common

isr17:
	push byte 0
	push byte 17
	jmp _isr_common

isr18:
	push byte 0
	push byte 18
	jmp _isr_common

isr19:
	push byte 0
	push byte 19
	jmp _isr_common

isr20:
	push byte 0
	push byte 20
	jmp _isr_common

isr21:
	push byte 0
	push byte 21
	jmp _isr_common

isr22:
	push byte 0
	push byte 22
	jmp _isr_common

isr23:
	push byte 0
	push byte 23
	jmp _isr_common

isr24:
	push byte 0
	push byte 24
	jmp _isr_common

isr25:
	push byte 0
	push byte 25
	jmp _isr_common

isr26:
	push byte 0
	push byte 26
	jmp _isr_common

isr27:
	push byte 0
	push byte 27
	jmp _isr_common

isr28:
	push byte 0
	push byte 28
	jmp _isr_common

isr29:
	push byte 0
	push byte 29
	jmp _isr_common

isr30:
	push byte 0
	push byte 30
	jmp _isr_common

isr31:
	push byte 0
	push byte 31
	jmp _isr_common

;;;;;;;;;;;
extern fault_handler

_isr_common:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10 ;kernel Data Segment
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov eax,esp
	push eax
	mov eax,fault_handler
	call eax	;call C fault_handler
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp,8	;purge error code and exeption code
	iret
;END: CPU Exeption handlers

;IRQ Handler
global _irq0;
global _irq1;
global _irq2;
global _irq3;
global _irq4;
global _irq5;
global _irq6;
global _irq7;
global _irq8;
global _irq9;
global _irq10;
global _irq11;
global _irq12;
global _irq13;
global _irq14;
global _irq15;

_irq0:
	cli
	push byte 0
	push byte 32
	jmp	irq_common

_irq1:
	cli
	push byte 0
	push byte 33
	jmp irq_common

_irq2:
	cli
	push byte 0
	push byte 34
	jmp irq_common

_irq3:
	cli
	push byte 0
	push byte 35
	jmp irq_common

_irq4:
	cli
	push byte 0
	push byte 36
	jmp irq_common

_irq5:
	cli
	push byte 0
	push byte 37
	jmp irq_common

_irq6:
	cli
	push byte 0
	push byte 38
	jmp irq_common

_irq7:
	cli
	push byte 0
	push byte 39
	jmp irq_common

_irq8:
	cli
	push byte 0
	push byte 40
	jmp irq_common

_irq9:
	cli
	push byte 0
	push byte 41
	jmp irq_common

_irq10:
	cli
	push byte 0
	push byte 42
	jmp irq_common

_irq11:
	cli
	push byte 0
	push byte 43
	jmp irq_common

_irq12:
	cli
	push byte 0
	push byte 44
	jmp irq_common

_irq13:
	cli
	push byte 0
	push byte 45
	jmp irq_common

_irq14:
	cli
	push byte 0
	push byte 46
	jmp irq_common

_irq15:
	cli
	push byte 0
	push byte 47
	jmp irq_common

extern irq_handler

irq_common:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov eax,esp
	push eax
	mov eax,irq_handler
	call eax
	pop eax
	mov esp,eax	;custom
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp,8
	iret

;END: IRQ Handler

section .bss
align 4
stack:
resb STACKSIZE                     ; reserve 16k stack on a doubleword boundary 
