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
	
	// While inflection point condition is not satisfied
	//while ( ! ( ( (mid != 0) && nums[mid-1] > nums[mid]) && ( mid+1 > n-1 ) ) && ! ( ( ( (mid != 0) && nums[mid-1] > nums[mid] ) && ( nums[mid+1] > nums[mid] ) ) ) )	// The first condition before the OR is corner case. When the minimum element is the last element in nums[]. Also take care of left side overflow.
	while ( ! ( ( ( !( mid-1 < 0) && nums[mid-1] > nums[mid] ) && ( ( mid + 1 > n-1 ) || ( nums[mid+1] > nums[mid] ) ) ) ) )	// Corner Cases: When the minimum element is the last element in nums[] (Right overflow) . Also left overflow.  
	{
		// The min element will be somwhere to the right of mid
		if ( nums[mid] >= nums[0] )
		{
			left = mid + 1;
		}
		
		// The min element will be somwhere to the right of mid
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