/*
	LC-919: REFER ONENOTE FOR DETAILS
	
	Claim: The number of meeting rooms needed is the maximum number of overlaps between meetings, at any point of time. 

		Algorithm: To find the maximum number of concurrent meetings occurring at any time instant: (2 pointers Method):
			Store all the start times and all the end times of all the meetings in start[] array and end[] array separately.
			Sort the start[] array and end[] array 
			Iterate all the start and end events, together, in ascending order (using 2 pointers). Use 'count' variable to count the number of concurrent meetings occurring at any time instant.
			As you iterate the start and end events:
				If the next event is a start event, increase 'count' , because now there is one more concurrent meeting started
				If the next event is an end event, decrease 'count', because now there is one less concurrent meeting (as one meeting has ended)
			Track the maximum 'count' among all these events. This will be the maximum overlapping meeting at any time. RETURN THIS MAX COUNT.
*/

#include<vector>


using namespace std;


class Interval 
{
public:
	int start, end;
	Interval(int start, int end) 
	{
		this->start = start;
		this->end = end;
	}
};


int minMeetingRooms(vector<Interval>& intervals)
{
	int n = intervals.size();
	
	if (n == 0)
	{
		return 0;
	}
	
	
	// Store all the start times and the end times of all the intervals in the start_times[] and end_times[] arrays
	vector<int> start_times, end_times;
	
	for (int i=0; i < n; i++)
	{
		start_times.push_back(intervals[i].start);
		end_times.push_back(intervals[i].end);
	}
	
	
	sort(start_times.begin(), start_times.end());
	sort(end_times.begin(), end_times.end());
	
	
	// 2 pointer loop
	int num_of_conccurent_meetings = 0;
	int max_num_of_concurrent_meetings = 0;
	int start_pointer = 0, end_pointer = 0;
	while (start_pointer < n && end_pointer < n)
	{
		int next_start_event = start_times[start_pointer];
		int next_end_event = end_times[end_pointer];
		
		if (next_start_event < next_end_event)
		{
			num_of_conccurent_meetings++;
			start_pointer++;	
		}
		
		else
		{
			num_of_conccurent_meetings--;
			end_pointer++;
		}
		
		if (num_of_conccurent_meetings > max_num_of_concurrent_meetings)
		{
			max_num_of_concurrent_meetings = num_of_conccurent_meetings;
		}
	}
	
	// Count left over end times that were not counted, because the loop ended. THIS DOES NOT ACTUALLY SERVE ANY PURPOSE, JUST FOR LOGICAL COHERENCE
	num_of_conccurent_meetings = num_of_conccurent_meetings - (n - end_pointer);
	
	
	return max_num_of_concurrent_meetings;
}

void main()
{
	
}