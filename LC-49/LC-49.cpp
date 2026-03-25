/*
	All anagram strings will have the same sorted order
	
	Algorithm:
		Sort each string in the array 
		Hash each sorted string ---> index in the output_arr[], which will hold the vector with all the anagrams of this string
		Push all the anagrams (strings with the same sorted order) into the output_arr[ ] at the position hash[sorted_str]
*/

#include <vector>
#include <algorithm>
#include <unordered_map>
#include<string>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) 
{
	int n = strs.size();
	
	unordered_map<string, int> hash;
	vector<vector<string>> output_arr;
	int output_arr_tail = 0;
	
	for (int i=0; i < n; i++)
	{
		string curr_str = strs[i];
		string curr_str_sorted = strs[i];
		sort(curr_str_sorted.begin(), curr_str_sorted.end());
		
		// If curr_str_sorted was never encountered before in the strs[] array, create a new vector in the output_arr, and move the index
		if ( hash.find(curr_str_sorted) == hash.end() )
		{
			hash[curr_str_sorted] = output_arr_tail;	// Hash position of the vector with curr_str_sorted in the output_arr[]
			vector<string> temp_arr = {curr_str};	
			output_arr.push_back(temp_arr);
			output_arr_tail++;
		}
		
		// If curr_str_sorted was encountered before, then push the curr_str in the respective position in the output_arr[]
		else
		{
			int index = hash[curr_str_sorted]; 
			output_arr[index].push_back(curr_str);
		}
	}
	
	return output_arr;
}

void main()
{
	
}