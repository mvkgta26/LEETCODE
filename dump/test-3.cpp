#include <iostream>
#include <stack>
#include <climits>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;




struct ListNode 
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

bool hasCycle(ListNode *head) 
{
	if (head == nullptr || head->next == nullptr)
	{
		return false;
	}
	
	ListNode* slow_ptr = head;
	ListNode* fast_ptr = head->next;
	
	while (fast_ptr != nullptr && fast_ptr->next != nullptr)
	{
		if (fast_ptr == slow_ptr)
		{
			return true;
		}
		
		slow_ptr = slow_ptr->next;
		fast_ptr = fast_ptr->next->next;
	}
	
	return false;
}