/*
Refer one note for diagram 

	What should we calculate?
		For element i: Find closest index 'j' to the right with higher temperature than	temperatures[i]
						output[i] = j - i
						output[i] = 0, if j overflows

	Algorithm:
		Iterate the indices in temperatures[]
			Check if there are elements in the stack that are smaller than temperatures[i]
				If yes: Pop all the indices of these smaller elements from the stack: j. Calculate the outputs for these indices (i-j) and place then in the outputs[j]
			Push index i to stack
		The stack will still have indices left. 
			These are elements that have no larger elements to their right in the array
			Pop all these elements. Calculate the outputs for these indices (j-i) and place then in the outputs[] array

	Claim:
		Let the element that is popped from stack: temperatures[j].
		Let the element that caused it to be popped temperatures[i].
		i is the closest element to the right of j, such that temperatures[i] > temperatures[j]
		How: Proof: If there was another element closer to j (between j and i), it would have already caused i to be popped in a previous iteration. But since 'i' is not popped, we know that j is the closest element 
		
	
	Claim: Corner Case: Indices left after iterating all the elements in temperatures[]. These are the elements that have NO larger element to the right.
		 Proof: Obvious
			
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