
[GLOBAL gdt_flush]

gdt_flush:
	mov eax, [esp+4]	;Get pointer to gdt (of type gdt_ptr_t) passed as argument
	lgdt [eax]			;Load GDT

	mov ax, 0x10		;0x10 is the offset in the GDT of the kernel mode data segment
	mov ds, ax
	mov ss, ax
	mov fs, ax
	mov es, ax
	mov gs, ax
	jmp 0x08:.flush		;0x08 is the offset to the code segment. The cs register is implecitly set to this value in the instruction.
.flush:
	ret


[GLOBAL idt_flush]

idt_flush:
	mov eax, [esp+4]	;Get pointer to idt (of type idt_ptr_t) passed as argument
	lidt [eax]			;Load IDT
	ret
