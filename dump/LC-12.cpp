#include <vector>
#include <queue>

using namespace std;


struct coord
{
	int x;
	int y;
};


void BFS(vector<vector<char>>& board, int x, int y, char visit_char)
{
	int m = board.size();		// Max y coord
	int n = board[0].size();	// Max x coord
	
	struct coord src;
	src.x = x; src.y = y;
	
	queue<coord> bfs_que;
	bfs_que.push(src);
	board[src.y][src.x] = visit_char;
	// board[][]
	
	
	while ( !bfs_que.empty() )
	{
		struct coord curr_cell = bfs_que.front();	bfs_que.pop();
		int curr_x = curr_cell.x;
		int curr_y =  curr_cell.y;
		int nbr_x, nbr_y;
		
		// board[curr_y][curr_x] = visit_char;	//Mark current node as visited 
		
		struct coord nbr_coord;
		
		// Upper neighbor
		nbr_x = curr_x;
		nbr_y = curr_y - 1; 
		if ( ( nbr_y >= 0 ) && ( board[nbr_y][nbr_x] == 'O' ) )
		{
			nbr_coord.x = nbr_x; 
			nbr_coord.y = nbr_y;
			// visited[nbr_x][nbr_y] = 1;
			board[nbr_y][nbr_x] = visit_char;	// Mark neighbor as visited
			
			bfs_que.push(nbr_coord);	
		}
		
		// Down neighbor
		nbr_x = curr_x;
		nbr_y = curr_y + 1; 
		if ( ( nbr_y < m ) && ( board[nbr_y][nbr_x] == 'O' ) )
		{
			nbr_coord.x = nbr_x; 
			nbr_coord.y = nbr_y;
			// visited[nbr_x][nbr_y] = 1;
			board[nbr_y][nbr_x] = visit_char;	// Mark neighbor as visited
			
			bfs_que.push(nbr_coord);	
		}
		
		// Left neighbor
		nbr_x = curr_x - 1;
		nbr_y = curr_y; 
		if ( ( nbr_x >= 0 ) && ( board[nbr_y][nbr_x] == 'O' ) )
		{
			nbr_coord.x = nbr_x; 
			nbr_coord.y = nbr_y;
			// visited[nbr_x][nbr_y] = 1;
			board[nbr_y][nbr_x] = visit_char;	// Mark neighbor as visited
			
			bfs_que.push(nbr_coord);	
		}
		
		// Right neighbor
		nbr_x = curr_x + 1;
		nbr_y = curr_y; 
		if ( ( nbr_x < n )  && ( board[nbr_y][nbr_x] == 'O' ) )
		{
			nbr_coord.x = nbr_x; 
			nbr_coord.y = nbr_y;
			// visited[nbr_x][nbr_y] = 1;
			board[nbr_y][nbr_x] = visit_char;	// Mark neighbor as visited
			
			bfs_que.push(nbr_coord);	
		}	
	}
}


class Solution 
{
	public:
		void solve(vector<vector<char>>& board) 
		{
			int m = board.size();
			int n = board[0].size();
			int i, j;
			
			// board[y_coord][x_coord]
			
			// --- Mark all the islands on the edges as visited ---
			
			// Left edge
			for (int y = 0; y < m; y++)
			{
				if (board[y][0] == 'O')
				{
					BFS(board, 0, y, '#');
				}
			}
			
			// Right edge
			for (int y = 0; y < m; y++)
			{
				if (board[y][n - 1] == 'O')
				{
					BFS(board, n - 1, y, '#');
				}
			}
			
			// Up edge
			for (int x = 0; x < n; x++)
			{
				if (board[0][x] == 'O')
				{
					BFS(board, x, 0, '#');
				}
			}
			
			// Down edge
			for (int x = 0; x < n; x++)
			{
				if (board[m - 1][x] == 'O')
				{
					BFS(board, x, m - 1, '#');
				}
			}
			

			
			// Iterate the entire board and convert all the islands from 'O' to 'X'
			for (int y = 0; y < m; y++)
			{
				for (int x = 0; x < n; x++)
				{
					if (board[y][x] == 'O')
					{
						board[y][x] = 'X';
					}	
				}
			}
			
			// Iterate the entire board and convert all the boundary islands from '#' to 'O'
			for (int y = 0; y < m; y++)
			{
				for (int x = 0; x < n; x++)
				{
					if (board[y][x] == '#')
					{
						board[y][x] = 'O';
					}	
				}
			}
			
		}
};