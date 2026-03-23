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



ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) 
{
	if (list1 == NULL)
	{
		return list2;
	}	
	
	if ( list2 == NULL )
	{
		return list1;
	}
	
	ListNode* new_head = ( list1->val <= list2->val ) ? list1 : list2;	// New head of the merged linked list
	
	ListNode* node1 = list1;
	ListNode* node2 = list2;
	
	ListNode* ptr = new_head;	// This pointer will point to the tail node of the sorted list
	
	// Update node1 and node2 to point to the next node in consideration in each of these linked lists
	if (node1->val <= node2->val)
	{
		node1 = node1->next;
	}
	else
	{
		node2 = node2->next;
	}

	while (node1 != NULL && node2 != NULL)
	{
		if (node1->val <= node2->val)
		{
			ptr->next = node1;
			ptr = node1;
			
			// Update node1
			node1 = ( node1 != NULL ) ? node1->next : NULL;
		}
		
		else
		{
			ptr->next = node2;
			ptr = node2;
			
			// Update node2
			node2 = ( node2 != NULL ) ? node2->next : NULL;
		}
	}
	
	if (node1 == NULL)
	{
		ptr->next = node2;
	}
	
	else
	{
		ptr->next = node1;
	}

	return new_head;
}