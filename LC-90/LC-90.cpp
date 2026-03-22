/*
	Sort the nums array
	Iterate every index, and make a decision whether to choose or not choose to add that number to the subset 

	Handling Duplicates:
	Main Claim:
		If you chose to not include a number nums[i] in the subset during a decision, skip all decisions on any further occurence of the same number nums[i] in future indices
		(Why? Not done proof, you can try a dry run)
*/


#include <vector>
#include<algorithm>

using namespace std;

// void backtrack(vector<int>& nums, vector<vector<int>>& outputs, int start, vector<int>& curr_subset, int n)
// {
// 	outputs.push_back(curr_subset);
	
// 	// Add nums[i] to the curr_subset
// 	for (int i = start; i < n; i++)
// 	{
// 		// Skip all futher occurces of the number nums[start].		
// 		if ( i > start && nums[i] == nums[i-1] )		continue;
		
// 		// Choose nums[i]
// 		curr_subset.push_back(nums[i]);
// 		backtrack(nums, outputs, i+1, curr_subset, n);
		
// 		// Dont choose nums[i]
// 		curr_subset.pop_back();
// 	}
// }

void backtrack(vector<int>& nums, vector<vector<int>>& outputs, int start, vector<int> curr_subset, int n)
{
	outputs.push_back(curr_subset);
	
	for (int i = start; i < n; i++)
	{
		// if i > start, that means we have decided to skip adding all the number from nums[start] till nums[i], into the curr_subset[]
		// Skip adding all the numbers that have the same value as nums[start]
		if (i > start && nums[i] == nums[i-1])  continue;
		
		
		// Make a separate backtrack call with nums[i] in curr_subset[]
		vector<int> next_subset = curr_subset;   // fresh copy for this branch
		next_subset.push_back(nums[i]);
		backtrack(nums, outputs, i+1, next_subset, n);
	}
}


vector<vector<int>> subsetsWithDup(vector<int>& nums) 
{
	int n = nums.size();
	sort(nums.begin(), nums.end());
	
	vector<vector<int>> outputs;
	vector<int> curr_sub = {};
	
	backtrack(nums, outputs, 0, curr_sub, n);
	
	return outputs;
}