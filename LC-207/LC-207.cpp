#include <vector>

using namespace std;

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
{
	// Create adjacency list. Total numCourses number of nodes in the graph.
	vector<vector<int>> adj_list(numCourses);
	
	// Build graph adjacency list
	for (int i=0; i < prerequisites.size(); i++)
	{
		int from_node = prerequisites[i][1];
		int to_node = prerequisites[i][0];
		
		adj_list[from_node].push_back(to_node);
	}
	
	
	// Topological sort detection
	vector<int> indegree(numCourses);	// indegree[i] = Number of edges going into the node i
	
	// Initialize indegree
	for (int i=0; i < numCourses; i++)
	{
		for (int j=0; j < adj_list[i].size(); j++)
		{
			indegree[adj_list[i][j]]++;	
		}
	}
	
	
	// Toplogical sort algorithm: Choose the node with the indegree 0. 
	// If at any stage, there is no node with indegree == 0, that means topological sort is not possible. Which means the graph is cyclic
	
	// Array that will hold the nodes in topological sorted order
	vector<int> top_sorted(numCourses);
	
	// Each node to add to the top_sorted array
	for (int i=0; i < numCourses; i++)
	{
		int cyclic_flag = 1;
		
		// Check for node with indegree 0 from all the nodes in the graph
		for (int j=0; j<numCourses; j++)
		{
			if(indegree[j] == 0)
			{
				// Node 'j' is chosen next in the topological sort
				indegree[j] = -1;
				
				cyclic_flag = 0;
				top_sorted.push_back(j);
				
				// Update the indegree of all the out neighbors of node 'j'
				for (int k=0; k < adj_list[j].size(); k++)
				{
					int out_node_from_j = adj_list[j][k];
					indegree[out_node_from_j]--;
				}
				
				break;	// The next node for the current index in the topological sort is already is found
			}
		}
		
		if (cyclic_flag == 1)
			return 0;
	}
	
	return 1;
}

int main()
{
	
}