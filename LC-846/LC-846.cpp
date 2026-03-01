/*
	Data Structures and Variables :
		num_of_open_groups: After processing any number i, the num_of_open_groups will represent the number of groups that require the number i+1
			
		Let k = groupSize.
		Queue<int> groups_to_close stores counts of groups started at the previous k numbers.
		At current number x, queue front = number of groups that started at x - k + 1, so they close at x.
			The number behind this queue front, will hold the number of groups that started at (x - k + 2), so they close at x+1

	num_of_groups_closed_by_num: The number of groups closed by the number 'num' in the current iteration
	num_of_new_groups_start_at_num: Number of new groups that start at num
	
	
	Algorithm:
		Hash all the numbers in the hand[] array
		
		Iterate all the numbers in the hash with non-zero frequencies (Iterator variable num)
			
			CHECK: For any num in the loop, check if num is continuous to the prev_num if there are open groups (num_of_open_groups != 0).
				If the number is not continous to the prev_num while there are still open groups, return False
			
			CHECK: Check if frequency of current num >= num_of_open_groups
				Otherwise return false, not all open groups can be fully formed, some groups will miss the num element. 	

			num_of_groups_closed_by_num = groups_to_close.pop_front(); 		
			num_of_new_groups_start_at_num = num_freq - num_of_open_groups;	(The excess occurrences of num will start new groups, the others will continue or close the old groups)
			num_of_open_groups = num_of_open_groups + num_of_new_groups_start_at_num - num_of_groups_closed_by_num;	
			groups_to_close.push(num_of_new_groups_start_at_num);
*/

#include <iostream>
#include <map>
#include <queue>

using namespace std;



bool isNStraightHand(vector<int>& hand, int groupSize) 
{
	// Easy check to eliminate a lot of invalid hand[] arrays
	if ( hand.size() % groupSize != 0 )
	{
		return false;
	}
	
	// Corner Case
	if ( groupSize == 1 )
	{
		return 1;	
	}
	
	// Hash all the elements of hand, and track the max element
	map<int, int> hash;
	for (int i=0; i < hand.size(); i++)
	{
		hash[ hand[i] ]++;
	}
	
	
	// Queue front = count of groups that started at (current_num - groupSize + 1), which close at current_num (After group_size window)
	queue<int> groups_to_close;
	
	// At any number i, the num_of_open_groups will represent the number of groups that require the number i+1
	int num_of_open_groups = 0;
	int num_of_groups_closed_by_num = 0;
	int prev_num = -1;
	
	// Iterate all the numbers with non zero frequency from the hash map
	for ( auto it = hash.begin(); it != hash.end(); it++ )
	{	
		int num = it->first; 
		int num_freq = it->second;
		
		// There are some open groups which expect the number prev_num + 1, but it is not there
		// There is a gap, which means some group is not formed properly with sequential elements
		if ( num_of_open_groups != 0 && num != prev_num + 1 )
		{
			return false;	
		}
		
		// Cannot close all the open groups. The number i was expected to add to all the groups_to_close
		// If it is not there, that means we cannot complete some groups. Hence, return false
		if ( num_of_open_groups > num_freq )
		{
			return false;
		}
	
		// From the que front, take the number of groups that are closed by the current number num, by the number ( num - group_size + 1 )
		if ( groups_to_close.size() >= groupSize - 1 )	// Ensure group_size number of elements are inserted into the queue first
		{
			num_of_groups_closed_by_num = groups_to_close.front();	
			groups_to_close.pop();	
		}
		
		// New group start points: The excess value, hash[i] - num_of_opengroups , these numbers dont contribute to any prexisiting groups. So they have to be start of new groups
		int num_of_new_groups_start_at_num = num_freq - num_of_open_groups;
		
		// Update the num_of_open_groups : Subtract the num_of_groups_closed_by_num, because these groups are closed by i, dont have to count them anymore. Add num_of_new_groups_start_at_num to the exisiting number of open groups
		num_of_open_groups = num_of_open_groups + num_of_new_groups_start_at_num - num_of_groups_closed_by_num;
		
		// Push to the groups_to_close que the num_of_new_groups_start_at_num. After groupSize number of iterations, this will be taken from the que front to denote how many groups to close at that point
		groups_to_close.push(num_of_new_groups_start_at_num);
		
		// Updatep prev_num 
		prev_num = num;
	}
	
	
	// No groups left open after all the iteation
	if (num_of_open_groups == 0)
	{
		return 1;
	}
	
	return 0;
}