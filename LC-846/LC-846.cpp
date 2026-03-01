#include <iostream>
#include <map>
#include <queue>

using namespace std;



bool isNStraightHand(vector<int>& hand, int groupSize) 
{
	// Easy check to eliminate a lot of options
	if ( hand.size() % groupSize != 0 )
	{
		return false;
	}
	
	// Corner Case
	if ( groupSize == 1 )
		return 1;
	
	// Hash all the elements of hand, and track the max element
	map<int, int> hash;
	int max_element = -1;
	
	for (int i=0; i < hand.size(); i++)
	{
		hash[ hand[i] ]++;
		
		if ( hand [i] > max_element )
		{
			max_element = hand[i];	
		}
	}
	
	
	// The front of the queue will contain the count of new groups that was opened groupSize numbers before
	// These number of elements will have to be closed at the number that comes after groupSize 
	queue<int> groups_to_close;
	
	// At any number i, the num_of_open_groups will represent the number of groups that require the number i+1
	int num_of_open_groups = 0;
	int num_of_groups_closed_by_num = 0;
	int prev_num = -1;
	
	// Iterate all the numbers with non zero frequency from the hash map
	int index = 0;	// Number of elements, with non zero freq, we have iterated so far in the map
	for ( auto it = hash.begin(); it != hash.end(); it++ )
	{	
		int num = it->first; 
		int num_freq = it->second;
		
		// There are some open groups which expect the number prev_num + 1, but it is not there
		// There is a gap, which means some group is not formed properly with sequential elements
		if ( num_of_open_groups != 0 && num != prev_num + 1 )
			return false; 
		
		// Cannot close all the open groups. The number i was expected to add to all the groups_to_close
		// If it is not there, that means we cannot complete some groups. Hence, return false
		if ( num_of_open_groups > num_freq )
		{
			return false;
		}
	
		// From the que front, take the number of groups that are closed by the current number num, by the number ( num - group_size + 1 )
		if ( index >= groupSize - 1 )
		{
			num_of_groups_closed_by_num = groups_to_close.front();	
			groups_to_close.pop();	
		}
		
		
		// New group start points: The excess value, hash[i] - num_of_opengroups , these numbers dont contribute to any prexisiting groups. So they have to be start of new groups
		int num_of_new_groups_start_at_i = num_freq - num_of_open_groups;
		
		// Update the num_of_open_groups : Subtract the num_of_groups_closed_by_num, because these groups are closed by i, dont have to count them anymore
		// Add num_of_new_groups_start_at_i to the exisiting number of open groups
		num_of_open_groups = num_of_open_groups + num_of_new_groups_start_at_i - num_of_groups_closed_by_num;
		
		// Push to the groups_to_close que the num_of_new_groups_start_at_i. After groupSize number of iterations, this will be taken from the que front to denote how many groups to close at that point
		groups_to_close.push(num_of_new_groups_start_at_i);
		
		
		// Updatep prev_num and index for the next iteration.
		prev_num = num;
		index++;
	}
	
	
	// No groups left open after all the iteation
	if (num_of_open_groups == 0)
	{
		return 1;
	}
	
	return 0;
	
}