// Implement a function that waits for a hardware status register to indicate that a device is ready.
// You are given a memory-mapped 32-bit status register. Bit 0 is the READY bit.
// Write a function:
// int wait_until_ready(volatile uint32_t *status_reg, uint32_t timeout);
// Requirements:
// Return 0 if the device becomes ready.
// Return -1 if the device does not become ready before the timeout expires.
// You must avoid an infinite optimized polling loop.


#include <stdint.h>

// Create unsigned int literal 1.
// << 0 is useless. 0 is just to mention the bit that is to be masked
#define READY_BIT (1u << 0)


int wait_until_ready(volatile uint32_t *status_reg, uint32_t timeout);

int wait_until_ready(volatile uint32_t *status_reg, uint32_t timeout)
{
	while (timeout > 0)
	{
		// if ( (*status_reg & READY_BIT) )
		if ( (*status_reg & 1) == 1 )
		{
			return 0;
		}
		
		timeout--;
	}
	
	return -1; 
}
