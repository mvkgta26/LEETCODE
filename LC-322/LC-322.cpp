/*

	Claim: To get total sum of any positive amount, the solution-set of coins that we use should have at least ONE coin of any denomination
	
	
	
	dp[i] = minimum number of coins needed to make total amount i.
			
	Recurrence Relation:
		For each amount i, try all coin denominations c such that c ≤ i:

			dp[i] = min(dp[i - c] + 1)  for all c in coins[]

		Explanation:
			>> To make amount i, assume you choose 1 coin of c. Using coin c contributes 1 coin
			>> The remaining amount (i - c), can be filled with the minimum number of coins dp[i - c]
			>> Among all choices of c, we pick the minimum total of dp[i-c] + 1. This will be the minimum number of coins needed to obtain a sum total of i
	
*/

#include<vector>
#include<climits>


using namespace std;


int coinChange(vector<int>& coins, int amount) 
{
	vector<int> dp(amount + 1, INT_MAX);
	
	// Base Case: You need 0 coins to make sum amount = 0
	dp[0] = 0;
	
	
	for ( int i=1; i < amount + 1; i++ )
	{
		int min_coins = INT_MAX;
		
		// Iterate all the coins. Choose one instance of coin c for each iteration
		// Find the minimum number of coins needed to obtain amount = i, among all choices of c
		for (int j=0; j < coins.size(); j++)
		{
			int c = coins[j];
			
			if ( (i - c) >= 0 && dp[i - c] != INT_MAX )		// Avoid corner cases: Make sure index i-c is not negative. Also dp[i - c] is not INT_MAX to avoid overflow when adding 1 ( You cannot even attain i-c sum with any set of coins. So by choosing coin c, you cannot attain the total of i at all  )
			{
				min_coins = min( min_coins,  			 
								 1 + dp[ i - c ] ); 	// // 1 coin of c +  Minimum number of coins needed to attain total i - c 
			}
		}
		
		dp[i] = min_coins;
	}
	
	// CORNER CASE: If no possible solution, return -1
	if (dp[amount] == INT_MAX)
	{
		return -1;
	}
	
	return dp[amount];		// dp[amount] is the minimum number of coins needed to obtain sum amount
}