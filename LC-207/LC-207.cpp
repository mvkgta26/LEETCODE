/*
	Steps:
		0. We are representing each course as a node in the directed graph. Each edge represents a prerequisite. 
			If course A has course B as prereq, then there is a directed edge from course B to course A. 
		1. Convert and obtain the graph adjacency list from the prerequisites[] array
		2. Calculate the indegree[] for each of the courses / each of the nodes in the graph.
			(Indegree[i]: The number of in-edges going into node i)
		3. Perform cycle detection algorithm, if no cycles: return 1, otherwise return 0

	Is it possible to complete all the courses with the given prerequisite order?
		Yes, If there are no cycles in the graph.
		If there is a cycle, that means there is a circular dependency, which means there is no valid order in which to complete the courses.
			(Ex: A needs B to complete, but B also needs A to complete)

	Background:
		>> Topological sort: Topological sort is a linear ordering of the vertices of a directed acyclic graph such that for every directed edge u→v,
		 	u comes before v in the ordering.
		>> A graph can have a valid topological sort only if there is no cycle. If there is a cycle, a topological sort is not possible.
	
	Topological sort creation algorithm (Kahn's Algorithm): To get the topological sort of a DAG graph of n vertices:
				Iteratively remove one node that has indegree as 0, and add to the topological sort array.
					Update the indegree of all the out-neigboring vertices of this vertex, considering this vertex has been removed.
				Keep doing this till all n vertices are addded to the topological sort array
						[No proof]
					
	Cycle Detection: If at any stage in the topological sort algorithm, 
					 there are still vertices remaining that are NOT added to the topological sort array, 
					 but none of them have 0 indegree, that means there is a cycle in the graph.  
						[No proof]
					
*/


#include <vector>

using namespace std;

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
{
	// Create adjacency list. Total numCourses number of nodes in the graph
	vector<vector<int>> adj_list(numCourses);
	
	// Build graph adjacency list from the prerequisites[] array
	for (int i=0; i < prerequisites.size(); i++)
	{
		int from_node = prerequisites[i][1];
		int to_node = prerequisites[i][0];
		
		adj_list[from_node].push_back(to_node);
	}
	
	
	// Topological sort detection
	vector<int> indegree(numCourses);	// indegree[i] = Number of edges going into the node i
	
	// Initialize indegree:
	// Traverse all edges in the graph. Count it for the indegree of the out-node of the edge.
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
	
	
	// Add courses one by one, to the top_sorted[] array, till all the courses in the graph are added
	int num_courses_added = 0;
	while (num_courses_added < numCourses)
	{
		int cyclic_flag = 1;
		
		// Iterate all the nodes/courses in the graph, find a node with indegree == 0
		for (int j=0; j < numCourses; j++)
		{
			if(indegree[j] == 0)	// Node 'j' is chosen next in the topological sort
			{
				indegree[j] = -1;	// Mark node j as already added in the topological sort array
				cyclic_flag = 0;
				top_sorted.push_back(j);
				
				// Iterate all the outneighbors of the current chosen node 'j'
				// Update the indegree of all the out-neighbors of node 'j', assuming that node j is removed
				for (int k=0; k < adj_list[j].size(); k++)
				{
					int out_node_from_j = adj_list[j][k];
					indegree[out_node_from_j]--;
				}
				
				break;	// The next vertex in the topological sort is already found, move to the next vertex after this
			}
		}
		
		// No vertex with indegree 0 is found, cycle detected
		if (cyclic_flag == 1)
			return 0;
			
		num_courses_added++;
	}
	
	return 1;
}

int main()
{
	
}