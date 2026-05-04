/*
	Algorithm: Interleaving
		Pass-1: Iterate through all the nodes of the linked list. For each node, create a clone node and attach it after the original node in the linked list
		Pass-2: Iterate through all nodes, and for each OG node, connect the clone node to the clone of the random node connected to the OG node.
		Pass-3: Split the OG linked list and the clone linked list, using 2 pointers
*/





// Definition for a Node.
class Node {
public:
	int val;
	Node* next;
	Node* random;
	
	Node(int _val) 
	{
		val = _val;
		next = nullptr;
		random = nullptr;
	}
};


class Solution 
{
public:
	Node* copyRandomList(Node* head) 
	{
		if (head == nullptr)	return nullptr;
		
		// First Pass: Interleave clone nodes for each node
		Node* ptr = head;
		Node* new_ptr;
		
		while ( ptr != nullptr )
		{
			new_ptr = new Node(ptr->val);
			new_ptr->next = ptr->next;
			ptr->next = new_ptr;
			
			ptr = ptr->next->next;	// Update
		}
		
		
		// Second Pass: Assign random pointers in clone nodes to their appropriate random clone nodes
		ptr = head;
		while (ptr != nullptr)
		{
			// Corner case: if the current node's random node is a nullptr, then dont do anything to the clone node
			if ( ptr->random != nullptr )
			{
				// Connect the random of clone node to the clone of the random node. (The clones are always the next of the original node)
				ptr->next->random = ptr->random->next;     
			}
			
			ptr = ptr->next->next;	// Update
		}
		
		// Third Pass: Remove the clone list separately
		Node* ptr_1 = head;
		Node* ptr_2 = head->next;
		Node* clone_head = ptr_2;
		
		while ( ptr_1->next->next != nullptr )	// Make sure you stop when ptr_1 and ptr_2 are the last 2 nodes
		{
			ptr_1->next = ptr_1->next->next;
			ptr_2->next = ptr_2->next->next;
			
			ptr_1 = ptr_1->next;	// Update
			ptr_2 = ptr_2->next;
		}
		
		// Set the next for the last 2 nodes in the interleaved list
		ptr_1->next =  nullptr;
		ptr_2->next = nullptr;
		
		
		return clone_head;
	}
};