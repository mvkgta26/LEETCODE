#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
#include <cctype>
#include <algorithm>



using namespace std;


int dfs(int i, int j, vector<vector<char>>& grid, vector<vector<int>>& visited)
{
	visited[i][j] = 1;
	
	int m = grid.size();
	int n = grid[0].size();
	
	// Down
	if ( (i-1 >= 0) && (grid[i-1][j] == '1') && !visited[i-1][j] )
	{
		dfs(i-1, j, grid, visited);
	}
	
	// Up
	if ( (i+1 < m) && (grid[i+1][j] == '1') && !visited[i+1][j] )
	{
		dfs(i+1, j, grid, visited);
	}

	// Left
	if ( (j-1 >= 0) && (grid[i][j-1] == '1') && !visited[i][j-1] )
	{
		dfs(i, j-1, grid, visited);
	}
	
	// Right
	if ( (j+1 < n) && (grid[i][j+1] == '1') && !visited[i][j+1] )
	{
		dfs(i, j+1, grid, visited);
	}
	
	
	return 0;
}


int numIslands(vector<vector<char>>& grid) 
{
	if (grid.empty() || grid[0].empty()) return 0;
	
	int m = grid.size();
	int n = grid[0].size();
	int island_count = 0;
	
	vector<vector<int>> visited(m, vector<int> (n,0));
	
	
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			if ( grid[i][j] == '1' && !visited[i][j] )
			{	
				island_count++;
				dfs(i, j, grid, visited);	
			}
		}		
	}
	
	return island_count;
}