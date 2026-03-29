/*

	Main Greedy Idea: At any time slot, out of all the eligible tasks, choose the task with the highest number of task-occurrences/frequency left. PROOF: Not doing. Intuition.

	Algorithm:
		1. Hash the frequency of all the tasks 
		2. Push all the frequencies to a max-heap priority queue. Invariant: Each element in the max-heap represents a task that is eligible to run in the current slot. (Location of Invariant after the innter while loop where the cooldown queue is unloaded into pq). PROOF: Not doing. Intuition.
		3. Pop all the tasks that are eligible to run in the current slot from the cooldown_queue into pq
		4. Now, Pop the top of the pq: This will be the task with highest frequency at the moment. Choose to run this in this slot. (If there is nothing in the pq, and the cooldown queue is full, that means this will have to be an idle slot.)
			4.1. Subtract 1 from the frequency of this currently chosen task. This is because it has been executed once in this slot.
			4.2. Push the next eligible slot for this task into the cooldown queue. (Invariant: The cooldown queue represents all tasks that are waiting for their next respective slots, in the increasing order of their next eligible slot from front to back.) (Invariant position after the inner while loop) PROOF: Not doing. Intuition.
		5. When the priority queue is empty and the cooldown queue is empty, that means all the tasks completed running all their frequencies. END. Return the number of slots so far.
*/


#include <vector>
#include <queue>
#include <utility>
#include <unordered_map>

using namespace std;


int leastInterval(vector<char>& tasks, int n) 
{	
	int num_tasks = tasks.size();
	
	// Hash frequency of each task
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
		// Push the frequencies of all tasks to the priority queue 'pq'
		pq.push(f->second);
	}
	
	
	// A queue that holds { current chosen task frequency, next-possible-usage-slot }
	queue<pair<int, int>> cooldown_que;
	int curr_slot = 0;	// The time slot
	
	while ( !pq.empty() || !cooldown_que.empty() )
	{
		// If the tasks executed last time are eligible are to run again, pop then off from the cooldown queue and push their frequencies into the priority queue
		while ( !cooldown_que.empty() && curr_slot >= cooldown_que.front().second )
		{
			pq.push( cooldown_que.front().first );	
			cooldown_que.pop();
		}
		
		// If the priority queue is empty, you cannot execute any task in this time slot. It will be an idle slot
		if ( !pq.empty() )
		{
			int curr_chosen_task_freq = pq.top();
			pq.pop();	// Pop the chosen task from the pq
			
			curr_chosen_task_freq--;	// Since the current task is now executed once, reduce its freq
			
			// Current task is executed in this cycle. Push it to the cooldown queue
			// Push the current task to the cooldown queue: {new frequency of this task, the next slot when it is eligible to execute again} . The next-eligible-slot =  (curr_slot + n + 1) because there has to be a gap of n slots between current slot and the next elgible slot for this task
			if ( curr_chosen_task_freq != 0 )	// If the current task is done executing all its occurrences, then it is completed. Dont add to the cooldown queue.
			{
				cooldown_que.push(make_pair(curr_chosen_task_freq, curr_slot + n + 1));		
			}
		}
		
		curr_slot++;
	}
	
	return curr_slot;
}