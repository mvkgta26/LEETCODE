#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

/*
int dfs_helper(vector<vector<int>>& heights, int i, int j, int& m, int& n, vector<vector<bool>>& visited, vector<vector<bool>>& reaches_pacific, vector<vector<bool>>& reaches_atlantic)
{
	
	// Mark the current cell as visited
	visited[i][j] = 1;
	
	// Exit conditions
	// If current cell neighbors pacific ocean, mark this cell as accessible to pacific ocean and return 1
	if ( i-1 < 0 || j-1 < 0 )
	{
		reaches_pacific[i][j] = 1; 
		return 1;	// 1 is code for pacific ocean
	}
	
	// If current cell neighbors atlantic ocean, mark this cell as accessible to atlantic ocean and return 2
	if ( i+1 >= m-1 || j+1 >= n-1 )
	{
		reaches_atlantic[i][j] = 1;
		return 2;  // 2 is code for atlantic ocean
	}
	
	int island_reached = 0;
	
	// Recursive dfs call
	// **** DFS call on the lower cell ****
	if ( heights[i+1][j] <= heights[i][j] )    //(i+1 < m) && 
	{
		island_reached = dfs_helper(heights, i+1, j, m, n, visited, reaches_pacific, reaches_atlantic);
		
		if (island_reached==1)
		{
			reaches_pacific[i][j] = 1;
			return 1;
		}
		
		if (island_reached==2)
		{
			reaches_atlantic[i][j] = 1;
			return 2;
		}
	}
	
	
	
	// **** DFS call on the upper cell ****
	
	if ( heights[i-1][j] <= heights[i][j] )	//(i-1 >= 0) &&
	{
		island_reached = dfs_helper(heights, i-1, j, m, n, visited, reaches_pacific, reaches_atlantic);
		
		if (island_reached==1)
		{
			reaches_pacific[i][j] = 1;
			return 1;
		}
		
		if (island_reached==2)
		{
			reaches_atlantic[i][j] = 1;
			return 2;
		}
	}
	
	//  **** DFS call on the right cell **** 
	if ( heights[i][j+1] <= heights[i][j] )	// (j+1 < n) &&
	{
		island_reached = dfs_helper(heights, i, j+1, m, n, visited, reaches_pacific, reaches_atlantic);
		
		if (island_reached==1)
		{
			reaches_pacific[i][j] = 1;
			return 1;
		}
		
		if (island_reached==2)
		{
			reaches_atlantic[i][j] = 1;
			return 2;
		}
	}
		
	//  **** DFS call on the left cell ****
	if ( heights[i][j-1] <= heights[i][j] )	// (j-1 >= 0) && 
	{
		island_reached = dfs_helper(heights, i, j-1, m, n, visited, reaches_pacific, reaches_atlantic);
		
		if (island_reached==1)
		{
			reaches_pacific[i][j] = 1;
			return 1;
		}
		
		if (island_reached==2)
		{
			reaches_atlantic[i][j] = 1;
			return 2;
		}
	}	
	
	
	return 0;
}
*/

int check_ocean_reachable_dfs(vector<vector<int>>& heights, int i, int j, int& m, int& n, vector<vector<bool>>& visited, vector<vector<bool>>& reaches_pacific, vector<vector<bool>>& reaches_atlantic)
{
	
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
				dfs_helper(heights, i, j, m, n, visited, reaches_pacific, reaches_atlantic);
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


int main()
{
	
}