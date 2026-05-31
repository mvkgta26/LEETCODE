#include <iostream>
#include <algorithm>
#include <semaphore.h>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <cstdlib>

using namespace std;


int main()
{
	int m = 10;
	int n = 5;
	
	// Array of m int* pointers
	int** arr = (int**) malloc(m * sizeof(int *));
	
	for (int i=0; i<m; i++)
	{
		arr[i] = (int *) malloc(n * sizeof(int));
	}
	
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			arr[i][j] = i*5 + j;
		}
	}
	
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			cout << arr[i][j] << " ";
		}
		
		cout << endl;
	}
	
	
	// Clear up the array memory
	for (int i=0; i<m; i++)
	{
		free(arr[i]);
	}
	
	free(arr);
	
	return 1;
}
