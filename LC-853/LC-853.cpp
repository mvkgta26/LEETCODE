/* 
Let cars c1, c2, c3 , ..., cn be arranged such that their positions are in decreasing order p1 > p2 > p3 > ... > pn

Claim-1: Cars c1, c2, .. ck can become a fleet only if speeds s1 < s2 < .. < sk. (Necessary)
			Proof: Obvious. The cars that start at previous positions need more speeds to catch up to cars with forward positions

Claim-2: [Sufficient]: Let Cars ci and cj, where j>i. Let ti and tj be the calculated time taken by the cars ci and cj, on their own, to reach target.
		Cars Ci and Cj will form a fleet, if and only if, ti > tj. That is, on its own, car Cj can reach target earlier than Ci. 
		Proof: If ti > tj, since ci is ahead of cj, cj will surely meet ci at some point. Not doing the subtler working for this proof. 

			
Claim-3: If cars [ci, ci+1, .. ,cj] form a fleet, then the time taken by all the cars in the fleet to reach the target will be the 
time taken by the first car ci to reach the target. 
			Proof: ci is the slowest car, at the farthest position.
				   All the other cars in the fleet, by rule, will be restricted to the speed of the slowest car, vi
				   No car can overtake ci. At a certain position before target, each of the other cars in the fleet join with Ci and drive at the same speed.
				   All the cars in the fleet reach target at the same time. 

Claim-4: Let cars [c1, c2, .., ci] be a fleet f1. Assume car ci+1 cannot reach this fleet f1.
		Then, NONE OF THE CARS after Ci+1 can reach fleet f1.
		Proof: Ci+1 cannot reach the fleet f1. Any cars after Ci+1, even if they are faster, will not be able to overtake Ci+1. 
				Hence, they cannot reach the fleet f1, they will be restricted by Ci+1.

				
Algorithm:
	1. Sort the cars as (position, speed) pairs, in decreasing order of position of each car
	2. Iterate all the cars, calculate the 'time to reach target' t of each car
	3. Maintain a stack. Push the 't' of each car. 
		3.1. But before pushing the 't' of each car, pop out all the previous cars from the stack top that have higher/equal 't' than this car
				(Basically pop all the other cars in the stack that belong to the same fleet as this car)
	4. At the end, the car_stk will have the "time to target" of one car of each fleet (the car with furthest back inital position)
	
					The size of the car_stk will be the number of fleets. Return this.

*/

#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

bool pos_cmp(const pair<int, int>& p1, const pair<int, int>& p2)
{
	return p1.first < p2.first;		// To sort in descending order
}

// To calculate the time taken by a car to reach target, starting at position p, with speed s, 
double time_taken_to_reach(int p, int s, int target)
{
	double t = double(target - p) / s;	// Distance / speed
	
	return t;
}

int carFleet(int target, vector<int>& position, vector<int>& speed) 
{
	int n = position.size();	// Number of cars
	vector<pair<int, int>> pos_speed_arr;
	
	// Make pairs of {position, speed} and append them into pos_speed_arr
	for (int i=0; i<n; i++)
	{
		pair<int, int> p = {position[i], speed[i]};
		pos_speed_arr.push_back(p);		
	}
	
	// Sort in descending based on position
	sort(pos_speed_arr.begin(), pos_speed_arr.end(), pos_cmp);
	
	
	stack<double> car_stk;
	
	// Iterate the pos_speed[] array
	for (int i=0; i < n; i++)
	{
		double t = time_taken_to_reach(pos_speed_arr[i].first, pos_speed_arr[i].second, target);
		
		// Pop all the cars in the stack that reach target after the car 'i' (Pop all cars that Take more time than car i)
		// Basically pop all the other cars in the stack that belong to the same fleet as this car.
		// At the end, the car_stk will have the "time to target" of one car of each fleet (the car with furthest back inital position)
		while ( !car_stk.empty() && car_stk.top() <= t )
		{
			car_stk.pop();
		}
		
		// Push the current car 'i' to the stack
		car_stk.push(t);
	}
	
	
	return car_stk.size();
}

