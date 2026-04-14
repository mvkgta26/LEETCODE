#include <vector>

using namespace std;

struct ListNode 
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* removeNthFromEnd(ListNode* head, int n) 
{
	// Corner Case: length = 1 and n = 1
	if ( head->next == NULL )
	{
		return NULL;
	}
	
	ListNode* right_ptr, *left_ptr;
	
	left_ptr = head;
	right_ptr = head;
	
	// Move the right pointer ahead by n+1 nodes
	for (int i=0; i < n+1; i++)
	{
		// Corner Case: If n == the length of the linked list (i.e, you have to remove the head), then the right pointer would overflow
		if (right_ptr == NULL)
		{
			ListNode* newHead = head->next;
			delete head;
			return newHead;	
		}
		right_ptr = right_ptr->next;
	}
	
	while (right_ptr != NULL)
	{
		left_ptr = left_ptr->next;
		right_ptr = right_ptr->next;
	}
	// left_ptr will now be the node before the target node that we have to remove deleted
	
	// Relink and Remove the target node
	ListNode* targetNode = left_ptr->next;
	left_ptr->next = left_ptr->next->next;
	delete targetNode;
	
	return head;
}