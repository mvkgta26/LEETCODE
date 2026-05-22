#include <stack>
#include<iostream>
#include <algorithm>
#include <climits>

using namespace std;



/*
	Use 2 pointers: left and right.
	Start with the largest width container.
	Shrink container width by one unit at each step. Shrink from the side with the shorter line. 
	Keep shrinking till the end and find the maximum area among all the containers.
	
	Proof:
		Intuition: Iterate all the lines and find the max area container with each line. Find the max among all the max-areas obtained for each line
	
		Initially we start with max-width container. (Width = wmax)
			2 lines h0, and hn. Let min(h0, hn) be hmin
			Area = hmin * width
		
			Next, we shrink width by one unit. We can shrink from left or right. 
			Any area after shrinking will have width < wmax
			Any container with the hmin line, after shrinking, will surely have lower area than the previous area. 
				( The min height in any shrunken containers will have an upper bound of hmin from the previous step . And the width will be lower )
			So any shrunken container with the shorter line is immediately disqualified for having max area. The current container will be the container with max area with shorter line.
			The taller line among the 2 could still have higher max area after shrinking container because the new container could have higher min height to compensate for the lower width.

*/

int maxArea(vector<int>& height) 
{
	int n = height.size();
	
	// 2 pointers
	int left = 0;
	int right = n-1;
	
	int max_area = INT32_MIN;
	
	while (left < right)
	{
		int curr_area = min(height[right], height[left]) * (right - left); 
		
		if ( curr_area > max_area )
		{
			max_area = curr_area;
		}
		
		
		if ( height[left] <= height[right] )
		{
			left++;
		}
		
		else
		{
			right--;
		}
	}
	
	return max_area;
}


// Left and right pointer
// Move away from pointer with smaller height
// Why?
// Any inner container: 
		// The height of container made with taller line will surely be greater than or equal to the height of container with smaller line
		