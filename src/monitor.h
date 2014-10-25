
/**
 * monitor.h
 * Functions for writing stuff on the screen in text mode.
 */

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

/* Prints a single character on the screen. */
void monitor_put(char c);

/* Clears the screen. */
void monitor_clear();

/* Prints a null-terminated ASCII string on the screen. */
void monitor_write(char *str);

#endif
