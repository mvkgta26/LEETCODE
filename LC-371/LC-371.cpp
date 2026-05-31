#include <cstdint>
#include <cstddef>
#include <iostream>

using namespace std;

constexpr size_t HEADER_SIZE = 8;

int getSum(int a, int b) 
{
	int ci = 0;
	int sum = 0;
	
	// Iterate 31 bits from LSB to MSB, leaving out the 31st bit (sign bit)
	//for (int i=0; i<11; i++)
	for (int i=0; i<32; i++)
	{
		int ai = (a >> i) & 1;		// 1 if ith bit is 1, 0 otherwise. Basically, this is the ith bit in a.
		int bi = (b >> i) & 1;		// 1 if ith bit is 1, 0 otherwise. Basically, this is the ith bit in b.
		sum = sum | ( (ai ^ bi ^ ci) << i );	// Put sum bit in the ith bit
		ci = (ai & bi) | (bi & ci) | (ai & ci);		// Set carry for next bit
	}

	return sum;
}