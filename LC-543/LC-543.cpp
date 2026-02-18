/*

Diameter of current node = max(depth of left subtree, depth of right subtree) + 1
Diameter of the tree = Max diameter among the diameter of all the nodes in the tree

Recursion:		
	Use recursion to calculate max_depth of each node. Have a reference variable diameter that is updated throughout the recurison		
*/


#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// Function returns the maximum depth from the node *root
int max_depth(TreeNode* root, int& diameter)
{
	// Base Condition
	if (root == NULL)
	{
		return 0;	// Return length of 0
	}
	
	int max_depth_of_left_child = max_depth(root->left, diameter);
	int max_depth_of_right_child = max_depth(root->right, diameter);
	
	// Update the largest diameter through all the nodes so far
	int diameter_through_root = max_depth_of_left_child + max_depth_of_right_child;
	if (diameter_through_root > diameter)
	{
		diameter = diameter_through_root;
	}

	int curr_node_depth = max(max_depth_of_left_child, max_depth_of_right_child) + 1; // +1 to account for the edge going from the left/right subtree to the current node	
	return curr_node_depth;	
}


int diameterOfBinaryTree(TreeNode* root) 
{
	int diameter = -1; 
	max_depth(root, diameter);
	
	return diameter;
}