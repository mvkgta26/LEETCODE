#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

struct cooordinates
{
	int x;
	int y;
};

// Perform BFS with source cell (i,j)
void BFS(vector<vector<char>>& board, vector<vector<int>>& visited, int i_source, int j_source, int surrounded_region)
{
	int m = board.size();	// Num rows
	int n = board[0].size();	// Num cols
	
	// Push source cell coordinates to the BFS-Q
	queue<cooordinates> bfs_q;
	cooordinates source_coord = {i_source, j_source};	
	bfs_q.push(source_coord);
	
	
	int i,j;
	while ( !bfs_q.empty() )
	{		
		// ** Process the current cell **
		// Retrieve and pop the cell at the que front
		i = bfs_q.front().x;
		j = bfs_q.front().y;
		bfs_q.pop();
		
		visited[i][j] = 1;	// Mark the current land as visited
		if (surrounded_region == 1)	// If the land is part of a surrounded region, change 'O' to 'X'
		{
			board[i][j] = 'X';
		}
		
		// ** Neighbor Expansion: Expand unvisited land neighbors **
		if ( (i-1) >= 0 && visited[i-1][j] == 0 && board[i-1][j] == 'O' )		// Upper Neighbor
		{
			cooordinates temp_coord = {i-1, j};
			bfs_q.push(temp_coord);
		}
		
		if ( (i+1) <= m-1 && visited[i+1][j] == 0 && board[i+1][j] == 'O' )	 // Down Neighbor
		{
			cooordinates temp_coord = {i+1, j};
			bfs_q.push(temp_coord);
		}
		
		if ( (j-1) >= 0  && visited[i][j-1] == 0 && board[i][j-1] == 'O' )	// Left Neighbor
		{
			cooordinates temp_coord = {i, j-1};
			bfs_q.push(temp_coord);
		}
		
		if ( (j+1) <= n-1  && visited[i][j+1] == 0 && board[i][j+1] == 'O' )	 // Right Neighbor
		{
			cooordinates temp_coord = {i, j+1};
			bfs_q.push(temp_coord);
		}
		
	}
}

void solve(vector<vector<char>>& board) 
{
	int m = board.size();	  // Num rows
	int n = board[0].size();  // Num cols
	
	// Edge cases: Surely no surrounded regions. You need minimum 3x3 board to make at least one surrounded region
	if (m <= 2 && n <=2)
		return;
		
	// Visited array of mxn
	vector<vector<int>> visited(m, vector<int>(n,0));
	
	
	// ****** Visit all non-surrounded regions: Choose source from border-cells *******
	// Traverse the border cells
	int i,j;
	int surrounded_region = 0;	// Flag : Mark if BFS is performed from a surrounded region or non-surrounded region
	
	// Upper Border
	for (j=0; j<n; j++)
	{
		// If it is an unvisited land cell, perform a BFS from that land-cell to visit all the land-cells in its corresponding region
		if ((visited[0][j] == 0) && (board[0][j] == 'O'))
		{
			BFS(board, visited, 0, j, surrounded_region);
		}
	}
	
	// Bottom Border
	for (j=0; j<n; j++)
	{
		// If it is an unvisited land cell, perform a BFS from that land-cell to visit all the land-cells in its corresponding region
		if ((visited[m-1][j] == 0) && (board[m-1][j] == 'O'))
		{
			BFS(board, visited, m-1, j, surrounded_region);
		}
	}
	
	// Left Border
	for (i=0; i<m; i++)
	{
		// If it is an unvisited land cell, perform a BFS from that land-cell to visit all the land-cells in its corresponding region
		if ((visited[i][0] == 0) && (board[i][0] == 'O'))
		{
			BFS(board, visited, i, 0, surrounded_region);
		}
	}
	
	
	// Right Border
	for (i=0; i<m; i++)
	{
		// If it is an unvisited land cell, perform a BFS from that land-cell to visit all the land-cells in its corresponding region
		if ((visited[i][n-1] == 0) && (board[i][n-1] == 'O'))
		{
			BFS(board, visited, i, n-1, surrounded_region);
		}
	}
	
	
	// ***** Visit all surrounded regions ******
	// Iterate the entire grid, look for univisted land-cells. All these land-cells belong to a surrounded region.
	surrounded_region = 1; 	// Set the flag: We are now visiting surrounded regions 
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
		{
			if ((visited[i][j] == 0) && (board[i][j] == 'O'))
			{
				BFS(board, visited, i, j, surrounded_region);
			}
		}
	}
}

int main()
{
	
}
