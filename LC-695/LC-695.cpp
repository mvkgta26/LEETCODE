/*
	Algorithm:
		1. Iterate all the blocks of the grid one by one
			2. If the block is an 'unvisited' land, perform a DFS of all the univisited lands connected to this block. The DFS will traverse <ALL> the connected land elements (hence all elements of the island to which this block belongs to). 
				2.1. Count the number of blocks in the island as the DFS is performed.
			3. Find the max of all such island areas calculated at each DFS.

	How to mark visited land blocks??
		Method 1: Maintain a visited array of size m*n
		Method 2: Just make the grid element to 0 (mark it as water) once it is visited and counted.

		Why would method 2 work??
			When you encounter a land block of an island (The top-left most land of any island): You performs DFS to all the elements in the island the block is in.
			When you do this DFS, you mark/change all this land in this island as water, and count them for the island.
			Later, when you iterate through the grid, even when you come across this block, you will not perform a DFS or count it as land since it is marked as water.
			This way the lands in each island is just counted once.
*/

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