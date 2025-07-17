#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

// DFS iteration over the grid, traverse the entire current island and count the number of blocks in the island. 
// Only dummy return value, the island area is counted using a static variable.
int DFS(vector<vector<int>>& grid, int& m, int& n, int i, int j, int& island_area) //, vector<vector<int>>& visited)
{
	// If current block is a land block, count it for island_area
	// Check if there is an univisited land block in the grid in the position i, j
	if ( (i>=0) && (i<m) && (j>=0) && (j<n) && (grid[i][j] == 1) ) // && (visited[i][j]==0)
	{
		island_area++;
		//visited[i][j] = 1;
		grid[i][j] = 0; // Make it as 0 to ensure that you dont count this again

		DFS(grid, m, n, i, j-1, island_area); //, visited);  // Left
		DFS(grid, m, n, i, j+1, island_area); //, visited);  // Right
		DFS(grid, m, n, i+1, j, island_area); //, visited);  // Down
		DFS(grid, m, n, i-1, j, island_area); //, visited);  // Up
	}
	
	return 0;	// Dummy return
}

int maxAreaOfIsland(vector<vector<int>>& grid) 
{
	int m = grid.size();	// Num rows
	int n = grid[0].size();		// Num columns
	
	//vector<vector<int>> visited(m, vector<int>(n, 0));	// 2D visited array of [m,n] dimensions. To mark if block visited during DFS

	
	int max_island_area = -1;
	
	// Iterate the grid, row by row
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<n; j++)
		{
			int island_area = 0;
			
			DFS(grid, m, n, i, j, island_area); //, visited);
			max_island_area = max(island_area, max_island_area);    // If current island_area is the max
		}
	}
	
	return max_island_area;
}


int main()
{ 
	cout << "Hello";
	
	return 0;
}