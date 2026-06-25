#include <iostream>
#include <stack>
#include <climits>

using namespace std;


// If all the digits are 9, only then the size of the output will +1 of the input

// vector<int> plusOne(vector<int>& digits) 
// {
// 	int n = digits.size();
// 	int output_size = n;
	
// 	// Corner Case: Check if all the digits are 9, and if so the output length will be input length + 1
// 	int nine_flag = 1;
// 	for (int i=0; i<n; i++)
// 	{
// 		if ( digits[i] != 9 )
// 		{
// 			nine_flag = 0;
// 			break;
// 		}
// 	}
	
// 	if (nine_flag == 1)
// 	{
// 		output_size++;
// 	}
	
// 	vector<int> output(output_size);
	
// 	int sum;
// 	int carry = 1;		// Set initially to 1, so that it acts as if you are adding 1 to LSB
// 	int output_i = output_size - 1;
	
// 	for (int i=n-1; i>=0; i--)
// 	{
// 		sum = digits[i] + carry;
// 		carry = 0;	// Reset carry
		
// 		if (sum == 10)
// 		{
// 			carry = 1;
// 			sum = 0;
// 		}
		
// 		output[output_i] = sum;
// 		output_i--;
// 	}
	
// 	// Final carry, set MSB in output
// 	if (carry == 1)
// 	{
// 		output[0] = 1;
// 	}
	
// 	return output;
// }



vector<int> plusOne(vector<int>& digits) 
{
	int n = digits.size();
	
	// Corner Case: Check if all the digits are 9, and if so the output length will be input length + 1
	//int nine_flag = 1;
	int sum;
	
	for (int i=n-1; i>=0; i--)
	{
		// Early stop case
		// If LSB != 9, Increment the LSB and return immediately. No problem with carry, only the LSB changes
		if (i == n-1 && digits[i] != 9)
		{
			digits[i] = digits[i] + 1;
			return digits;
		}
		
		// Early stop case: Carry gets passed only as long as there are contiguous 9's from right. Ex" 28589999
		// The carry stops from the current digit if it is not 9. No more carries passed to the left from this digit onward.
		if (digits[i] != 9)
		{
			digits[i] = digits[i] + 1;
			return digits;
		}
		
		/// Make 9 digit to 0
		digits[i] = 0;
	}
	
	// If the for loop does not prematurely end, that means there is a final carry
	// If all digits are 9, add final carry as MSB
	digits.insert(digits.begin(), 1);
	
	return digits;
}
