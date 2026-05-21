/*
	Idea: Maintain 4 boudaries: left, right, top and bottom
			Maintain a direction number, and rotate through the directions

	For right direction: Fix top, iterate left to right. Update top.
	For Down direction: Fix right, iterate top to bottom. Update right.
	For Left direction: Fix bottom, iterate right to left. Update bottom.
	For Up direction: Fix left, iterate bottom to top. Update left.
	
*/


#include <vector>


using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) 
{
	int m = matrix.size();
	int n = matrix[0].size();
	
	vector<int> output;
	
	int top = 0;
	int bottom = m-1;
	int left = 0;
	int right = n-1;
	
	int direction = 0;	// Rightward
	// int direction = 1;	// Down
	// int direction = 2;	// Leftward
	// int direction = 3;	// Up
	
	while (top <= bottom && left <= right)
	{
		// Right
		if (direction == 0)
		{
			for (int j=left; j<=right; j++)
			{
				output.push_back(matrix[top][j]);
			}
			
			top++;	// Update top border
		}
		
		// Down
		else if (direction == 1)
		{
			for (int i=top; i<=bottom; i++)
			{
				output.push_back(matrix[i][right]);
			}
			
			right--;	// Update right border
		}
		
		// Left
		else if (direction == 2)
		{
			for (int j=right; j>=left; j--)
			{
				output.push_back(matrix[bottom][j]);
			}
			
			bottom--;		// Update bottom border
		}
		
		// Up
		else if (direction == 3)
		{
			for (int i=bottom; i>=top; i--)
			{
				output.push_back(matrix[i][left]);
			}
			
			left++;		// Update left border
		}
		
		
		direction = (direction + 1) % 4;		// Update direction for next traversal
	}
	
	return output;
}