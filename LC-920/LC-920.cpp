#include <vector>
#include <algorithm>

/*
	Algorithm:
		Sort (ascending) by start (or end) value of the intervals
		Check if any adjacent intervals conflict:
			If any conflict: Return False
			Else; Return True: This is a valid arrangement
			
	Proof: Not doing, pretty simple and obvious
*/


using namespace std;

class Interval {
	public:
		 int start, end;
		 Interval(int start, int end) {
			 this->start = start;
			 this->end = end;
		 }
};

bool cmp(Interval& Int_1, Interval& Int_2)
{
	return Int_1.start < Int_2.start;
	// return Int_1.end < Int_2.end;		// This will also work
}

bool canAttendMeetings(vector<Interval>& intervals) 
{
	// Sort (ascending order) the intervals[] array based on the start time of all the intervals
	sort(intervals.begin(), intervals.end(), cmp);
	
	
	for (int i=1; i < intervals.size(); i++)
	{
		// If there is a conflict between adjacent intervals
		if ( intervals[i-1].end > intervals[i].start )
		{
			return false;
		}
	}
	
	return true;
}