#include <algorithm>

/* 
	Because trees are acyclic, there can be only one path from the root node to any other node
	Perform DFS:
		When making a DFS call to a node 'x', pass to it the maximum value among all the nodes in the path from the root to that node 'x' 
*/


using namespace std;

int good_node_count = 0;

struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// path_max is the maximum number in the path taken from the root ---> curr_node, excluding curr_node
void dfs_helper(TreeNode* curr_node, int path_max)
{
	// DFS Exit Condition
	if (curr_node == NULL)
		return;
	
	// If the value of the current node is greater/equal than all the values in the path from root ---> curr_node, the curr_node IS A GOOD NODE
	if (curr_node->val >= path_max)
	{
		good_node_count++;
	}
	
	int curr_max = max(path_max, curr_node->val);	// The maximum number in the path from root--> curr_node, INCLUDING curr_node. Pass this to the left and right children
	
	// Make recursive DFS call to the left and right branch of the curr_node, with the curr_max as input
	dfs_helper(curr_node->left, curr_max);
	dfs_helper(curr_node->right, curr_max);
}



int goodNodes(TreeNode* root) 
{    
	good_node_count = 0;  // Reset global variable good_node_count, so that it does not accumulate between multiple leetcode test cases

	dfs_helper(root, INT_MIN);

	return good_node_count;
}