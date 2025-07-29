/*
	Essential Data Structure:
		Maintain a hash table that maps each node value to the address of the clone-node with that value.

	Algorithm:
		Perform BFS on the nodes of the graph
			When processing each node of the graph:
				Obtain the clone of that node from the hash table
				Iterate all the neighbors of each node:
					If neighbor already visited, take the neighbor's clone-node from the hash
					If neighbor is not already visited: create a new clone-node of the neighbor, add a new hash entry for this neighbor clone-node 
				Add the clones of all the neighbors of the current node to a list and Attach it to the current clone node
				
	Proof:
		You can use loop invariant to understand. A rough understanding should be enough, mostly you can just understand intuitively.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class Node {
public:
	int val;
	vector<Node*> neighbors;
	Node() {
		val = 0;
		neighbors = vector<Node*>();
	}
	Node(int _val) {
		val = _val;
		neighbors = vector<Node*>();
	}
	Node(int _val, vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};



// 
Node* cloneGraph(Node* node) 
{
	// Corner Case. There ain't no graph.
	if (node == NULL)
	{
		return NULL;
	}
	
	// Create bfs queue and push the node 1 to que front. Also create visited array.
	queue<Node*> bfs_que;
	bfs_que.push(node);
	vector<int> visited(101, 0);	// There are maximum 101 unique nodes in the graph, from 0-100, based on the question specifications
	map<int, Node*> copy_node_hash;	// Hash table that hashes the value of each clone node to its address
	
	// Create the head node 1 of the clone graph. Hash its value to its address.
	Node* clone_graph_head_node = new Node(node->val);
	copy_node_hash[clone_graph_head_node->val] = clone_graph_head_node;
	
	visited[node->val] = 1; // Mark the head node as visited
	
	// BFS
	Node* curr_node;
	vector<Node*> curr_neighbors;
	while  (!bfs_que.empty())
	{
		// Pop Que Front
		curr_node = bfs_que.front();
		bfs_que.pop();
		
		// Get the address of the copy node corresponding to this node value 
		Node* copy_node = copy_node_hash[curr_node->val];
	
		// BFS Neighbor Iteration: Iterate the neighbors of the current node and push them to the que
			// In parallel: Create clones of the neighbors of the current node, and attach them to the current node
		curr_neighbors = curr_node->neighbors;
		Node* copy_nbr_node;
		vector<Node*> nbrs_arr_clone;	// Array for storing the clones of the neighbors of the current node
		for (int i=0; i < curr_neighbors.size(); i++)
		{
			//If neighbor is not already visited
			if (visited[curr_neighbors[i]->val] == 0)	
			{
				bfs_que.push(curr_neighbors[i]);
				visited[curr_neighbors[i]->val] = 1;	// Mark current neighbor node as visited
				
				// If unvisited neighbor, Create clone of the neighbor node. Hash the clone neighbor node.
				copy_nbr_node = new Node(curr_neighbors[i]->val);
				copy_node_hash[copy_nbr_node->val] = copy_nbr_node;	// Hash
			}
			
			// Take the neighbor's address from the hash table
			copy_nbr_node = copy_node_hash[curr_neighbors[i]->val];
			
			// Add the neighbor to the copy-node's neighbors list, irrespective of if it is already visited.
			nbrs_arr_clone.push_back(copy_nbr_node);
		}
		
		copy_node->neighbors = nbrs_arr_clone;	// Attach the clone neighbors to the clone node
		nbrs_arr_clone.clear(); // Clear the neighbors array for the iteration of the next node
	}
	
	
	return clone_graph_head_node;
}