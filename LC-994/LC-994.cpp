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
	
	queue<rotten_cell> rotten_que;
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			// If orange in this cell is rotten, 
			if (grid[i][j] == 2)
			{
				struct rotten_cell temp_cell;
				temp_cell.x=i;
				temp_cell.y=j;
				//temp_cell.rotten_minute 
			}
		}
	}	
}


int main()
{
	return 1;
}