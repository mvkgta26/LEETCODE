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


ListNode* reverseList(ListNode* head) 
{
	// Edge case: Linked list of length 0 or 1
	if (head == NULL || head->next == NULL )
	{
		return head;
	}
	
	ListNode* p1 = NULL;
	ListNode* p2 = head;
	ListNode* p3 = head->next;
	
	while( p3 != NULL )
	{	
		p2->next = p1;
		
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	
	p2->next = p1; // Reverse connect the last node
	
	return p2;	// Return the new head
}