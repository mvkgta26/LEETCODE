#include <vector>
#include <algorithm>

using namespace std;


bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) 
{
	int target_a = target[0];
	int target_b = target[1];
	int target_c = target[2];
	
	int a_flag = 0;
	int b_flag = 0;
	int c_flag = 0;
	
	vector<vector<int>> output_operand_triplets;
	
	// Iterate all the triplets
	for (int i=0; i < triplets.size(); i++)
	{
		int a = triplets[i][0];
		int b = triplets[i][1];
		int c = triplets[i][2];
		
		// Eliminate TOXIC triplets: If any one of the elements in the triplets is greater than the corresponding element in the target triplet, eliminate that option. If these toxic triplets are in the solution operands, surely, because of the property of max(), the output will not be target
		// Check among the non-toxic triplets, if at least one of the triplets have target_a, target_b and target_c in them. Set flags for each a, b and c
		if ( !( a > target_a || b > target_b || c > target_c ) )
		{
			if (a == target_a)
			{
				a_flag = 1;		// Mark that target_a is present in one of the valid triplets
			}
			
			if ( b == target_b )
			{
				b_flag = 1;		// Mark that target_b is present in one of the valid triplets
			}
			
			if ( c == target_c )
			{
				c_flag = 1;		// Mark that target_c is present in one of the valid triplets
			}
		}
	}
	
	// If a, b and c occurs at least in one triplet among the non-toxic triplets (not necessarily toegthor), that means we can arrive at target by applying max operations on some triplets among the non-toxic triplets
	if ( a_flag && b_flag && c_flag )
	{
		return 1;
	}
	
	return 0;
}