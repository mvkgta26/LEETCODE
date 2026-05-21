/*

Approach-1: Easy:
	Perform transpose and then reverse each row, that will be rotated image

Approach-2: Swap 2 Pointers Approach:
	1. Layer-Number: Iterate each of the concentric layers of the square ( n/2 layers )
		>> Offset: In each concentric square, if m = number of elements in a square side, iterate the first m-1 elements in the side
			>> For each layer and offset: Swap Rotate using 2 pointers:
					[layer_num][layer_num + offset]
					[layer_num + offset][n - 1 - layer_num]
					[n - 1 - layer_num][n - 1 - layer_num - offset]
					[n - 1 - layer_num - offset][layer_num]
					
*/



#include <vector>


using namespace std;



void rotate(vector<vector<int>>& matrix) 
{
	int n = matrix.size();
	int layer_num = 0;
	int offset = 0;
	
	// Half the length of the diagonal is the number of layers. Each element in the diagonal represents a layer.
	// Iterate each of the concentric layers
	for (layer_num = 0; layer_num < n/2; layer_num++)
	{
		// In every side, swap half the elements in that side. 2 cells lost every time we move one layer in
		for (offset=0; offset < n - 2*layer_num - 1; offset++)
		{
			// Swap on 4 sides of square, one by one
			
			// Store Top-left
			int temp1 = matrix[layer_num][layer_num + offset];
			int temp2;
			
			// Place top-left in top-right
			temp2 = matrix[layer_num + offset][n - 1 - layer_num];
			matrix[layer_num + offset][n - 1 - layer_num] = temp1;	
			temp1 = temp2;
			
			// Place top-right in bottom-right
			temp2 = matrix[n - 1 - layer_num][n - 1 - layer_num - offset];
			matrix[n - 1 - layer_num][n - 1 - layer_num - offset] = temp1;	
			temp1 = temp2;
			
			
			// Place bottom-right in bottom-left
			temp2 = matrix[n - 1 - layer_num - offset][layer_num];
			matrix[n - 1 - layer_num - offset][layer_num] = temp1;	
			temp1 = temp2;
			
			
			// Place bottom-left in top-left
			temp2 = matrix[layer_num][layer_num + offset];
			matrix[layer_num][layer_num + offset] = temp1;	
			// temp1 = temp2;	Not needed here
		}
	}
}




void rotate(vector<vector<int>>& matrix) 
{
	int n = matrix.size();

	// Transpose
	
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<i; j++)
		{
			int temp1 = matrix[j][i];
			matrix[j][i] = matrix[i][j];
			matrix[i][j] = temp1;
		}
	}

	
	// Reverse rows
	
	// Iterate rows
	for (int i=0; i<n; i++)
	{
		// Reverse each row
		for (int j=0; j<n/2; j++)
		{
			int temp1 = matrix[i][n-1-j];
			matrix[i][n-1-j] = matrix[i][j];
			matrix[i][j] = temp1;
		}
	}
	
}