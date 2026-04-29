/*
	Main Idea: To Handle Overflow:
		Catch overflow without actually computing an overflowed number and storing it. You only have 32 bits.
		Let k be the number of digits in the INT_MAX
		So do overflow only when reversed is k-1 digits long
		
		Check if the number of digits in reversed is k-1. Potential for overflow.
			Check if the MSB k-1 digits in reversed > MSB k-1 digits in INT_MAX.
				If yes, OVERFLOW.
		
		Check if the MSB k-1 digits in reversed == MSK k-1 digits in INT_MAX
			If yes, check the next digit to be added in the LSB in reversed IS GREATER  than the LSB Of INT_MAX
				If yes, OVERFLOW.
*/



#include <climits>


int reverse(int x) 
{
	int num = x;
	int reversed = 0;
	
	
	// Loop works for both positive and negative. % operator preserves sign
	while ( num != 0 )
	{
		
		if ( reversed > 0 )
		{
			// Overlflow check
			// We have to catch oveflow, without actually computing and storing a overflowed number (32 bit limit)
			// In the next step, we will do reversed * 10
			// Check if, after doing reversed * 10, the number of digits in reversed = number of digits in INT_MAX
				// And if they are equal, check if the most significant digits, leaving out the 0th bits in both, reversed > INT_MAX. THIS SURELY MEANS OVERFLOW
			if ( reversed > INT_MAX/10 )
			{
				return 0;
			}
			
			
			// Check if all the digits so far, except the LSB, reversed == INT_MAX
			// Now check only the upcoming digit, > , the LSB of INT_MAX
			else if ( reversed == INT_MAX/10 ) 
			{
				// num % 10 is the next upcoming digit
				if ( (num % 10) > INT_MAX % 10 ) 
				{
					return 0;
				}
			}
		}
		
		
		if ( reversed < 0 )
		{
			// Similar to the check for reversed > 0
			if ( reversed < INT_MIN /10 )
			{
				return 0;
			}
			
			else if ( reversed == INT_MIN/10 ) 
			{
				// num % 10 is the next upcoming digit
				if ( (num % 10) < INT_MIN % 10 ) 
				{
					return 0;
				}
			}
		}
		
		
		// Main reverse logic
		reversed = reversed*10 + (num % 10);
		num = num/10;		
	}

	return reversed;
}