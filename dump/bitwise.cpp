#include <iostream>
#include <algorithm>
#include <semaphore.h>
#include <mutex>
#include <vector>
#include <unordered_map>

using namespace std;



// Hex: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F


uint32_t byte_swap_func(uint32_t n)
{
	uint32_t a = n << 8;
	a =  a & 0xFF00FF00;
	
	uint32_t b = n >> 8;
	b = b & 0x00FF00FF;
	
	uint32_t out = a | b;
	
	return out;
}


uint32_t bit_swap_func(uint32_t n)
{
	uint32_t a = n >> 1;
	uint32_t b = n << 1;
	a = a & 0x55555555;
	b = b & 0xAAAAAAAA;
	
	uint32_t out = a | b;
	
	return out;
}


int main()
{

	
	return 1;
}