#include <stdlib.h>

void main()
{
	int * p = (int *) malloc(10*sizeof(int));	
	p[2] = 10;
	free(p);
	
	
	//int* arr = new int[10];
	int* arr = new int[10]();
	arr[2] = 10;
	delete[] arr;
	
}

