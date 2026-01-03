/*
	Logic:
		Maintain 2 stacks. One for the actual stack and the other (min_stack) for maintaining the minimum element at each position.
		The min_stack be the same size as the main_stack.
		>> At any time, the top of min_stack will hold the minimum number among all the numbers in the main_stack till (and including) the top
		>> The min_stack will have one number associated with the number at each position of the main_stack. 
			>> The number at each position in the min_stack will hold the minimum number among all the numbers in the main_stack till that position
*/

#include <vector>
#include <stack>

using namespace std;

class MinStack {
	public:
		int min = INT32_MAX;
		stack<int> main_stack, min_stack;
		
		MinStack() 
		{
			// Nothing to initialize
		}
		
		void push(int val) 
		{
			main_stack.push(val);
			
			if (val < min)
			{
				min = val;
			}

			min_stack.push(min);
			
		}
		
		void pop() 
		{
			main_stack.pop();
			min_stack.pop();

			// Update min after popping the top of the stack
			// Also handle the corner case: If after popping the stack, if the stack is empty, the min should have a dummy value
			if ( !min_stack.empty() )
				min = min_stack.top();
			
			else
				min = INT_MAX;
		}
		
		int top() 
		{
			return main_stack.top();
		}
		
		int getMin() 
		{
			return min_stack.top();
		}
};

void main()
{
	
}