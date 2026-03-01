

uint32_t reverseBits(uint32_t n) 
{
	uint32_t reversed = 0;

	for (int i=31; i>=0; i--)
	{
		// Mask and take the 0th bit alone from n, and move it to i'th position.
		// OR it with 'reversed'  
		reversed = reversed | ( (n & 1) << i ) ;
		n = n >> 1;
	}

	return reversed;
}