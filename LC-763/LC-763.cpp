#include <vector>
#include <map>

using namespace std;



/*

Valid Partition: A partition, such that none of the characters in the partition occur outside the partition

Claim-1: If there is a character 'c' in a valid partition, 
		Let last_c_index be the index of the last occurrence of 'c' within string s 
		The end index of the partition surely cannot be before last_c_index
		Proof: Simple

Greedy
Claim-2: For the solution partition-set to have the maximum possible number of non-overlapping partitions, 
			We have to create smallest possible valid partition, one by one, starting from the left end of s, until the entire string s is covered. (greedily)
			Proof:
				Let P1 be the smallest possible VALID partition starting from index-0
				Say P1L is a bigger valid partition created by adding more characters to the right of this parition p1.
				Extending partitions like this (from P1 to P1L) will not result in the maximum possible partitions from the string s.
				Why? By contradiction. You can just split the extended valid partition into 2 valid partitions. (VISUALIZE: SPLITTING THE SINGLE PARTITION INTO TWO PARTITIONS) (We know P1 is a valid partition in itself, which means there wont be any characters from P1 repeated in P1L) 
				This clearly means that any solution partitions set that start with P1L from index-0, will not have the maximum number of partititions.
				By induction, we can repeatedly prove like this that every subsequent valid partition that we create to the right, must be the smallest possible valid partition.			

*/


/*
Algorithm:
1. Precompute last_index[c] = last occurrence index of character c in s.
2. Scan left to right with two variables:
	  - max_window_end      : the furthest last-occurrence index among all characters seen in the current partition.
	  - prev_partition_end  : the end index of the previous partition (initialized to -1).
3. At each index i:
	  - Update max_window_end = max(max_window_end, last_index[s[i]]).
	  - If i == max_window_end, all characters in [prev_partition_end+1 .. i] are fully contained.
		→ Partition length = max_window_end - prev_partition_end. Push to output.
		→ Set prev_partition_end = max_window_end. Move to the next partition.
*/






vector<int> partitionLabels(string s) 
{
	int n = s.size();
	map<char, int> last_index; 		// Maps each character to the last index of its occurrence
	
	// Iterate the string s
	for ( int i=0; i<n; i++ )
	{
		last_index[s[i]] = i; 
	}
	
	
	vector<int> out_arr;
	
	int prev_partiton_end_index = -1;	// Adjusted to get correct partition length
	int max_window_end = -1;	// Will represent the end index after which all the characters encountered so far till iteration i, will never occur
	
	for (int i=0; i<n; i++)
	{
		char curr_char = s[i];
		
		// Update the max_window_end to represent the last occurrence among all the characters encountered so far in the partition
		if ( last_index[curr_char] > max_window_end )
		{
			max_window_end = last_index[curr_char];
		}
		
		// If we have reached the end of the current partition, push the size of the parition to the output array
		if ( i == max_window_end )
		{
			int partition_len = max_window_end - prev_partiton_end_index;
			out_arr.push_back(partition_len);
			
			prev_partiton_end_index = max_window_end;	// Update prev_partition_end_index for the next partition
		}
	}
	
	
	return out_arr;
}