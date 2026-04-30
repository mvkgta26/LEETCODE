#include <stdio.h>




void detect_endianness()
{
	int num = 1;
	int* p_int = &num;
	unsigned char* p = (unsigned char*) p_int;	// Typecast pointer to char pointer (Only refers 1 byte)
	
	// If Little Endian
	if ( *p == 1 )
	{
		printf("Little Endian");		
	}
	
	else
	{
		printf("Big Endian");
	}
}