/*
	Refer OneNote for full detailed notes
	
	Algorithm:
		Greedy algorithm: Finding the optimal intervals set: 
			EFF (Earliest Finish First)

		Optimal[]: Array with the optimal output intervals (Maximum number of non conflicting intervals)
			>> Among all the intervals, choose the interval with the next lowest finish time, 
				and whose start time does not conflict with the start time of the current last interval in the optimal[] array. 
				Add this interval to the optimal[] array.
			>> If the interval with the next lowest finish time, conflicts with the current last interval in the optimal[] array, then SKIP THAT INTERVAL. 
				It is not part of the Optimal[] array.
*/


#include <vector>

using namespace std;

bool cmp(vector<int>& a, vector<int>& b)
{
	return a[1] < b[1];
}


// EFF: Earliest Finish First algorithm
int eraseOverlapIntervals(vector<vector<int>>& intervals) 
{
	if (intervals.size() == 1)
	{
		return 0;
	}

	// Sort the intervals[][2] vector based on the element 2 in each of the inner vectors
	sort(intervals.begin(), intervals.end(), cmp);
	
	int count = 0;
	int last_added_interval_index = 0;
	int i = 1;
	while( i < intervals.size() )
	{
		int current_interval_start_time = intervals[i][0];
		int prev_interval_end_time = intervals[last_added_interval_index][1];
		
		// Current interval overlaps with the previously added one: Remove this interval from the interval schedule
		if (current_interval_start_time < prev_interval_end_time)
		{
			count++;	// Count this interval to be removed
		}
		
		// Current interval does not overlap with the previously added one: Add this to the final interval schedule
		else
		{
			last_added_interval_index = i;	
		}
			
		i++;
	}
	
	return count;
}



