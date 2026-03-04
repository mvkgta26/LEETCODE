


#include <iostream>
#include <vector> 

using namespace std;


bool canPartition(vector<int>& nums) 
{
	int n = nums.size();
	
	int sum = 0;
	for (int i=0; i<n; i++)
	{
		sum = sum + nums[i];
	}
	
	// Corner Case: Premature return: If the total sum of nums[] is odd, then surely equal sum partitions is not possible 
	if ( sum % 2 == 1 )
	{
		return 0;
	}
	
	// The equal partitions should sum to this value. (Since the 2 partitions should have equal sum, obviously they will have to have the sum half_sum)
	int half_sum = sum/2;
	
	// dp[i][sum_j] == 1 , if it is possible to obtain sum == sum_j by choosing a subarray of elements from nums[] within the indices [0, i] 
	vector<vector<int>> dp( n, vector<int> (half_sum+1, 0) );
	
	
	// Trivial Base Case: Sum 0 is possible with 0 elements
	dp[0][0] = 1;
	
	// // Base Cases: No sum if possible with the index i = 0. This does not have to be done as the array is initialized with 0 
		// for ( int sum_j=1; sum_j <= half_sum; sum_j++ )
		// {
		// 	dp[0][sum_j] = 0;
		// }
	
	
	// i is the index (inclusive) still which we check if 
	for (int i=1; i < n; i++)
	{
		for (int sum_j=0; sum_j <= half_sum; sum_j++)
		{
			// Corner Case
			if (sum_j == 0)
			{
				dp[i][sum_j] = 1;
			}
			
			// Recurrence relation: (Similar to coin change problem)
				// At every index i, to obtain sum_j, you have 2 options: To choose current number nums[i] OR not choose current number nums[i].
				// Not choose nums[i]: The sum = sum_j is obtainable through indices [0, i] if it is already obtainable through the indices [0, i-1]. Obviously it will be obtainable through [0, i] too, because we can just not choose nums[i].
				// Choose nums[i]:  The sum = sum_j is also obtainable if the sum = ( sum_j - nums[i] ) is obtainable through the numbers [0, i-1]. Because we can then add nums[i] to ( sum_j - nums[i] ) to obtain sum_j.
			
			if ( sum_j - nums[i] >= 0 )		// Underflow check
			{
				dp[i][sum_j] = dp[i-1][sum_j] || dp[i-1][sum_j - nums[i]];	
			}
			
			else	// If there is underflow for sum_j - nums[i] , just check if it possible to get sum only with index [0, i-1]
			{
				dp[i][sum_j] = dp[i-1][sum_j];
			}
			
			// Premature return, if it possible to obtain half_sum through any index till i [0, i]
			if (dp[i][half_sum] == 1)
				return 1;
		}
	}
	
	
	int output = dp[n-1][half_sum];		// Check if the sum == half_sum is possible by taking a subset of numbers from [0, n-1] (The entire array)
	return output;	
}