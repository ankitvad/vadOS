
/**
 * monitor.c
 * Defines the basic monitor functions.
 */

#include "monitor.h"

static uint16 vga_control_port = 0x3D4;
static uint16 vga_data_port = 0x3D5;
static uint16 *vga_video_memory = (uint16 *)0xB8000;
static uint8 vga_cursor_location_high = 0xE;
static uint8 vga_cursor_location_low = 0xF;
static uint16 screen_width = 80;
static uint16 screen_height = 25;
static uint16 cursor_y = 0, cursor_x = 0;

/**
 * Updates the vga cursor location to reflect the contents of cursor_x and cursor_y.
 */
static void move_cursor()
{
	uint16 cursor_location = cursor_y * screen_width + cursor_x;

	//Send high cursor byte
	outb(vga_control_port, vga_cursor_location_high);
	outb(vga_data_port, cursor_location >> 8);

	//Send low cursor byte
	outb(vga_control_port, vga_cursor_location_low);
	outb(vga_data_port, cursor_location & 0xFF);
}

/**
 * Scrolls the text on the screen up one line, if necessary.
 */
static void scroll()
{
	//If the cursor is at or after the last line, scroll up
	if(cursor_y >= screen_height)
	{
		int i;

		for(i = 0; i < screen_width*(screen_height-1); ++i)
		{
			vga_video_memory[i] = vga_video_memory[i + screen_width];	
		}

		for(i = screen_width*(screen_height-1); i<screen_width*screen_height; ++i)
		{
			vga_video_memory[i] = 0x0F20;//black space
		}

		cursor_y = 24;
	}
}

/**
 * Prints a single character to the screen.
 */
void monitor_put(char c)
{
	if(c == 0x08) //Backspace: move cursor back one position horizontally
	{
		--cursor_x;
	}
	else if(c == '\t') //Tab: move cursor to the next location divisible by 4
	{
		cursor_x = (cursor_x + 4) & ~(4-1);
	}
	else if(c == '\r') //Carriage return: set cursor_x to 0
	{
		cursor_x = 0;
	}
	else if(c == '\n') //New line: set cursor_x to 0 and increment cursor_y
	{
		cursor_x = 0;
		++cursor_y;
	}
	else if(c >= ' ') //Printable characters
	{
		vga_video_memory[cursor_y*screen_width + cursor_x] = 0x0F00 | c;
		++cursor_x;
	}

	if(cursor_x >= 80) //If cursor goes past the right of the screen, start a new line
	{
		cursor_x = 0;
		++cursor_y;
	}

	//Update scroll and cursor location
	scroll();
	move_cursor();
}

/**
 * Clears the screen by filling it with spaces.
 */
void monitor_clear()
{
	int i;

	for(i = 0; i < screen_width*screen_height; ++i)
	{
		vga_video_memory[i] = 0x0F20;
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

/**
 * Prints a null-terminated ASCII string to the screen.
 */
void monitor_write(char *str)
{
	while(*str != 0)
	{
		monitor_put(*str++);
	}
}
