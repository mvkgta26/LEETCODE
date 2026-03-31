/*
	Exclusion-Product[i] = Product of all elements of nums[i], except nums[i]
	Prefix-Product[i] and Postfix-Product[i] are exclusive of nums[i] itself
	
	Idea:
		Exclusion-Product[i] = Prefix-Product[i] * Postfix-Product[i]
		
	2 Loops: 
		Loop-1: Place prefix product in out[i] 
		Loop-2: Multiply postfix product into out[i], so that out[i] = prefix[i] * postfix[i]  (Note: You can maintain a separate postix array and multiply, but this is more space efficient)
*/


#include <vector>

using namespace std;



vector<int> productExceptSelf(vector<int>& nums) 
{
	int n = nums.size();
	
	if (n == 1)
		return {1};
	
	
		
	vector<int> out(n, 1);
	
	// Calculate prefix product, place prefix product of nums[i] in out[i] (NOTE: Prefix product is exclusive)
	int prefix = 1;
	for (int i=1; i<n; i++)
	{
		prefix = prefix * nums[i-1];
		out[i] = prefix;
	}
	
	// out[i] now holds prefix product of nums[i]
	// The final exclusion product of nums[i] would be prefix[i] * postfix[i]
	// Calculate postfix product, Make out[i] = out[i] * postfix product of nums[i] (NOTE: Postfix product is exclusive)
	int postfix = 1;
	for (int i = n-2; i>=0; i--)
	{
		postfix = postfix * nums[i+1];
		out[i] = out[i] * postfix;
	}

	return out;
}


void main()
{
	
}