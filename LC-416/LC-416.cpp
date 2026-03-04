/*
	Similar to LC-322 coin change problem. 0/1 knapsack problem like.
	
	Idea:
		Let total_sum be the sum_total of the entire array nums[]
		The 2 equal total_sum partitions should obviously have total_sum == half_sum == sum_total/2 
		We have to find if we can find a subarry that has the total_sum == half_sum. If a subarray has half_sum, the complement of this subarray will also have half_sum, obviously
	
	2-D DP-Array:
		dp[n][ sum_total + 1 ]: 
			dp[i][part_sum] == 1, if the total_sum == part_sum by choosing a subarray from the array nums[] through the indices [0, i]
	
	Base-Case: 
		dp[0][0] = 1
		For all other elements in the column 0, dp[0][i] = 0. (Cannot obtain any non-zero total_sum with 0 elements)
			
	Algorithm:
		Recurrence Relation: 
				At every index i, to obtain part_sum, you have 2 options: To choose current number nums[i] OR to NOT choose current number nums[i].
				Option-1: Don't choose nums[i]: The total_sum = part_sum is obtainable through indices [0, i] if it is already obtainable through the indices [0, i-1]. Obviously it will be obtainable through [0, i] too, because we can just not choose nums[i].
				Option-2: Choose nums[i]: The total_sum = part_sum is obtainable by indeices [0-i] if the total_sum = ( part_sum - nums[i] ) is obtainable through the indices nums[0, i-1]. Because we can add nums[i] to ( part_sum - nums[i] ) to obtain part_sum.
			
				Putting in equation:
					dp[i][part_sum] == dp[i-1][part_sum] || dp[i-1][part_sum - nums[i]]

					It is possible to make total_sum == part_sum with nums[0:i], 
						if it possible to make total_sum == part_sum with nums[0:i-1] OR
						if it possible to make total_sum == (part_sum - nums[i]) with nums[0:i-1]
*/



#include <iostream>
#include <vector> 

using namespace std;


bool canPartition(vector<int>& nums) 
{
	int n = nums.size();
	
	// Calculate total total_sum of nums[]
	int total_sum = 0;
	for (int i=0; i<n; i++)
	{
		total_sum = total_sum + nums[i];
	}
	
	// Corner Case: Premature return: If the total total_sum of nums[] is odd, then surely equal total_sum partitions is not possible 
	if ( total_sum % 2 == 1 )
	{
		return 0;
	}
	
	// The equal partitions should total_sum to this value. (Since the 2 partitions should have equal total_sum, obviously they will have to have the total_sum half_sum)
	int half_sum = total_sum/2;
	
	// dp[i][part_sum] == 1 , if it is possible to obtain total_sum == part_sum by choosing a subarray of elements from nums[] within the indices [0, i] 
	vector<vector<int>> dp( n, vector<int> (half_sum+1, 0) );
	
	
	// Trivial Base Case: Sum 0 is possible with 0 elements
	dp[0][0] = 1;
	
	// Base Cases: No total_sum if possible with the index i = 0. No actual initialization has to be done as the array is initialized with 0 

	// FILL THE DP ARRAY column by column
	// i is the upper bound nums[0 : i], within which we check if it possible to make subarray that makes sum == part_sum. (Column-by-column iteration)
	for (int i=1; i < n; i++)
	{
		// Row-by-row iteration
		for (int part_sum=0; part_sum <= half_sum; part_sum++)
		{
			// Corner Case
			if (part_sum == 0)
			{
				dp[i][part_sum] = 1;
			}
			
			// Recurrence relation: (Similar to coin change problem)
				// At every index i, to obtain part_sum, you have 2 options: To choose current number nums[i] OR not choose current number nums[i].
				// Not choose nums[i]: The total_sum = part_sum is obtainable through indices [0, i] if it is already obtainable through the indices [0, i-1]. Obviously it will be obtainable through [0, i] too, because we can just not choose nums[i].
				// Choose nums[i]:  The total_sum = part_sum is also obtainable if the total_sum = ( part_sum - nums[i] ) is obtainable through the numbers [0, i-1]. Because we can then add nums[i] to ( part_sum - nums[i] ) to obtain part_sum.
			
			if ( part_sum - nums[i] >= 0 )		// Underflow check
			{
				dp[i][part_sum] = dp[i-1][part_sum] || dp[i-1][part_sum - nums[i]];	
			}
			
			else	// If there is underflow for part_sum - nums[i] , just check if it possible to get total_sum only with index [0, i-1]
			{
				dp[i][part_sum] = dp[i-1][part_sum];
			}
			
			// Premature return, if it possible to obtain half_sum through any index till i [0, i]
			if (dp[i][half_sum] == 1)
				return 1;
		}
	}
	
	int output = dp[n-1][half_sum];		// Check if the total_sum == half_sum is possible by taking a subset of numbers from [0, n-1] (The entire array)
	return output;	
}