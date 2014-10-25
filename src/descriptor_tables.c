
#include "descriptor_tables.h"

/**
 * GDT and IDT entries.
 */
#define NUM_GDT_ENTRIES 5
gdt_entry_t gdt_entries[NUM_GDT_ENTRIES];
gdt_ptr_t gdt_ptr;

#define NUM_IDT_ENTRIES 256
idt_entry_t idt_entries[NUM_IDT_ENTRIES];
idt_ptr_t idt_ptr;

/**
 * Flushes the gdt using the lgdt instruction. Defined in descriptor_tables.s.
 */
extern void gdt_flush(uint32 ui_gdt_ptr);

/**
 * Flushes the idt using the lidt instruction. Defined in descriptor_tables.s.
 */
extern void idt_flush(uint32 ui_idt_ptr);

static void init_gdt();
static void gdt_setup_entry(uint32 index, uint32 base, uint32 limit, uint32 access, uint32 flags);

static void init_idt();
static void idt_setup_entry(uint8 index, uint32 base, uint16 sel, uint8 flags);

void init_descriptor_tables()
{
	init_gdt();
	init_idt();
}

void init_gdt()
{
	gdt_ptr.base = (uint32)gdt_entries;
	gdt_ptr.limit = sizeof(gdt_entries)-1;

	gdt_setup_entry(0, 0, 0, 0, 0);				//Null segment
	gdt_setup_entry(1, 0, 0xFFFFF, 0x9A, 0x0C);	//Kernel mode code segment
	gdt_setup_entry(2, 0, 0xFFFFF, 0x92, 0x0C);	//Kernel mode data segment
	gdt_setup_entry(3, 0, 0xFFFFF, 0xFA, 0x0C);	//User mode data segment
	gdt_setup_entry(4, 0, 0xFFFFF, 0xF2, 0x0C);	//User mode data segment

	gdt_flush((uint32)&gdt_ptr);
}

void gdt_setup_entry(uint32 index, uint32 base, uint32 limit, uint32 access, uint32 flags)
{
	gdt_entries[index].base_low		= (base & 0xFFFF);
	gdt_entries[index].base_middle	= (base >> 16) & 0xFF;
	gdt_entries[index].base_high	= (base >> 24) & 0xFF;
	gdt_entries[index].limit_low	= (limit & 0xFFFF);
	gdt_entries[index].limit_flags	= ((limit >> 16) & 0x0F) | (flags << 4);
	gdt_entries[index].access		= access;
}

void init_idt()
{
	int i;
	void *isrs[] = {isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7, isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15, isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23, isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31};

	idt_ptr.limit = sizeof(idt_entries)-1;
	idt_ptr.base = (uint32)&idt_entries;

	memset(idt_entries, 0, sizeof(idt_entries));

	for(i = 0; i < 32; ++i)
	{
		id_setup_entry(i, (uint32)isrs[i], 0x08, 0x8E);
	}

	idt_flush((uint32)&idt_ptr);
}


static void idt_setup_entry(uint8 index, uint32 base, uint16 sel, uint8 flags)
{
	idt_entries[index].base_low 	= (base & 0xFFFF);
	idt_entries[index].base_high	= (base >> 16) & 0xFFFF;
	idt_entries[index].sel			= sel;
	idt_entries[index].flags		= flags;
	idt_entries[index]._0			= 0;
}

