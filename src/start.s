
MBOOT_PAGE_ALIGN	equ 1<<0	;Load kernal/modules on a page boundary 
MBOOT_MEM_INFO		equ 1<<1	;Memory info
MBOOT_HEADER_MAGIC	equ 0x1BADB002	;Multiboot magic number

MBOOT_HEADER_FLAGS	equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM		equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)



[BITS 32]		;32-bit instructions


[GLOBAL mboot]		;Make mboot accessible in C code
[EXTERN code]		;Begin '.text' section	
[EXTERN bss]		;Begin '.bss' section
[EXTERN end]		;End of the last loadable section

mboot:
   dd MBOOT_HEADER_MAGIC    ;GRUB will look for this on every 4-byte boundary in the kernel file
   dd MBOOT_HEADER_FLAGS    ;Instructs how GRUB should load stuff
   dd MBOOT_CHECKSUM

   dd mboot     ;Location of this descriptor
   dd code      ;Start of '.text' section
   dd bss       ;End of '.data' section
   dd end       ;End of the kernel
   dd start     ;Kernel entry point (EIP)


[GLOBAL start]  ;Kernel entry point
[EXTERN main]   ;Entry point in C code

start:
    push ebx    ;Load multiboot header location
    cli         ;Disable interrupts
    call main   ;Call the main() function defined in C code
    jmp $       ;Infinite loop
