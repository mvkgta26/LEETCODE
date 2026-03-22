#include <vector>


using namespace std;


struct ListNode 
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};



bool hasCycle(ListNode *head) 
{
	ListNode* slow_pointer;
	ListNode* fast_pointer;
	
	slow_pointer = head;
	fast_pointer = head;
	
	while ( slow_pointer != NULL && fast_pointer != NULL && fast_pointer->next != NULL )
	{
		if ( slow_pointer == fast_pointer )
		{
			return 1;
		}
		
		slow_pointer = slow_pointer->next;
		fast_pointer = fast_pointer->next->next;
	}
}