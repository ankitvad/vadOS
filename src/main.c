
#include "monitor.h"

/**
 * Kernel entry point function.
 */
int main(struct multiboot *mboot_ptr)
{
	monitor_clear();
	monitor_write("Hello, world!");

    return 0xDEADB00F;
}
