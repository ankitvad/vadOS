# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler
# rule, as we use nasm instead of GNU as.

SOURCES = main.o start.o common.o monitor.o descriptor_tables.o dt_flush.o
CFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 
LSFLAGS = -Tlink.ld -m elf_i386
ASFLAGS = -felf

all: $(SOURCES) link

clean:
	rm *.o kernel

link:
	ld $(LSFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

