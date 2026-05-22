/*
	2 approaches:
		Approach-1: Set: Keep performing digit-square-sum. Use a hash-map or unordered-set to keep track of previously obtained numbers for finding loop.

		Optimized Approach-2: Floyd-Cycle : 2 numbers: fast and slow numbers.  
				Imagine each number acquired in the series of repeated digit Square Sum as a node in the linked list
				Have fast_num and slow_num, both start at n.
					slow_num jumps 1 node: digitSquareSum is performed once to update
					fast_num jumps 2 nodes: digitSquareSum is performed twice to update
					If there is a loop in the abstract linked list, the fast_num and the slow_num will clash at some point.
				
				Otherwise, they will converge to 1

		Approach-2 saves space needed for set and has same time complexity      
*/


#include <string>
#include <unordered_set>


using namespace std;

// Helper function
int calculateDigitSquareSum(int n)
{
	string num_str = to_string(n);
	 
	// Perform digit-square-sum on the number num
	int sum = 0;
	for (int i=0; i < num_str.size(); i++)
	{
		int d = num_str[i] - '0';
		sum = sum + d*d;
	}
	
	return sum;
}



/*
	Imagine each number acquired in the series of repeated digit Square Sum as a node in the linked list
	
	Have fast_num and slow_num, both start at n.
		slow_num jumps 1 node: digitSquareSum is performed once to update
		fast_num jumps 2 nodes: digitSquareSum is performed twice to update
		If there is a loop in the abstract linked list, the fast_num and the slow_num will clash at some point.
	
	Otherwise, they will converge to 1
*/
bool isHappy(int n) 
{	
	int slow_num = n;
	int fast_num = n;
	
	// Keep performing digit-square-num till the number num decays to 1. That is the only way that the number converges to a point, instead of looping
	// If the number decays, the fast_num will go to 1 first, no need to wait for slow pointer
	while ( fast_num != 1 )
	{
		slow_num = calculateDigitSquareSum(slow_num);
		fast_num = calculateDigitSquareSum(calculateDigitSquareSum(fast_num));
			
		// Floyd cycle detection algorithm loop detection
		if ( (fast_num != 1) && (fast_num == slow_num ) )
		{
			return false;
		}
	}

	return true;
}


	// Unoptimized approach
// bool isHappy(int n) 
// {	
// 	int num = n;
// 	unordered_set<int> num_set;
	
// 	// Keep performing digit-square-num till the number num decays to 1. That is the only way that the number converges to a point, instead of looping
// 	while ( num != 1 )
// 	{
// 		num = calculateDigitSquareSum(num);
			
// 		// If the number num was already obtained, there is a loop. NOT A HAPPY NUMBER
// 		if ( num_set.find(num) != num_set.end() )
// 		{
// 			return false;
// 		}
		
// 		num_set.insert(num);
// 	}

// 	return true;
// }

