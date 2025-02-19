#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) 
{
    int new_left = newInterval[0];
    int new_right = newInterval[1];

    int n = intervals.size();

    //int mid  = n/2;

    int closest_left_interval = 0;
    int left = 0;
    int right = n-1;
    int mid = 0;
    while (left <= right)
    {
        mid = (left + right)/2; 
        if ( new_left < intervals[mid][1] )
        {
            right = mid - 1;
        }

        else if ( new_left > intervals[mid][1] )
        {
            left = mid + 1;
        }

        else if ( new_left == intervals[mid][1] )
        {
            // Since the right end of the interval at mid has the same value of new_left, 
            // the interval at mid-1 index will surely have the largest right that is smaller than new_left
            closest_left_interval = mid - 1;
            break;
        }

    }

    // The mid interval at this point will have the closest right end value to new_left
    if (intervals[mid][1] > new_left)
    {
        closest_left_interval = mid - 1;
    }

    else if (intervals[mid][1] < new_left)
    {
        closest_left_interval = mid;
    }

    //----------------------------------------------------------------------------------------------------------------------------------

    int closest_right_interval = 0;
    left = 0;
    right = n-1;
    mid = 0;
    while (left <= right)
    {
        mid = (left + right)/2; 
        if ( new_right < intervals[mid][0] )
        {
            right = mid - 1;
        }

        else if ( new_right > intervals[mid][0] )
        {
            left = mid + 1;
        }

        else if ( new_right == intervals[mid][0] )
        {
            // Since the right end of the interval at mid has the same value of new_left, 
            // the interval at mid-1 index will surely have the largest right that is smaller than new_left
            closest_right_interval = mid + 1;
            break;
        }

    }

    // The mid interval at this point will have the closest right end value to new_left
    if (intervals[mid][0] < new_right)
    {
        closest_right_interval = mid + 1;
    }

    else if (intervals[mid][0] > new_right)
    {
        closest_right_interval = mid;
    }

    //----------------------------------------------------------------------------------------------------------------------------------


    //cout << "Closest Left Interval: " << intervals[closest_left_interval][0] << " , " << intervals[closest_left_interval][1] << "\n";
    //cout << "Closest Right Interval: " << intervals[closest_right_interval][0] << " , " << intervals[closest_right_interval][1] << "\n"; 


    //------------------------------------------------------------------------------------------

    // Create Merged Interval: Take care of corner case, the closest_left_interval and closest_right_interval might be at edge of intervals[]
    int merged_interval_left = min ( (closest_left_interval + 1 < n) ? intervals[closest_left_interval + 1][0] : new_left, new_left);  //The leftmost overlapping interval
    int merged_interval_right = max( (closest_right_interval - 1 >= 0) ? intervals[closest_right_interval - 1][1] : new_right, new_right); //The rightmost overlapping interval

    vector<int> merged_interval = {merged_interval_left, merged_interval_right};

    cout << "Merged Interval: " << merged_interval_left << " " << merged_interval_right << "\n";


    // Prepare the final intervals array

    // Delete all the overlapping intervals
    intervals.erase(intervals.begin() + closest_left_interval + 1, intervals.begin() + closest_right_interval);  // Right index is excluded in erase()

    // Inser the merged interval at the appropriate location
    intervals.insert(intervals.begin() + closest_left_interval + 1, merged_interval);

    return intervals;
}

int main()
{
    vector<vector<int>> intervals = {{1,2},{3,5},{6,7},{8,10},{12,16}}; 
    vector<int> newInterval = {1, 2};
    vector<vector<int>> ans = insert(intervals, newInterval);

    cout << "Final Array: \n";
    for ( int i = 0; i < ans.size(); i++ )
    {
        cout << ans[i][0] << " " << ans[i][1] << "\n";
    }

    return 0;
}