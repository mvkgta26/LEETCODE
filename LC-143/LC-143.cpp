/*
	Algorithm:
		1. Find the total length of the linked list
		2. Reverse the second half of the linked list (First half length n/2, second half length n - n/2)
		3. Cross Merge First Half and Reversed Second half of the linked list
*/ 


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



void reorderList(ListNode* head) 
{
	// -------- Count the total number of nodes in the linked list --------
	int n = 0;
	ListNode* node = head;
	while ( node != NULL )
	{
		n++;
		node = node->next;	
	}

	// -------- Handle corner cases: Linked list of length 0, 1, 2 need no changes -------- 
	if ( n== 0 || n == 1 || n==2 )
	{
		return;
	}
	
	int first_half_len = n/2;
	int second_half_len = n - n/2;
	
	// --------  Find the start node of the second half --------
	ListNode* second_half_head = head;
	for (int i=0; i < first_half_len; i++)
	{
		second_half_head = second_half_head->next;
	}
	
	// -------- Reverse the second half of the linked list, and detach it -------- 
	if ( !( second_half_len == 0 || second_half_len == 1 ) )	// Corner cases: If second half of the linked list is of length 1 or 2, dont reverse
	{
		ListNode* p1, *p2, *p3;
		p1 = NULL;
		p2 = second_half_head;
		p3 = second_half_head->next;
		
		while (p3 != NULL)
		{
			// Reverse connect
			p2->next = p1;
			
			// Update
			p1 = p2;
			p2 = p3;
			p3 = p3->next;
		}
		
		p2->next = p1;	// Reverse connect the last node
		second_half_head = p2;		// Update the head of the new reversed second half of the linked list 
	}
	

	// -------- Cross merge the first half and the reversed second half --------
	ListNode* p1, *p1_next, *p2, *p2_next;
	p1 = head;
	p2 = second_half_head;
	p1_next = p1->next;
	p2_next = p2->next;

	while ( p1_next != NULL && p2_next != NULL )
	{
		p1->next = p2;
		p2->next = p1_next;
		
		// Update p1, p2, p1_next and p2_next
		p1 = p1_next;
		p2 = p2_next;
		p1_next = (p1 != NULL) ? (p1->next) : NULL;		// Corner case: To ensure we dont dereference NULL
		p2_next = (p1 != NULL) ? (p2->next) : NULL;
	}
}