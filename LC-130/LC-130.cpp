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
void BFS(vector<vector<char>>& board, int i_source, int j_source)
{
	int m = board.size();	// Num rows
	int n = board[0].size();	// Num cols
	
	// Push source cell coordinates to the BFS-Q and Mark source as visited
	queue<cooordinates> bfs_q;
	cooordinates source_coord = {i_source, j_source};	
	bfs_q.push(source_coord);
	board[i_source][j_source] = '#';	// # : Mark the source land as visited, in-place. NO VISITED ARRAY NEEDED
	
	// ** BFS Loop **
	int i,j;
	while ( !bfs_q.empty() )
	{		
		// ** Retrieve and pop the cell at the que front **
		i = bfs_q.front().x;
		j = bfs_q.front().y;
		bfs_q.pop();

		// ** Neighbor Expansion: Expand unvisited land neighbors **
		if ( (i-1) >= 0 && board[i-1][j] == 'O' )		// Upper Neighbor
		{
			board[i-1][j] = '#';	// # : Mark the neighbor as visited
			cooordinates temp_coord = {i-1, j};
			bfs_q.push(temp_coord);
		}
		
		if ( (i+1) <= m-1 && board[i+1][j] == 'O' )	 // Down Neighbor
		{
			board[i+1][j] = '#';	// # : Mark the neighbor as visited
			cooordinates temp_coord = {i+1, j};
			bfs_q.push(temp_coord);
		}
		
		if ( (j-1) >= 0 && board[i][j-1] == 'O' )	// Left Neighbor
		{
			board[i][j-1] = '#';	// # : Mark the neighbor as visited
			cooordinates temp_coord = {i, j-1};
			bfs_q.push(temp_coord);
		}
		
		if ( (j+1) <= n-1 && board[i][j+1] == 'O' )	 // Right Neighbor
		{
			board[i][j+1] = '#';	// # : Mark the neighbor as visited
			cooordinates temp_coord = {i, j+1};
			bfs_q.push(temp_coord);
		}
	}
}

void solve(vector<vector<char>>& board) 
{
	int m = board.size();	  // Num rows
	int n = board[0].size();  // Num cols
	
	// Edge cases: No surrounded regions possible if board is too small
	if (m <= 2 || n <= 2)
		return;
		
	// ****** Visit all non-surrounded regions: Pick source from border-cells *******
	// Traverse the border cells: If it is an unvisited land cell, perform a BFS from that land-cell to visit all the land-cells in its corresponding region
	int i,j;
	
	// Upper Border
	for (j=0; j<n; j++)
	{
		if (board[0][j] == 'O')
		{
			BFS(board, 0, j);
		}
	}
	
	// Bottom Border
	for (j=0; j<n; j++)
	{
		if (board[m-1][j] == 'O')
		{
			BFS(board, m-1, j);
		}
	}
	
	// Left Border
	for (i=0; i<m; i++)
	{
		if (board[i][0] == 'O')
		{
			BFS(board, i, 0);
		}
	}
	
	
	// Right Border
	for (i=0; i<m; i++)
	{
		if (board[i][n-1] == 'O')
		{
			BFS(board, i, n-1);
		}
	}
	
	
	// ***** Mark all surrounded regions ******
	// Iterate the entire grid, look for land-cells marked with 'O' at this stage. All these land-cells belong to a surrounded region. Mark them as 'X'.
	// Change the land-cells marked as '#' back to 'O'
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
		{
			if (board[i][j] == '#')
				board[i][j] = 'O';
							
			else if (board[i][j] == 'O')
				board[i][j] = 'X';
		}
	}
}

int main()
{
	
}
