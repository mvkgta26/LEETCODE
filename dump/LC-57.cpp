#include <vector>
#include <algorithm>

using namespace std;


//Condition Function for sorting based on index 0 of all vectors. (Condition for v2 > v1)
bool sort_rule(const vector<int>& v1,const vector<int>& v2)
{
	//If both vectors have same 0-index, but differnt 1-index ==> Vector with higher 1-index is considered to be higher
	if(v2[0] == v1[0])
	{
		if(v2[1] > v1[1])
		{
			return 1;
		}
		
		else
		{
			return 0;
		}
	}
	
	//Otherwise, sort based on 0-index
	else if(v2[0] > v1[0])
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

vector<vector<int>> merge(vector<vector<int>>& intervals) 
{
	int n = intervals.size();
	
	// Corner case
	if (n == 0)
	{
		return {};
	}
	
	// Sort based on the start element of each interval
	sort(intervals.begin(), intervals.end(), sort_rule);
	
	int start_i = intervals[0][0];
	int max_j = intervals[0][1];
	
	vector<vector<int>> out;
	
	for (int i=0; i<n; i++)
	{
		// This interval is part of the current overlap group
		if ( intervals[i][0] <= max_j )
		{
			// Update max_j
			max_j = max(max_j, intervals[i][1]);
		}
		
		// Overlap ended with the interval at intervals[i]
		else
		{
			vector<int> interval = {start_i, max_j};
			out.push_back(interval);	// Push the previously grouped interval to the output set
			
			// Update new start_i and max_j
			start_i = intervals[i][0];
			max_j = intervals[i][1];
		}		
	}
	
	
	// The last overlap group is never added to the output. Add it now
	out.push_back( {start_i, max_j} );
	
	
	return out;
}