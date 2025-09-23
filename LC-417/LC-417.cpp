#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
/*
int dfs_check_ocean_reachable(vector<vector<int>>& heights, int i, int j, int& m, int& n, vector<vector<bool>>& visited, vector<vector<bool>>& reaches_pacific, vector<vector<bool>>& reaches_atlantic)
{
	
	visited[i][j] = 1;	// Mark the current cell as visited
	
	// Exit conditions
	// If current cell is on pacific ocean border (top row or left column)
	if ( i == 0 || j == 0 )
	{
		reaches_pacific[i][j] = 1; 
	}
	
	// If current cell is on atlantic ocean border (bottom row or right column)
	if ( i == m-1 || j == n-1 )
	{
		reaches_atlantic[i][j] = 1;
	}
	
	// ******** Recursive DFS calls *********
		// **** DFS call on the lower cell ****
		if ((i+1 < m) && visited[i+1][j] == 0)
		{	
			dfs_check_ocean_reachable(heights, i+1, j, m, n, visited, reaches_pacific, reaches_atlantic);
		}
		
		//  **** DFS call on the left cell ****
		if ((j-1 >= 0) && visited[i][j-1] == 0)
		{
			dfs_check_ocean_reachable(heights, i, j-1, m, n, visited, reaches_pacific, reaches_atlantic);
		}

	return 0;
	
}



vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) 
{
	int m = heights.size();	// Number of rows
	int n = heights[0].size(); // Number of columns
	
	// Create a visited array to mark if a cell has been visite during DFS
	vector<vector<bool>> visited(m, vector<bool>(n, 0));
	
	// Create hash maps to mark if a cell can reach pacific and atlantic oceans.
	vector<vector<bool>> reaches_pacific(m, vector<bool>(n, 0));
	vector<vector<bool>> reaches_atlantic(m, vector<bool>(n, 0));
	
	
	// Iterate the visited array
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{	
			// Call dfs on unvisited nodes
			if (visited[i][j] == 0)
			{
				//visited[i][j] = 1;
				dfs_check_ocean_reachable(heights, i, j, m, n, visited, reaches_pacific, reaches_atlantic);
			}
		}
	}
	
	
	// DP Steps: To check path through all the directions
	// Run multiple iterations until no more changes occur
	bool changed = true;
	while (changed)
	{
		changed = false;
		for (int i=0; i<m; i++)
		{
			for (int j=0; j<n; j++)
			{
				bool old_pacific = reaches_pacific[i][j];
				bool old_atlantic = reaches_atlantic[i][j];
				
				// Check down neighbor
				if (i+1 < m && heights[i+1][j] <= heights[i][j])
				{
					reaches_pacific[i][j] = reaches_pacific[i][j] || reaches_pacific[i+1][j];
					reaches_atlantic[i][j] = reaches_atlantic[i][j] || reaches_atlantic[i+1][j];
				}
				
				// Check up neighbor
				if (i-1 >= 0 && heights[i-1][j] <= heights[i][j])
				{
					reaches_pacific[i][j] = reaches_pacific[i][j] || reaches_pacific[i-1][j];
					reaches_atlantic[i][j] = reaches_atlantic[i][j] || reaches_atlantic[i-1][j];
				}
				
				// Check right neighbor
				if (j+1 < n && heights[i][j+1] <= heights[i][j])
				{
					reaches_pacific[i][j] = reaches_pacific[i][j] || reaches_pacific[i][j+1];
					reaches_atlantic[i][j] = reaches_atlantic[i][j] || reaches_atlantic[i][j+1];
				}
				
				// Check left neighbor
				if (j-1 >= 0 && heights[i][j-1] <= heights[i][j])
				{
					reaches_pacific[i][j] = reaches_pacific[i][j] || reaches_pacific[i][j-1];
					reaches_atlantic[i][j] = reaches_atlantic[i][j] || reaches_atlantic[i][j-1];
				}
				
				// Check if any changes occurred
				if (reaches_pacific[i][j] != old_pacific || reaches_atlantic[i][j] != old_atlantic)
				{
					changed = true;
				}
			}
		}
	}
	
	// Iterate the island grid and find out all the cells that have routest to both the oceans
	vector<vector<int>> solutions;
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (reaches_pacific[i][j] && reaches_atlantic[i][j])
			{
				solutions.push_back({i, j});
			}
		}
	}
	
	return solutions;
}
*/

int dfs_check_ocean_reachable( vector<vector<int>>& heights, int i, int j, int& m, int& n, vector<vector<bool>>& reaches_ocean )
{
	reaches_ocean[i][j] = 1;	// Mark the current land-cell as reachable fron the current ocean
	
	// ******** Recursive DFS calls *********
		// **** DFS call on the lower cell ****
		// Check if it is higher and is not already visited by the current ocean. Also check edge case.
		if ((i+1 < m) && ( heights[i+1][j] >= heights[i][j] ) && reaches_ocean[i+1][j] == 0)
		{	
			dfs_check_ocean_reachable(heights, i+1, j, m, n, reaches_ocean);
		}
		
		//  **** DFS call on the left cell ****
		// Check if it is higher and is not already visited by the current ocean. Also check edge case.
		if ((j-1 >= 0) && ( heights[i][j-1] >= heights[i][j] ) && reaches_ocean[i][j-1] == 0)
		{
			dfs_check_ocean_reachable(heights, i, j-1, m, n, reaches_ocean);
		}
		
		//  **** DFS call on the upper cell ****
		// Check if it is higher and is not already visited by the current ocean. Also check edge case.
		if ((i-1 >= 0) && ( heights[i-1][j] >= heights[i][j] ) && reaches_ocean[i-1][j] == 0)
		{
			dfs_check_ocean_reachable(heights, i-1, j, m, n, reaches_ocean);
		}
				
		//  **** DFS call on the right cell ****
		// Check if it is higher and is not already visited by the current ocean. Also check edge case.
		if ((j+1 < n) && ( heights[i][j+1] >= heights[i][j] ) && reaches_ocean[i][j+1] == 0)
		{
			dfs_check_ocean_reachable(heights, i, j+1, m, n, reaches_ocean);
		}
		
	return 0;
}

vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) 
{
	int m = heights.size();	// Number of rows
	int n = heights[0].size(); // Number of columns
		
	// Create hash maps to mark if a cell can reach pacific and atlantic oceans.
	vector<vector<bool>> reaches_pacific(m, vector<bool>(n, 0));
	vector<vector<bool>> reaches_atlantic(m, vector<bool>(n, 0));
	
	int i, j;
	// Iterate Upper wall to the pacific ocean 
	i = 0;
	for (int j=0; j<n; j++)
	{	
		dfs_check_ocean_reachable(heights, i, j, m, n, reaches_pacific);
	}
	
	// Iterate Left wall to the pacific ocean
	j = 0;
	for (int i=0; i<m; i++)
	{	
		dfs_check_ocean_reachable(heights, i, j, m, n, reaches_pacific);
	}
	
	// Iterate lower wall to the atlantic ocean 
	i = m-1;
	for (int j=0; j<n; j++)
	{	
		dfs_check_ocean_reachable(heights, i, j, m, n, reaches_atlantic);
	}
		
	// Iterate right wall to the atlantic ocean 
	j = n-1;
	for (int i=0; i<m; i++)
	{	
		dfs_check_ocean_reachable(heights, i, j, m, n, reaches_atlantic);
	}

	
	// Iterate the island grid and find out all the cells that have routes to both the oceans
	vector<vector<int>> solutions;
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (reaches_pacific[i][j] && reaches_atlantic[i][j])
			{
				solutions.push_back({i, j});
			}
		}
	}
	
	return solutions;
}


int main()
{
	
}