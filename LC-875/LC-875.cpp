#include <vector>
#include <algorithm>


using namespace std; 



int minEatingSpeed(vector<int>& piles, int h) 
{
	int m = *max_element(piles.begin(), piles.end());	// Size of the biggest pile
	
	
	vector<int> speed_arr;
	
	// Create an array consisting of possible speed values [1, 2, 3, ......., m]
	// Any speed value > m will surely not be answer. Because the biggest pile is m
	for (int i = 1; i <= m; i++ )
	{
		speed_arr.push_back(i);	
	}
	
	
	
	// Find the smallest possible eating speed value 'k', such that all the piles are finished within h 'hours'
	
	/* 
		Binary search logic: 
		We iteratively choose the middle element, and eliminate the left / window of speed values. 
		We keep doing this until we 
		
		Speed Array: [s_l, s_l + 1, ......, s_m, ......, s_r - 1, s_r]
		
		If with eating speed of s_m, the piles get finished in time LESS THAN h hours:
			That means there is a chance that we can reduce the eating speed, and see if Koko can still finish within 'h' hours.
				(Note: We need minimum possible value of eating speed, so we have to keep reducing eating speed till we find the least possible speed)
		
			Also, that means all the speed values > than s_m : [s_m + 1, ....., s_r] CANNOT be answer, because just with the speed of s_m, Koko can finish eating within 'h' hours
		
			
		If with eating speed of s_m, the piles get finished in time GREATER THAN h hours:
			That means the eating speed is not enough to complete all the piles within 'h' hours
			Also, that means all the speed values < s_m : [s_l, s_l + 1, ......, s_m-1] cannot be answers, because with these lower speeds, Koko surely cannot finish all the piles within 'h' hours
			
			
		
	*/
	
	
	
}

