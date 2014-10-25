
#include "common.h"

/**
 * Defines one segment.
 */
struct gdt_entry_struct
{
	uint16 limit_low;   //Lower 16 bits of the limit.
	uint16 base_low;    //Lower 16 bits of the base address.
	uint8  base_middle; //Third byte of the base address.
	uint8  access;		//Access flags, specify the ring for this segment.
	uint8  limit_flags;	//Limit's 4 last bits and flags (granularity, size bit) .
	uint8  base_high;	//Last byte of the base address.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

/**
 * Defines the data that must be given to the lgdt instruction. It's got the
 * location of the gdt entries array and its size minus one.
 */
struct gdt_ptr_struct
{
	uint16 limit;	//Size in bytes of the gdt entries array minus 1.
	uint32 base;	//Address of the gdt entries array.
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

/**
 * Defines on interrupt
 */
struct idt_entry_struct
{
	uint16 base_low;	//Lower 16 bits of the address of the interrupt routine.
	uint16 sel;			//Kernel segment selector
	uint8  _0;			//Reserved, always 0
	uint8  flags;		//Flags (always present, ring, 0b00110)
	uint16 base_high;	//Upper 16 bits of the address.
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

/**
 * Data structure for the lidt instruction containing the address and size of the
 * array of interrupt handlers.
 */
struct idt_ptr_struct
{
	uint16 limit;
	uint32 base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

/**
 * Initializes the GDT and IDT, and set them using the lgdt and lidt instructions.
 */
void init_descriptor_tables();

/**
 * Interrupt Service Routines - ISRs
 */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
