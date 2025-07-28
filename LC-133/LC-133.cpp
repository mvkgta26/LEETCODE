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

Node* cloneGraph(Node* node) 
{
	// Create bfs queue and push the node 1 to que front. Also create visited array.
	queue<Node*> bfs_que;
	bfs_que.push(node);
	vector<int> visited(100, 0);	// There are maximum 100 unique nodes in the graph, based on the question specifications
	map<int, Node*> copy_node_hash;	// Hash table that hashes the value of each clone node to its address
	
	// Create the head node 1 of the clone graph. Hash its value to its address.
	Node* clone_graph_head_node = new Node(node->val);
	copy_node_hash[clone_graph_head_node->val] = clone_graph_head_node;
	
	
	// BFS
	Node* curr_node;
	vector<Node*> curr_neighbors;
	while  (!bfs_que.empty())
	{
		// Pop Que Front
		curr_node = bfs_que.front();
		bfs_que.pop();
		visited[curr_node->val] = 1;	// Mark current node as visited
		
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
				
				// Create clone of the neighbor node. Hash the clone neighbor node.
				copy_nbr_node = new Node(curr_neighbors[i]->val);
				nbrs_arr_clone.push_back(copy_nbr_node);
			}
			
			// If neighbor is already visited, take its address from the hash table
			else
			{
				copy_nbr_node = copy_node_hash[curr_neighbors[i]->val];
			}
			
			// Add the neighbor to the clone node neighbors list, irrespective of if it is already visited.
			nbrs_arr_clone.push_back(copy_nbr_node);
		}
		
		copy_node->neighbors = nbrs_arr_clone;	// Attach the clone neighbors to the clone node
	}
	
	
	return clone_graph_head_node;
}