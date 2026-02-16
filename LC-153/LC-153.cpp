/*
	Claims:
		1. Inflection Point:  nums[min_index-1] < nums[min_index] < nums[min_index+1] .
								min_index is the index of the minimum number in nums[]
								nums[min_index] is the minimum number in nums[]
								Proof: Obvious. Just write a generalized rotated sorted array and see.
		1. If nums is rotated < n times, and If nums[index] >= nums[0] : The minimum element will be to the right of index
		2. If nums is rotated < n times, and If nums[index] < nums[0] : The minimum element will be to the left of index
								[Proof for both above: Pretty obvious. Just write a generalized rotated sorted array and see.]
		
	Corner Cases: 	
		1. The nums[] is rotated n times. nums[] will be in proper sorted order. 
				Only In that case, nums[n-1] > nums[0]
		2. Left overflow and right overflow when checking for inflection point condition
*/

#include <vector>


using namespace std;



int findMin(vector<int>& nums) 
{
	int i = 0;
	int n = nums.size();
	
	int left = 0;
	int right = n-1;
	int mid = (left + right) / 2;
	
	
	// Corner Case: If nums[] is rotated n times, so that the nums[] array is just in sorted order
	if ( n == 1 )
	{
		return nums[0];
	}
		
	// Corner Case: If nums[] is rotated n times, so that the nums[] array is just in sorted order
	if (nums[right] > nums[0])
	{
		return nums[0];
	}
	
	// Chcek if inflection point condition is satisfied
	while ( ! ( ( ( !( mid-1 < 0) && nums[mid-1] > nums[mid] ) && ( ( mid + 1 > n-1 ) || ( nums[mid+1] > nums[mid] ) ) ) ) )	// Corner Cases: When the minimum element is the last element in nums[] (Right overflow) . Also check for left overflow.  
	{
		// The min element will be somwhere to the right of mid
		if ( nums[mid] >= nums[0] )
		{
			left = mid + 1;
		}
		
		// The min element will be somwhere to the left of mid
		else if ( nums[mid] < nums[0] )
		{
			right = mid - 1; 
		}

		mid = ( left + right ) / 2;
	}
	
	
	return nums[mid];
}



void main()
{
	
}