	// For temperatures[i] :
	// Find closest index 'j' to the right with higher temperature than	temperatures[i]
	// output[i] = j - i
	// output[i] = 0, if j overflows
	
	
	// Montonic Stack: The stack should only have elements in decreasing order
	// When you push temperatures[i], pop all the elements in stack that have smaller value than temperatures[i]
		// When popping each of these elements, calculate the difference between i and their index. This will be the output for the element temperatures[i]
	
	// Iterate all the elements in temperatures[] from left to right. 
	// The element that is popped temperatures[j].
	// The element that caused it to be popped temperatures[i].
	// i is the closest rightward element to j, such that temperatures[i] > temperatures[j]
		// How ?? Proof by contradiction
	// If after all the iterations, there are some elements left, these have no solution. Make their solution as 0.
	

	
/*
	

*/	
	
#include <vector>
#include <stack>

using namespace std;


vector<int> dailyTemperatures(vector<int>& temperatures) 
{
	int n = temperatures.size();
	vector<int> outputs(n);
	stack<int> decreasing_stack;	// The stack will strictly hold the indices of elements, such that the elements are in decreasing order from bottom to top
	
	// Iterate temperatures[]
	for (int i=0; i < n; i++)
	{
		// Pop all the elements that are smaller than the temperatures[i]. Calculate the outputs for all these popped elements
		while ( !(decreasing_stack.empty()) && temperatures[decreasing_stack.top()] < temperatures[i] )
		{
			outputs[decreasing_stack.top()] = i - decreasing_stack.top();
			decreasing_stack.pop();
		}
		
		decreasing_stack.push(i);	
	}
	
	// Calculate the outputs for all the unpopped elements still in the stack
	// These are elements that have no larger element to their right
	while (!decreasing_stack.empty())
	{
		outputs[decreasing_stack.top()] = 0;
		decreasing_stack.pop();
	}
	
	return outputs;
}


void main()
{
	
}