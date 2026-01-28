/*
	max_rob[i] is the maximum cash that can be stolen with a rob pattern using houses {0, i}, and ending at house-i
	Recurrence Relation (For linearly arranged houses): max_rob[i] = max ( max_rob[i-2], max[i-3] ) + nums[i]
	
	max_cash_to_rob = max(max_cash_0, max_cash_1);
		The maximum possible robbed cash among the circularly located houses [0, n-1]  will be:
		The max of (max robbed cash among the houses [0, n-2] , assuming they are linearly located, AND, 
  		the max robbed cash among the houses [1, n-1] assuming they are linearly arranged )
	
	
	REFER ONE NOTE FOR PROOF
*/


#include <vector>
#include <algorithm>


using namespace std;


int rob(vector<int>& nums) 
{
	int n = nums.size();
	vector<int> max_rob_0(n-1);
	vector<int> max_rob_1(n);	// max_rob_1[0] is useless here. Just having it for index convenience.
	int max_cash_0 = -1;
	int max_cash_1 = -1;
	
	// Corner Cases
	if (n == 1)
	{
		return nums[0];
	}
	
	if (n == 2)
	{
		return max(nums[0], nums[1]);
	}
	
	if (n == 3)
	{
		return max(max(nums[0], nums[1]), nums[2]);
	}
	
	
	// Find maximum possible cash to rob from [0-n-2] houses
	// Base Cases
	max_rob_0[0] = nums[0];
	max_rob_0[1] = nums[1];
	max_rob_0[2] = nums[0] + nums[2];
	max_cash_0 = max( max(max_rob_0[0], max_rob_0[1]), max_rob_0[2]);		// Track max vaue in the max_rob_0[] array. Also track the base cases.
	
	for (int i=3; i < n-1; i++)
	{
		max_rob_0[i] = max(max_rob_0[i-2], max_rob_0[i-3]) + nums[i];		// Recurrence relation
		max_cash_0 = max(max_cash_0, max_rob_0[i]);		// Track the maximum cash stolen so far
	}
	
	
	// Find maximum possible cash to rob from [1-n-1] houses
	// Base Cases
	max_rob_1[1] = nums[1];
	max_rob_1[2] = nums[2];
	max_rob_1[3] = nums[1] + nums[3];
	max_cash_1 = max(max(max_rob_1[1], max_rob_1[2]), max_rob_1[3]);		// Track max vaue in the max_rob_1[] array. Also track the base cases.
	
	for (int i=4; i < n; i++)
	{
		max_rob_1[i] = max(max_rob_1[i-2], max_rob_1[i-3]) + nums[i];		// Recurrence relation
		max_cash_1 = max(max_cash_1, max_rob_1[i]);		// Track the maximum cash stolen so far
	}
	
	
	// Maximm cash to rob among the set [0, n-2] and the set [1, n-1] 
	int max_cash_to_rob = max(max_cash_0, max_cash_1);
	
	return max_cash_to_rob;
}
