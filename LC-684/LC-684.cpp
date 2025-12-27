/*

REFER ONENOTE FOR DETAILS

Algorithm:
	1. Perform DFS and return the first cycle node that you encounter.
		a. As you perform DFS, keep track of the parent of each node in their respective DFS paths.
			parent[] array: parent[i] = j, means the DFS call to the node-i was called from the node-j. 
			
	2. If we back track the DFS path from this cycle node back to itself, using the parent[] array, that will give us ALL THE NODES WITHIN 
	THE CYCLE IN THE GRAPH. (We know a DFS path went from this node, to this node again cyclically, because we visit an already visited vertex during our DFS traversal)

	3. Hash all the Cycle nodes.
	
	4. Iterate the edges[] from right to left. Edges that have both nodes as cycle nodes, will be cycle edges. (Use cycle node hash for this)
		Remove the first cycle edge that you encounter. 
		This will be the solution: The right most edge that can be removed to make the graph acyclic, and hence a tree.
*/


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
		if (visited[nbr_node] == 0)
		{
			parent[nbr_node] = node;		// Store the parent node
			
			// If the child in the branch path detected a cycle, it will return 1.
			// If cycle node is detected in this branch path from this node, immediately return 1. All we need is 1 cycle node.
			// You don't have to look for all the other branch paths going from all the other neighbors of this node. 
			if (dfs_helper(nbr_node, adj_list, visited, parent, cycle_start_node))	
				return 1;	
		}
		
		// If the neighbor is the parent of the current node, just ignore 
		else if (nbr_node == parent[node])
		{
			// Do nothing, skip iteration for this node
		}
		
		// Already visited neighbor vertex: We encountered a cycle node. 
		//Set cycle_start_node. Break DFS and start trace back.
		else
		{
			cycle_start_node = nbr_node;  // Consdier this nbr_node as the start of the cycle within the graph
			parent[nbr_node] = node;	// The nbr_node is encountered again, because it is in a cycle. Change the parent of this nbr_node to this new one. This will trace the cycle path
			
			// Immediate return 1. Cycle detected.
			return 1;
		}
	}
	
	return 0;	// return 0 if no cycle is found in this branch path
}



vector<int> findRedundantConnection(vector<vector<int>>& edges) 
{
	// Number of nodes in the graph = Number of edges in the graph , in the cyclic graph in question
	// Number of edges in a tree is always n-1
	int n = edges.size();	
	
	// Convert edges to adjacency list (nodes are 1-indexed, so we need n+1 size)
	vector<vector<int>> adj_list(n + 1);
	for (int i=0; i < edges.size(); i++)
	{
		adj_list[edges[i][0]].push_back(edges[i][1]);
		adj_list[edges[i][1]].push_back(edges[i][0]);  // Undirected graph - add both directions
	}
	
	// Index 0 is dummy because there is no node 0
	vector<int> parent(n + 1, -1);	// parent[] array: parent[i] = j, means the DFS call to the node-i was called from the node-j. Used to trace DFS path
	vector<int> visited(n + 1, 0);
	
	int src = 1;
	int cycle_start_node = -1;
	visited[src] = 1;
	dfs_helper(src, adj_list, visited, parent, cycle_start_node);	// DFS call from the source node. Get the value of cycle_start_node and parent[] array

	
	// Prepare a hash map for cycle nodes. All the nodes in the parent[] array are the cycle nodes
	vector<int> cycle_node_hash(n + 1, 0);	// cycle_node_hash[i] == 1, if the node 'i' is a cycle node
	
	// Prepare cycle_node_hash[]
	// Iterate all the nodes of the cycle starting from the cycle_start_node, till we reach the cycle_start_node again. Using parent[] map	
	// Mark all the nodes in the cycle in the cycle_node_hash[]
	int node = cycle_start_node;
	do
	{
		cycle_node_hash[node] = 1;
		node = parent[node];	// Update node
	} while (node != cycle_start_node);
	
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
