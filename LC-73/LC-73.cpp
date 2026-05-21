/*
	If any element in matrix[i][j] == 0, set the flag in the 0th element of the row-i and the 0th element of the column-i as 0. 0 will be flag.

		Question: What if the 0 row-element or the 0 column element are already 0?
					Setting flag to 0 in the 0 element in the row or column does not change anything. There is already a 0 in the 0th element, so that row or col will be rightly flagged with 0 there.
				
		Question: The data in the 0 element is lost. Is that a problem?
					No, because that row or column has a 0, and so the entire row or column including the 0th element will be changed to 0 anyway.


	Careful: Setting 0 in row-0 and col-0 as flags would confuse if the 0-row and 0-col actually had original 0s. 
			To avoid, have separate flags variables for row-0 and col-0. 
			
	>> Iterate and check row-0 and col-0 and set the flags first so that they dont confuse. 
	>> After that, iterate the entire matrix other than row-0 and col-0 and set the flags.
	>> Finally, set the appropriate rows and cols to 0.

*/


#include <vector>


using namespace std;



void setZeroes(vector<vector<int>>& matrix) 
{
	int m = matrix.size();
	int n = matrix[0].size();
	
	// Corner case: 1 element matrix
	if (m == 1 && n == 1)	return;
	
	int row_0_flag = 0;
	int col_0_flag = 0;
	
	
	// Iterate row-0 and set row_0_flag
	for (int j=0; j<n; j++)
	{
		if(matrix[0][j] == 0)
			row_0_flag = 1;
	}
	
	// Iterate col-0 and set col_0_flag
	for (int i=0; i<m; i++)
	{
		if(matrix[i][0] == 0)
			col_0_flag = 1;
	}
	
	// Iterate all the elements except the first row and the first column on the matrix
	for (int i=1; i<m; i++)
	{
		for (int j=1; j<n; j++)
		{
			// Set flag in the first element of the row and column
			if (matrix[i][j] == 0)
			{
				matrix[i][0] = 0;	// Flag in First element of row
				matrix[0][j] = 0;	// Flag in first element of column
				
			}
		}
	}
	
	
	// Iterate all the rows other than row-0
	for (int i=1; i<m; i++)
	{
		// If flag is set for row, set the entire row as 0
		if (matrix[i][0] == 0)
		{
			for (int j=0; j<n; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}
	
	// Iterate all the columns other than column-0
	for (int j=1; j<n; j++)
	{
		// If flag is set for column, set the entire column as 0
		if (matrix[0][j] == 0)
		{
			for (int i=0; i<m; i++)
			{
				matrix[i][j] = 0;
			}
		}
	}
	
	
	// Check and do for row-0 and col-0, at the last, so that you dont mess with the flags initially
	
	// Row-0
	if (row_0_flag == 1)
	{
		// Set row-0 to 0
		for (int j=0; j<n; j++)
		{
			matrix[0][j] = 0;
		}		
	}
	
	// Column-0
	if (col_0_flag == 1)
	{
		// Set column-0 as 0
		for (int i=0; i<m; i++)
		{
			matrix[i][0] = 0;
		}
	}

}