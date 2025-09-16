#include <vector>
#include <queue>

using namespace std;

struct rotten_cell
{
	int x=-1;
	int y=-1;
	int rotten_minute=0;	// The exact minute when the orange in this cell became rotten
};

int orangesRotting(vector<vector<int>>& grid) 
{
	int m = grid.size();
	int n = grid[0].size();
	
	vector<vector<int>> visited(m, vector<int>(n, 0)); 	// Visited array to track which nodes are visited
	//vector<vector<int>> distance_arr;  //--- 
	
	queue<rotten_cell> bfs_que;
	
	
	// Iterate the grid and push all the rotten orange cells to the queue
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			// If orange in this cell is rotten, set its coordinates and push it to the queue
			if (grid[i][j] == 2)
			{
				struct rotten_cell temp_cell;
				temp_cell.x=i;
				temp_cell.y=j;
				temp_cell.rotten_minute = 0;  // Initial rotten oranges start at minute 0
				
				bfs_que.push(temp_cell);
			}
		}
	}
	
	//------Perform BFS------
	int max_rot_min = -1;		// Will hold the minute in which all the oranges are done rotting.
	
	while (!bfs_que.empty())
	{
		// Take the rotten cell at the front of the bfs que
		struct rotten_cell curr_node = bfs_que.front();
		bfs_que.pop();
		
		int x_curr = curr_node.x;
		int y_curr = curr_node.y;
		
		//Mark curr_node as visited
		max_rot_min = max(max_rot_min, curr_node.rotten_minute);	// To hold the highest rotting minute among all the nodes that are visited in BFS
		visited[x_curr][y_curr] = 1;
		
		//Expand rot to neighbors
		
		// Left neighbor. Check if left neighbor is: within bounds, not already visited, and if it is fresh.
		if ( (x_curr-1 >= 0) && (visited[x_curr-1][y_curr] != 1) && (grid[x_curr-1][y_curr] == 1) )
		{
			struct rotten_cell temp_node;
			temp_node.x = x_curr-1;
			temp_node.y = y_curr;
			temp_node.rotten_minute = curr_node.rotten_minute + 1;	// *Increase the rot minute for the neighbor. It will be rotten in the next minute in which the current node rotted.	
		
			bfs_que.push(temp_node);	// Push the neighbor with its parameters set.
		}
		
		// Right neighbor. Check if right neighbor is: within bounds, not already visited, and if it is fresh.
		if ( (x_curr+1 <= n-1) && (visited[x_curr+1][y_curr] != 1) && (grid[x_curr+1][y_curr] == 1) )
		{
			struct rotten_cell temp_node;
			temp_node.x = x_curr+1;
			temp_node.y = y_curr;
			temp_node.rotten_minute = curr_node.rotten_minute + 1;	// *Increase the rot minute for the neighbor. It will be rotten in the next minute in which the current node rotted.	
		
			bfs_que.push(temp_node);	// Push the neighbor with its parameters set.
		}
		
		// Down neighbor. Check if down neighbor is: within bounds, not already visited, and if it is fresh.
		if ( (y_curr-1 >= 0) && (visited[x_curr][y_curr-1] != 1) && (grid[x_curr][y_curr-1] == 1) )
		{
			struct rotten_cell temp_node;
			temp_node.x = x_curr;
			temp_node.y = y_curr-1;
			temp_node.rotten_minute = curr_node.rotten_minute + 1;	// *Increase the rot minute for the neighbor. It will be rotten in the next minute in which the current node rotted.	
		
			bfs_que.push(temp_node);	// Push the neighbor with its parameters set.
		}
		
		// Up neighbor. Check if up neighbor is: within bounds, not already visited, and if it is fresh.
		if ( (y_curr+1 <= m-1) && (visited[x_curr][y_curr+1] != 1) && (grid[x_curr][y_curr+1] == 1) )
		{
			struct rotten_cell temp_node;
			temp_node.x = x_curr;
			temp_node.y = y_curr+1;
			temp_node.rotten_minute = curr_node.rotten_minute + 1;	// *Increase the rot minute for the neighbor. It will be rotten in the next minute in which the current node rotted.	
		
			bfs_que.push(temp_node);	// Push the neighbor with its parameters set.
		}	
	}
	
	// Check if there are any fresh oranges left that were not rotten till the end
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			if (grid[i][j] == 1)
			{
				return -1;
			}
		}
	}
	
	return max_rot_min;
}

// To clear: 
// Does the order of expanding from rotten cells of same distance matter? Why not?
// What happens if 2 rot cells conflict in spreading rot to the same cell ? Does who spread it matter?



int main()
{
	return 1;
}