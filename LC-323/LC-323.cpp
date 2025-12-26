/*
	Algorithm:
		Iterate all the nodes of the graph
		Once you encounter the unvisited node i of a graph: 
			Peform a BFS with this vertex - i as source
			Once this BFS is completed, all the nodes in the connected component 'i' belongs will be marked as visited
		Continue iterating the nodes of the graph. 
			If you again encounter an unvisited vertex, that means it belongs to a new undiscovered connected component.
			Count this new connected component, and call BFS with this vertex as source to mark all the vertices in this connected component as visited
		Repeat this till all the nodes in the graph are iterated	
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs_helper(int source, vector<vector<int>>& adj_list, vector<int>& visited)
{
	queue<int> bfs_que;
	bfs_que.push(source);
	visited[source] = 1;
	
	while (!bfs_que.empty())
	{
		// Take out the element at the front of the bfs que
		int curr_node = bfs_que.front();
		bfs_que.pop();
		visited[curr_node] = 1; // Process
		
		// Iterate all the unvisited neighbors of the curr_node, and push to the bfs que
		for (int i=0; i < adj_list[curr_node].size(); i++)
		{
			int nbr_node = adj_list[curr_node][i];
			
			if ( visited[nbr_node] != 1 )
			{
				bfs_que.push(nbr_node);
			}
		}
	}
}


int countComponents(int n, vector<vector<int>>& edges) 
{
	vector<vector<int>> adj_list(n);
	
	// Build adj_list of the graph 
	for (int i=0; i<edges.size(); i++)
	{
		adj_list[edges[i][0]].push_back(edges[i][1]);
		adj_list[edges[i][1]].push_back(edges[i][0]);
	}
	
	// visited[] array: visited[i] == 1, if node i is already visited
	vector<int> visited(n, 0);
	
	int num_of_connected_components = 0;
	
	/// Make a BFS call with vertex 0 as source
	bfs_helper(0, adj_list, visited);
	num_of_connected_components++;

	
	// Iterate the visited[] array, make BFS calls with unvisited vertices as source
	// Each unvisited vertex represents a new connected component
	for (int i=0; i < n; i++)
	{
		// If you encounter an unvisited vertex, you encountered a new connected component. Count this.
		// Make BFS call with that vertex as source
		if ( visited[i] == 0 )
		{
			num_of_connected_components++;
			bfs_helper(i, adj_list, visited);
		}
	} 
	
	
	return num_of_connected_components;
}