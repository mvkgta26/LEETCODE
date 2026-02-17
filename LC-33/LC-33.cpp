/*

	// Check diagram in OneNote

	// Left slope: From nums[0] to the max element
	// Right slope: From min element (which is immediately after max element) to nums[n-1]
	
	
	// Handle case by case
	// Case-1: Mid is in left slope
			Case-1.1: Target is surely not to the left of mid in the left slope
			Case-1.2: Target is surely to the left of mid in the left slope
			Case-1.3: Target is surely in the right slope, not in the left slope
		
	// Case-2: Mid is in left slope
		Case-1.1: Target is surely not to the right of mid in the right slope
		Case-1.2: Target is surely to the right of mid in the right slope
		Case-1.3: Target is surely in the left slope, not in the right slope
	
*/


#include <vector>

using namespace std;

int search(vector<int>& nums, int target) 
{		
	int n = nums.size();
	int left = 0;
	int right = n-1;
	int mid = (left + right)/2;
	

	// Corner Case: What if it is rotated n times: Is automatically handled in the cases for this problem. No need special if clause.
	
	
	while ( left <= right )
	{
		int curr_num = nums[mid];
		
		
		// Target detected at current mid
		if (curr_num == target)
		{
			return mid;
		}
		
		
		// Left slope cases: Mid is in left slope right now
		else if ( curr_num >= nums[0] )
		{
			// Target cannot surely be to the left of 'mid' in nums[]
			// Rule out every element to the left of 'mid' in nums[]
			if ( target > curr_num )
			{
				left = mid + 1;
			}
			
			// Target is surely in the left slope, to the left of 'mid'
			// Rule out every element to the right of 'mid' in nums[]
			else if ( target < curr_num && target >= nums[0] )
			{
				right = mid - 1;
			}
			
			// Target is surely in the right slope, to the right of 'mid' which is currently in the left slope
			// Eliminate all the elements that are to the left of 'mid'
			else if ( target < curr_num && target < nums[0] )
			{
				left = mid + 1;
			}
		}
		
		// Right slope cases: Mid is in right slope right now
		else if ( curr_num < nums[0] )
		{
			// Target cannot surely be to the right of 'mid' in nums[]
			// Rule out every element to the right of 'mid' in nums[]
			if ( target < curr_num )
			{
				right = mid - 1;
			}
			
			// Target is surely in the right slope, to the right of 'mid'
			// Rule out every element to the left of 'mid' in nums[]
			else if ( target > curr_num && target <= nums[n-1] )
			{
				left = mid + 1;
			}
			
			// Target is surely in the left slope, to the left of 'mid' which is currently in the right slope
			// Eliminate all the elements that are to the right of 'mid'
			else if ( target > curr_num && target > nums[n-1] )
			{
				right = mid - 1;
			}
		}
		
		// Update mid
		mid = (left + right)/2;
	}
	
	
	return -1;
}