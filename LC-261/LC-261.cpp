/*
	// A tree is an unidrected graph that is Connected and Acyclic

	
	Data Structures: 
		HASH-MAP: visited[n]
			If visited[i] == 1, if node i is already visited in DFS traversal. DFS call has already been made to that node.
		
		adj_list: adjacency list of the graph, converted from edges[] array given as input
		
		
	DFS Based Algorithm: 
			Start with node 0 as source and perform DFS
			
			With each node, perform DFS calls on all its neighbors (except the parent node obviously)
				Cycle Detection (**NO PROOF**): Check if this new node HAS ALREADY been VISITED in DFS. If it has already been visited, that MEANS A CYCLE IS DETECTED. Return FALSE, GRAPH NOT A TREE
			
		After the DFS traversal is complete:
			If the DFS traveral is fully complete without returning False, that means there is no cycle detected. 
			Check for connected graph:
				Count the number of visited nodes. If all the n nodes are visited in the DFS: It is CONNECTED. 
				Otherwise, not connected, return False.
			
		If there is no cycle detected, and the graph is connected: Then it is a tree. Return True.
*/

#include <vector>
#include <map>
#include <iostream>

using namespace std;

// Performs dfs from the node 'node'. Traverses all the nodes connected to 'node', except the parent node 'prev_node'
// Returns False if any cycle is detected in this DFS. Return True otherwise.
bool dfs_helper(int node, int prev_node, vector<vector<int>> &adj_list, vector<int>& visited)
{
	visited[node] = 1;
	int out = 1;
	
	// Iterate all the neighbors of the node i, and make dfs calls with each of them
	for (int i=0; i < adj_list[node].size(); i++)
	{
		int neighbor_node = adj_list[node][i];
		
		// Iterate neighbors of node 
		// Ensure you do not iterate the parent which made this DFS call (prev_node)
		if ( neighbor_node != prev_node )
		{
			// If the neighbor is not the parent, and is previously already visited, that means there is a cycle
			if ( visited[neighbor_node]==1 )
			{
				return false;	// Cycle detected	
			}
			
			out = out && dfs_helper(neighbor_node, node, adj_list, visited);	// DFS call to neighbor node with the current node as prev
		}
	}

	return out;
}


bool validTree(int n, vector<vector<int>>& edges) 
{
	// Create adjacency list from the edges list
	vector<vector<int>> adj_list(n);	// One list for each of the n nodes
	
	for (int i=0; i<edges.size(); i++)
	{
		adj_list[edges[i][0]].push_back(edges[i][1]); 
		adj_list[edges[i][1]].push_back(edges[i][0]);
	}
	
	// Create and initialize visited structure: vector position based hash
	// visited[i] means that the node i is visited
	vector<int> visited(n, 0);
	
	// Make DFS call with 0 as node. Use dummy node -1 as previous node
	int out = 1;
	int prev_node = -1; // Dummy previous node for node 0
	int node = 0;	// DFS source as 0
	visited[node] = 1;
	
	// Iterate all the neighbors of the node 0, and make dfs calls with each of them
	for (int i=0; i < adj_list[node].size(); i++)
	{
		int neighbor_node = adj_list[node][i];
		
		// Iterate neighbors of node 
		// Ensure you do not iterate the parent which made this DFS call (prev_node)
		if ( neighbor_node != prev_node )
		{
			// If the neighbor is not the parent, and is previously already visited, that means there is a cycle
			if ( visited[neighbor_node] == 1 )
			{
				return false;	// Cycle detected	
			}
			
			out = out && dfs_helper(neighbor_node, node, adj_list, visited);	// DFS call to neighbor node with the current node as prev
		}
	}
	
	
	// Check if the graph is connected: After the DFS, check if all the 'n' nodes are visited
	for (int i=0; i<n; i++)
	{
		// If even a single node in the graph is unvisited, graph is unconnected. Graph is not a tree.
		if (visited[i] == 0)
		{
			return false;
		}
	}
	
	return out;
}


int main()
{
	int n = 5;
	vector<vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}, {1, 4}};
	
	int out = validTree(n, edges);
	
	cout << "The answer is: " << out << endl;
	
	return 0;
}








