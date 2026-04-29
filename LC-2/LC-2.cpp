
 
struct ListNode 
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
	
	int carry = 0;
	int curr_sum = 0;
	
	ListNode* dummy_head = new ListNode(0);
	ListNode* result_itr = dummy_head;
	ListNode* new_node = new ListNode();
	result_itr->next->next = new_node;
	
	
	// Iterate till either of the linked lists reach an end
	while ( l1 != nullptr && l2 != nullptr )
	{
		curr_sum = l1->val + l2->val + carry;
		
		if ( curr_sum > 9 )
		{
			carry = 1;
			curr_sum = curr_sum - 10;
			
			result_itr->next->val = curr_sum; 
		}
		
		else
		{
			carry = 0;
			result_itr->next->val = curr_sum; 
		}
		
		ListNode* new_node = new ListNode();
		result_itr->next->next = new_node;
		result_itr = result_itr->next;
		
		// Update l1 and l2
		l1 = l1->next;
		l2 = l2->next;
	}
	
	
	while ( l1 != nullptr )
	{
		curr_sum = l1->val + carry;
		
		if ( curr_sum > 9 )
		{
			carry = 1;
			curr_sum = curr_sum - 10;
			
			result_itr->next->val = curr_sum;  
		}
		
		
		else
		{
			carry = 0;
			result_itr->next->val = curr_sum; 
		}
		
		ListNode* new_node = new ListNode();
		result_itr->next->next = new_node;
		result_itr = result_itr->next;
		
		// Update l1 and l2
		l1 = l1->next;
	}
	
	
	while ( l2 != nullptr )
	{
		curr_sum = l2->val + carry;
		
		if ( curr_sum > 9 )
		{
			carry = 1;
			curr_sum = curr_sum - 10;
			
			result_itr->next->val = curr_sum;
		}
		
		
		else
		{
			carry = 0;
			result_itr->next->val = curr_sum;  
		}
		
		ListNode* new_node = new ListNode();
		result_itr->next->next = new_node;
		result_itr = result_itr->next;
		
		// Update l1 and l2
		l2 = l2->next;
	}
	
	// Final carry over
	if (carry == 1)
	{
		result_itr->next->val = 1;
		
		ListNode* new_node = new ListNode();
		result_itr->next->next = new_node;
		result_itr = result_itr->next;
		
		carry = 0;
	}
	
	result_itr->next = nullptr;
	
	return dummy_head->next;
}