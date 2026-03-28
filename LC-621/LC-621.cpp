#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>

using namespace std;


int leastInterval(vector<char>& tasks, int n) 
{	
	int num_tasks = tasks.size();
	
	// Hash map for frequency of each task
	unordered_map<char, int> freq;
	for (int i=0; i < num_tasks; i++)
	{
		freq[tasks[i]]++;
	}
	
	// Max-heap priority-queue holding the frequency of the tasks. Max frequency at the top
	priority_queue<int> pq;		
	
	// Iterate the freq hash map and push each element to the priority que
	for ( auto f = freq.begin(); f != freq.end(); f++ )
	{
		// Make {frequency_count, task-name} pair and push to max-heap pq
		pair<int, char> curr_pair = {f->second, f->first};
		pq.push(f->second);
	}
	
	
	// A queue that holds { current chosen task frequency, next-possible-usage-slot }
	queue<pair<int, int>> cooldown_que;
	int curr_slot = 0;	// The time slot
	
	while ( !pq.empty() || !cooldown_que.empty() )
	{
		// If the tasks executed last time are eligible are to run again, pop then off from the cooldown queue and push into the priority queue
		while ( !cooldown_que.empty() && curr_slot >= cooldown_que.front().second )
		{
			pq.push( cooldown_que.front().first );	
			cooldown_que.pop();
		}
		
		// If the priority queue is empty, you cannot execute any task in this time slot. It will be an idle slot
		if ( !pq.empty() )
		{
			//char curr_chosen_task = pq.top().second;
			int curr_chosen_task_freq = pq.top();
			
			pq.pop();	// Pop the chosen task from the pq
			
			curr_chosen_task_freq--;	// Since the current task is now executed once, reduce its freq
			
			// Current task is executed in this cycle. Push it to the cooldown queue
			// Push the current task to the cooldown queue: {new frequency of this task, the next slot when it is eligible to execute again}
			if ( curr_chosen_task_freq != 0 )	// If the current task is done executing all its occurrences, then it is completed. Dont add to the cooldown queue.
			{
				cooldown_que.push(make_pair(curr_chosen_task_freq, curr_slot + n + 1));		
			}
		}
		
		curr_slot++;
	}
	
	
	return curr_slot;
}