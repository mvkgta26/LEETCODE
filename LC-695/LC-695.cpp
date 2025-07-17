#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

// DFS iteration over the grid, traverse the entire current island and count the number of blocks in the island. 
// Only dummy return value, the island area is counted using a static variable.
int DFS(vector<vector<int>>& grid, int& m, int& n, int i, int j, int& island_area, vector<vector<int>>& visited)
{
	visited[i][j] = 1;

	// If current block is a land block, count it for island_area
	if (grid[i][j] == 1)
	{
		island_area++;
	}
	
	// Check the left element. Call DFS if left element is an unvisited land
	if ( (j-1)>=0 && visited[i][j-1] == 0 && grid[i][j-1] == 1 )
	{
		DFS(grid, m, n, i, j-1, island_area, visited);
	}
	
	// Check the right element. Call DFS if right element is an unvisited land
	if ( (j+1)<n && visited[i][j+1] == 0 && grid[i][j+1] == 1 )
	{
		DFS(grid, m, n, i, j+1, island_area, visited);
	}

	// Check the down element. Call DFS if down element is an unvisited land
	if ( (i+1)<m && visited[i+1][j] == 0 && grid[i+1][j] == 1 )
	{
		DFS(grid, m, n, i+1, j, island_area, visited);
	}

	// Check the up element. Call DFS if up element is an unvisited land
	if ( (i-1)>=0 && visited[i-1][j] == 0 && grid[i-1][j] == 1 )
	{
		DFS(grid, m, n, i-1, j, island_area, visited);
	}

	return 0;	// Dummy return
}



int maxAreaOfIsland(vector<vector<int>>& grid) 
{
	int m = grid.size();	// Num rows
	int n = grid[0].size();		// Num columns
	
	vector<vector<int>> visited(m, vector<int>(n, 0));	// 2D visited array of [m,n] dimensions. To mark if block visited during DFS
	
	int max_island_area = -1;
	
	// Iterate the grid, row by row
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<n; j++)
		{
			int island_area = 0;
			
			// If you encounter an unvisited land block, initiate DFS to traverse over the entire land surrounding it
			if (visited[i][j] == 0 && grid[i][j] == 1)
			{
				DFS(grid, m, n, i, j, island_area, visited);
			}
			
			// Max check
			if (island_area > max_island_area)
			{
				cout << "Island Area: " << island_area << "\n";
				max_island_area = island_area;
			}
		}
	}
	
	return max_island_area;
}

int main()
{ 
	cout << "Hello";
	
	return 0;
}