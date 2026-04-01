/*
	Idea:
		2D Arrays row-hash[9][9], col_hash[9][9], and box_hash[9][9]
		row_hash[i][num] == 1, if there is num in row-i
		Similarly for col_hash[9][9] and box_hash[9][9]
		
		Box_index calculation = (i/3)*3 + j/3
*/


#include <vector>
#include <unordered_map>

using namespace std;


bool isValidSudoku(vector<vector<char>>& board) 
{
	// 2D vector (9x9). row_hash[i][num] = 1, if num exists in row-i 
	vector<vector<int>> row_hash(9, vector<int>(9, 0));
	
	// 2D vector (9x9). col_hash[i][num] = 1, if num exists in col-i 
	vector<vector<int>> col_hash(9, vector<int>(9, 0));
	
	// 2D vector (9x9). box_hash[i][num] = 1, if num exists in box-i
	vector<vector<int>> box_hash(9, vector<int>(9, 0));
	
	// Iterate the board 
	for (int i=0; i<9; i++)
	{
		for (int j=0; j<9; j++)
		{
			// Check if board cell is empty
			if ( board[i][j] == '.' )
				continue;
			
			int num = board[i][j] - '1';	// Convert num from char to int, and make it 0 indexed
			
			// i/3 => Box row
			// j/3 => Box column
			// 3 boxes in each row
			int box_index = 3 * (i/3) + j/3 ;		// Formula to calculate the box-index using row-number-i and column-number-j
			
			// A number encountered twice in row-i
			if ( row_hash[i][num] == 1 )
				return 0;
				
			// A number encountered twice in col-j
			if ( col_hash[j][num] == 1 )
				return 0;
				
			
			// A number encountered twice in box-box_index
			if ( box_hash[box_index][num] == 1 )
				return 0;
			
			
			// Mark the num as visited in its respective row, col and hash
			row_hash[i][num] = 1;
			col_hash[j][num] = 1;
			box_hash[box_index][num] = 1;
		}
	}
	
	return 1;
}

void main()
{
	
}