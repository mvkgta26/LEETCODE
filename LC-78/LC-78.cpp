#include <vector>

using namespace std;


void backtracker(vector<int>& nums, vector<vector<int>>& output_subsets, vector<int>& curr_branch, int n, int start)
{
	output_subsets.push_back(curr_branch);
	
	// Iterate all the numbers that come after start in nums[]. Each of these will lead to different branches from the current branch
	for (int i = start; i<n; i++)
	{
		curr_branch.push_back(nums[i]);
		backtracker(nums, output_subsets, curr_branch, n, i+1);
		curr_branch.pop_back(); 	// Pop the latest branch so that curr_branch is ready for the next branch 
	}
	
	return;
}


vector<vector<int>> subsets(vector<int>& nums) 
{
	int n = nums.size();
	vector<vector<int>> output_subsets;
	vector<int> curr_branch = {};
	
	output_subsets.push_back(curr_branch);	// Push empty array. Corner Case
	
	// Start first vertex of braanches
	for (int i=0; i<n; i++)
	{
		curr_branch.push_back(nums[i]);
		backtracker(nums, output_subsets, curr_branch, n, i+1);
		curr_branch.pop_back();		// Pop the latest branch so that curr_branch is ready for the next branch 
	}
	
	return output_subsets;
}