/*

	REFER ONENOTE FOR VISUAL 

	2 methods:
		Method-1: 
			Have a hash[10^5+1] :  A hash of all possible numbers that could occur. hash[i] = Number of times the number i occurs.
			Find i such that hash[i] > 1.  
			This is O(1) space
		
		Method-2: Linked list cycle
		
			Visualize nums array as a linked list
			Think of each index i as a node with pointer value i
			Think of nums[i] as the next pointer: nums[i] is the pointer/adddress of the next node
			That is: The node at address 'i' points to the next node at address nums[i]
			
			Floyd tortoise-hare algorithm:
				Phase-1: Find if 2 nodes coincide with fast and slow.
				Phase-2 (Cycle entry point detection): Reset slow = 0, head of the linked list. Continue fast from the saved state. Fast should now move at same speed as slow.
														The meeting point node now is the cycle entry point, which is the repeated number. 

*/



#include <vector>



using namespace std;



int findDuplicate(vector<int>& nums) 
{
	// Now use tortoise-hare algorithm to find cycle in this linked list. There will be a cycle if 2 nodes have the same next node. That is, if 2 indices in the array nums[] have the same value
	
	
	// Phase-1 of tortoise hare algorithm: Find if there is a cycle
	// fast and slow are node values, nums[fast] and nums[slow] are node pointers
	int slow = nums[0];	// 1 node ahead
	int fast = nums[nums[0]];	// 2 nodes ahead	
	   
	while ( slow != fast )
	{
		slow = nums[slow];	// 1 node ahead
		fast = nums[nums[fast]];	// 2 nodes ahead
	}
	
	
	// Phase-2: Detects the start of the cycle. Entry point is the repeated number
	// Phase 2 of tortoise-hare algorithm: Fast pointer continues from saved state and moves by one node instead of 2. Slow is initialized to node 0 
	slow = 0;
	while ( slow != fast )
	{
		slow = nums[slow];	// 1 node ahead
		fast = nums[fast];	// Also 1 node
	}
	
	
	return slow;
}