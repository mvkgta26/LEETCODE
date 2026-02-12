// Find the smallest possible eating speed value 'k', such that all the piles are finished within h 'hours'
	
/* 
	Binary search logic: 
	We iteratively choose the middle element, and eliminate the either the left window / the right window of speed values. 
	We keep iteratively eliminating left / right windows until we reach a singular value that is the smallest speed at which Koko can finish all the piles within 'h' hours
	
	Speed Array: [s_l, s_l + 1, ......, s_m, ......, s_r - 1, s_r]
	
	1. If with eating speed of s_m, the piles get finished in time LESS THAN h hours:
		That means there is a chance that we can reduce the eating speed, and see if Koko can still finish within 'h' hours.
			(Note: We need minimum possible value of eating speed, so we have to keep reducing eating speed till we find the least possible speed)
	
		Also, that means all the speed values > than s_m : [s_m + 1, ....., s_r] CANNOT be answer, because just with the speed of s_m, Koko can finish eating within 'h' hours
	
		
	2. If with eating speed of s_m, the piles get finished in time GREATER THAN h hours:
		That means the eating speed is not enough to complete all the piles within 'h' hours
		Also, that means all the speed values < s_m : [s_l, s_l + 1, ......, s_m-1] cannot be answers, because with these lower speeds, Koko surely cannot finish all the piles within 'h' hours
*/

#include <vector>
#include <algorithm>
#include <math.h>


using namespace std; 

// Use double for number of hours. There is overflow possibility
double calc_num_hours_to_finish_piles(vector<int> &piles, int &speed)
{
	double hours = 0;
	
	for (int i=0; i < piles.size(); i++)
	{
		hours = hours +  (piles[i] + speed - 1) / speed;		// Ceiling on piles[i] / speed.   	
	}
	
	return hours;
}

int minEatingSpeed(vector<int>& piles, int h) 
{
	int m = *max_element(piles.begin(), piles.end());	// Size of the biggest pile
	
	
	// vector<int> speed_arr;
	
	// Create an array consisting of possible speed values [1, 2, 3, ......., m]
	// Any speed value > m will surely not be answer. Because the biggest pile is m
	// for ( int i = 1; i <= m; i++ )
	// {
	// 	speed_arr.push_back(i);	
	// }
	
	
	int left = 0; 
	int right = m-1;
	int lowest_speed = 2;
	
	while ( left <= right )
	{
		int c = (left + right) / 2;
		
		int curr_speed = c + 1;    // speed_arr[c];
		
		double num_hours = calc_num_hours_to_finish_piles(piles, curr_speed);	// Use double for number of hours. There is overflow possibility
		
		// If with the curr_speed, the piles are finished in exactly 'h' hours, that means that is the answer for sure (Least possible speed for which all the piles are finished)
		// if ( num_hours == h )
		// {
		// 	return curr_speed;
		// }
		
		// The eating speed could be slower. Eliminate the right window: all the speeds higher than curr_speed
		if ( num_hours <= h )
		{
			right = c - 1;
			lowest_speed = curr_speed;	// Best possible answer for now
		}
		
		// The eating speed has to be faster. Eliminate the left window: all the speeds lower than curr_speed
		else if ( num_hours > h )
		{
			left = c + 1;
		}
		
	}
	
	return lowest_speed;
}

