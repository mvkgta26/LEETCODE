#include <iostream>
#include <vector>

using namespace std;

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) 
{
	// Build graph using prerequisites[]. adjacency list representation in adj_list[]
	vector<vector<int>> adj_list(numCourses);
	
	for (int i=0; i < prerequisites.size(); i++)
	{
		int out_node = prerequisites[i][0];
		int in_node = prerequisites[i][1];
		adj_list[in_node].push_back(out_node);
	}
	
	
	// Build in-degree[] array
	vector<int> in_degree(numCourses, 0);
	
		// Iterate all the directed edges in the DAG
	for (int i=0; i<adj_list.size(); i++)
	{
		for (int j=0; j<adj_list[i].size(); j++)
		{
			int out_node = adj_list[i][j];
			int in_node = i;
			in_degree[out_node]++;	
		}
	}
	
	// Kahn's Algorithm for topological sort
	vector<int> top_sort;
	
	// Add courses with 0 in-degree, one by one, to the top_sort[] array. Till all the numCourses courses are added to the output topsort[]
	int courses_added = 0;
	while (courses_added < numCourses)
	{
		int cycle_detect_flag = 1;
		
		for (int i = 0; i<numCourses; i++)
		{
			if (in_degree[i] == 0)
			{
				in_degree[i] = -1; // Mark the vertex i as added to the topological sort
				cycle_detect_flag = 0;
				top_sort.push_back(i);
				
				
				// Update the in_degree of all the out-neighbors of vertex i, assuming the vertex-i is now removed from the graph
				for (int j=0; j < adj_list[i].size(); j++)
				{
					in_degree[adj_list[i][j]]--;
				}
				
				
				break;	// Break, because we have already added the vertex with in-degree = 0, in the top_sort array. Go to the next iteration.
			}
		}
		
		// If cycle detected, no top sort possible, return empty
		if (cycle_detect_flag == 1)
		{
			return {};
		}
		
		courses_added++;
	}
	
	return top_sort;
}