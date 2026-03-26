/*
	Hash the frequency of each number in the nums[]
	Iterate through the hash, and add each pair from the hash to a min-heap which sorts based on the second element of the pair (Sort based on The frequency)
		Keep popping the top of the min-heap so that at any time only the k most frequent elements seen so far will remain
	
	Add all the k most frequent elements from the min heap into the output array
	Return output
	
	NOTE: You can also do it with bucket sorting method. Have a 2D vector of size n+1, arr[i][] will hold the number that occur with frequency i 
*/

#include<vector>
#include <queue>
#include <unordered_map>

using namespace std;

class cmp
{
	public:
		// Overload the () operator, so that the class can be used like a function call. cmp(a, b)
		bool operator()(const pair<int, int> &a, const pair<int, int> &b)
		{
			return a.second > b.second;
		}	
};

vector<int> topKFrequent(vector<int>& nums, int k) 
{
	// Min heap, sorts based on the second element in the pair (Sorts based on the frequency of each element. Min heap)
	priority_queue< pair<int, int>, vector<pair<int, int>>, cmp > pq;
	
	unordered_map<int, int> hash;	// Hash the frequency of occurrence of each element
	
	// Hash all the numbers in nums[]
	for (int i=0; i<nums.size(); i++)
	{
		hash[nums[i]]++;
	}
	

	// Iterate all the elements in hash. Add to priority que one by one. Keep popping the top of the pq so that only the most frequent k elements remain at the end in the heap
	// At the end, Pq will have the smallest k elements, increasing from heap top to bottom
	for (auto it = hash.begin(); it != hash.end(); it++)
	{
		pair<int, int> temp = {it->first, it->second};
		pq.push( temp );
		
		// If size pq > k, remove the smallest element from pq
		if (pq.size() > k)
		{
			pq.pop();
		}
	}
	
	// Take all the k elements from the priority queue and put it into output[] array
	vector<int> output;
	while ( !pq.empty() )
	{
		output.push_back(pq.top().first);
		pq.pop();
	}
	
	return output;
}


void main()
{
	
}