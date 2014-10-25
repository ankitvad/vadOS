/**
 * common.h
 * Defines some basic types and functions.
 */

#ifndef COMMON_H
#define COMMON_H

/**
 * Typedefs to standardize the size of integers for 32-bit x86.
 */
typedef unsigned int	uint32;
typedef			 int	int32;
typedef unsigned short	uint16;
typedef 		 short	int16;
typedef unsigned char	uint8;
typedef			 char	int8;

/**
 * Basic I/O functions.
 */
uint8 inb(uint16 port);
void outb(uint16 port, uint8 value);
uint16 inw(uint16 port);

#endif
