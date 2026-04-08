/*
	Algorithm:
		2 pointers
		
		Idea: Make triplets of numbers that add to 0, such that the indices of the numbers in the triplet are strictly in increasing order. (We need only unique triplets. So sorted index triplet is one occurence of a group of duplicates)
		
		
		Algorithm: 
			Sort nums[]
			Iterate first_index
				Use 2 pointers after the first_index in nums[], such that the sum of the numbers of the 2 pointers in nums[] sums up to to -nums[first_index] 
				2 pointers: Shrinking window. Move left pointer to right if you need bigger sum, move right pointer to left if you need lower sum. If the sum is equal to nums[first_index], add the triplet to the output array
			
			Skip duplicate elements for first_index, second_index and third_index as well. Take care of edge cases.
*/

#include <vector>
#include <algorithm>

using namespace std;


/*
class Solution
{
	
public:
	vector<int> nums;
	
	int n = nums.size();

	vector<vector<int>> sumTriplets;
	
	vector<vector<int>> findSumIndexPairs( vector<int>& nums_sorted, int& n, const int& sum, vector<vector<int>>& sumTriplets, int first_index )
	{
		// 2 Pointer method to find all pairs of numbers that add up to sum
		
		int left_ptr = first_index + 1;	// Initially index of the smallest number in nums[]
		int right_ptr = n-1;	// Iitially index of the largest number in nums[]
		int curr_sum = nums[left_ptr] + nums[right_ptr];	

		
		while ( left_ptr < right_ptr )
		{
			// The pair curr_sum == sum
			if (curr_sum == sum)
			{
				vector<int> temp_triplet = {nums[first_index], nums[left_ptr], nums[right_ptr]};
				sumTriplets.push_back(temp_triplet);
				
				// Update left ptr, to find other pairs that could add to sum
				while ( nums[left_ptr] == nums[left_ptr+1] )
				{
					left_ptr++;
				}
				left_ptr++;
			}
						
			// The pair needs to have a bigger sum
			else if (curr_sum < sum)
			{
				// Update left_ptr to the next index in the right DOES NOT HAVE THE SAME NUMBER
				while ( nums[left_ptr] == nums[left_ptr+1] )
				{
					left_ptr++;
				}
				left_ptr++;
			}
			
			// The pair needs to have a smaller sum
			else if ( curr_sum > sum )
			{
				// Update righ_ptr to the next index in the left DOES NOT HAVE THE SAME NUMBER (TO AVOID DUPLICATE TRIPLETS)
				while ( nums[right_ptr] == nums[right_ptr - 1] )
				{
					right_ptr--;
				}
				right_ptr--;
			}
		}
		
		return sumTriplets;
	}
	
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		sort(nums.begin(), nums.end());
		
		// We only fill sorted indices triplet, in the sumTriplets array
		
		// Iterate first index.
		// Try to find sorted index pair that sum to the complement of nums[first_index]
		for (int i=0; i<n; i++)
		{
			int first_num = nums[i];	
			int complement_num = -1 * first_num;	// complement_num + first_num = 0
			
			findSumIndexPairs(nums, n, complement_num, sumTriplets, i);
		}
		
		return sumTriplets;
	}

};
*/



// Finds all pairs of elements that add up to sum, and makes triplet with ( nums[first_index] and this pair ). Appends all such triplets to output.
int findSumTriplets( vector<int>& nums, int n, const int& sum, vector<vector<int>>& output, int first_index )
{
	// 2 Pointer method to find all pairs of numbers that add up to sum
	
	int left_ptr = first_index + 1;	// Initially index of the smallest number in nums[]
	int right_ptr = n-1;	// Iitially index of the largest number in nums[]
	int curr_sum = nums[left_ptr] + nums[right_ptr];	

	
	while ( left_ptr < right_ptr )
	{
		// Calculate new curr_sum
		curr_sum =  nums[left_ptr] + nums[right_ptr];	

		// The pair's sum curr_sum == sum
		if (curr_sum == sum)
		{
			vector<int> temp_triplet = {nums[first_index], nums[left_ptr], nums[right_ptr]};
			output.push_back(temp_triplet);
			
			// Update left ptr, to find other pairs that could add to sum
			while ( ( left_ptr+1 < n ) && nums[left_ptr] == nums[left_ptr+1] )
			{
				left_ptr++;
			}
			left_ptr++;
		}
					
		// The pair's sum needs to be bigger
		else if (curr_sum < sum)
		{
			// Update left_ptr to the next index in the right DOES NOT HAVE THE SAME NUMBER
			while ( (left_ptr+1 < n) && nums[left_ptr] == nums[left_ptr+1] )
			{
				left_ptr++;
			}
			left_ptr++;
		}
		
		// The pair's sum needs to be smaller
		else if ( curr_sum > sum )
		{
			// Update righ_ptr to the next index in the left DOES NOT HAVE THE SAME NUMBER (TO AVOID DUPLICATE TRIPLETS)
			while ( (right_ptr-1 >= 0) && nums[right_ptr] == nums[right_ptr - 1] )
			{
				right_ptr--;
			}
			right_ptr--;
		}
	}
	
	return 1;	// Dummy return
}


vector<vector<int>> threeSum(vector<int> nums)
{
	sort(nums.begin(), nums.end());
	int n = nums.size();
	
	vector<vector<int>> output;
	
	
	// We only fill sorted indices triplet, in the output array
	
	// Iterate first index.
	// Try to find sorted index pair that sum to the complement of nums[first_index]
	for (int first_index=0; first_index <= n-3; first_index++)
	{
		// Duplicate skip, for first index
		if ( first_index > 0 && nums[first_index] == nums[first_index - 1] )
		{
			continue;
		}

		int first_num = nums[first_index];	
		int complement_sum = -1 * first_num;	// complement_num + first_num = 0
		
		findSumTriplets(nums, n, complement_sum, output, first_index);
	}
	
	return output;
}


void main()
{
	vector<int> nums = {-1,0,1,2,-1,-4};
	
	threeSum(nums);
	
}