#include <iostream>
#include <vector>


using namespace std;

int dfs_helper(int node, vector<vector<int>>& adj_list, vector<int>& visited, vector<int>& parent, int& cycle_start_node)
{
	visited[node] = 1;	// Mark node as visited --
	
	// Iterate the neighbors of the node and make DFS calls to each of the unvisited neighbors
	for (int i=0; i < adj_list[node].size(); i++)
	{
		int nbr_node = adj_list[node][i];
		
		// Recrursive DFS call on unvisited neighbor
		if (visited[i] == 0)
		{
			parent[nbr_node] = node;		// Note down the parent node
			dfs_helper(nbr_node, adj_list, visited, parent, cycle_start_node);	
		}
		
		// If the neighbor is the parent of the current node, just ignore 
		else if (nbr_node = parent[node])
		{
			// Do nothing, skip iteration for this node
		}
		
		// Already visited neighbor vertex: We encountered a cycle node. 
		//Set cycle_start_node. Break DFS and start trace back.
		else
		{
			cycle_start_node = nbr_node;  // Consdier this nbr_node as the start of the cycle within the graph
			parent[nbr_node] = node;	// The nbr_node is encountered again, because it is in a cycle. Change the parent of this nbr_node to this new one. This will trace the cycle path
			
			// return cycle_start_node;
		}
	}
	
	return 0;	// Dummy Return
}



vector<int> findRedundantConnection(vector<vector<int>>& edges) 
{
	// Number of nodes in the graph = Number of edges in the graph , if there is one cycle in the graph
	// Why??
	int n = edges.size();	
	
	// Convert edges to adjacency list
	vector<vector<int>> adj_list(n);
	for (int i=0; i < edges.size(); i++)
	{
		adj_list[edges[i][0]].push_back(edges[i][1]);
	}
	
	
	vector<int> parent(n, -1);	// parent[] array: parent[i] = j, means the DFS call to the node-i was called from the node-j. Used to trace DFS path
	vector<int> visited(n, 0);
	
	int src = 1;
	int cycle_start_node = -1;
	visited[src] = 1;
	dfs_helper(src, adj_list, visited, parent, cycle_start_node);	// DFS call from the source node. Get the value of cycle_start_node and parent[] array

	
	// // Iterate the neighbors of the node and make DFS calls to each of the neighbors
	// for (int i=0; i < adj_list[src].size(); i++)
	// {
	// 	int nbr_node = adj_list[src][i];
		
	// 	if (visited[i] == 0)
	// 	{
	// 		parent[nbr_node] = src;		// Note down the parent node
	// 		cycle_start_node = dfs_helper(nbr_node, adj_list, visited, parent);	
	// 	}
	// }
	
	
	// Iterate the edges array from right to left. (The question asks for the edge that occurs rightmost and which when removed will make it acyclic)
	// Find the first edge that has both nodes in the cycle. This will be an edge within the cycle
	// This edge will be the solution
	// Removing any edge from a cycle will make it NOT A CYCLE 
	
	// Prepare a hash map for cycle nodes. All the nodes in the parent[] array are the cycle nodes
	vector<int> cycle_node_hash(n, 0);	// cycle_node_hash[i] == 1, if the node 'i' is a cycle node
	
	// Iterate all the nodes of the cycle starting from the cycle_start_node, till we reach the cycle_start_node again. Using parent[] map	
	// Mark all the nodes in the cycle in the cycle_node_hash[]
	int node = cycle_start_node;
	while (parent[node] !=  cycle_start_node)
	{
		cycle_node_hash[node] = 1;
		node = parent[node];	// Update node
	}
	
	// Iterate edges from right to left and return the first cycle edge 
	for (int i = edges.size() - 1; i>=0; i--)
	{
		// If both the nodes of the edge are cycle nodes, this edge is a cycle edge
		if ( ( cycle_node_hash[ edges[i][0] ] == 1 ) && ( cycle_node_hash[ edges[i][1] ] == 1 ) )
		{
			return edges[i];
		}
	}
	
	return{};	// Dummy return
}


void main()
{
	

}
