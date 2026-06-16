#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
#include <cctype>
#include <algorithm>
#include <stack>



using namespace std;


class Solution 
{
	public:
		vector<int> dailyTemperatures(vector<int>& temperatures) 
		{
			int n = temperatures.size();
			vector<int> output(n, 0);
			stack<int> decreasing_stk;	// Stack with indices of temperatures, ordered higer to lower from bottom to top
			
			for (int i=0; i<n; i++)
			{
				int curr_temp = temperatures[i];
				while ( !decreasing_stk.empty() && temperatures[decreasing_stk.top()] < curr_temp )
				{
					int lower_temp_i = decreasing_stk.top();
					int curr_temp_i = i;
					
					output[lower_temp_i] = curr_temp_i - lower_temp_i;
					
					decreasing_stk.pop();
				}
				
				// Push index of current temperature
				decreasing_stk.push(i);
			}
			
			
			// Left over indices in the stack
			while (!decreasing_stk.empty())
			{
				output[decreasing_stk.top()] = 0;
				decreasing_stk.pop();
			}
			
			return output;
		}
	};