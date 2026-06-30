#include <iostream>
#include <stack>
#include <climits>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;


void dfs(int i, int j, vector<vector<char>>& grid, int& m, int& n)
{
	// visited[i][j] = 1;
	grid[i][j] = '2';	// Mark it as visited. Use '2' as visited marker
	
	// UP
	// if ( i-1 >= 0 && visited[i-1][j] == 0 && grid[i-1][j] == '1')
	if ( i-1 >= 0 && grid[i-1][j] == '1')
	{
		dfs(i-1, j, grid, m, n);	
	}
	
	// DOWN
	if ( i+1 < m && grid[i+1][j] == '1')
	{
		dfs(i+1, j, grid, m, n);	
	}
	
	// LEFT
	if ( j-1 >= 0 && grid[i][j-1] == '1')
	{
		dfs(i, j-1, grid, m, n);	
	}
		
	// RIGHT
	if ( j+1 < n && grid[i][j+1] == '1' )
	{
		dfs(i, j+1, grid, m, n);	
	}
}


int numIslands(vector<vector<char>>& grid) 
{
	int m = grid.size();
	int n = grid[0].size();
	int num_islands = 0;
	
	// vector<vector<int>> visited(m, vector<int>(n, 0));
	
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			// if (visited[i][j] == 0 && grid[i][j] == '1')
			if (grid[i][j] == '1')
			{
				num_islands++;
				// dfs(i, j, grid, visited, m, n);
				dfs(i, j, grid, m, n);
			}
		}
	}
	
	return num_islands;
}