#include <vector>



using namespace std;

//Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// ** Note that the depth in this problem is actually height **
int find_depth(TreeNode* root, int& balanced)
{
	// Base condition
	if (root == NULL)
		return -1;
	
	int left_subtree_depth = find_depth(root->left, balanced);
	int right_subtree_depth = find_depth(root->right, balanced);
	
	// Check if the current subtree with the root-node root , is balanced. If not, set flag to 0
	if ( abs( left_subtree_depth - right_subtree_depth ) > 1 )	
		balanced = 0;
	
	else
		balanced = balanced * 1; 	// Do nothing	
	
	int depth_of_curr_node = max(left_subtree_depth, right_subtree_depth) + 1; 
	return depth_of_curr_node;	// Depth calculation. Return the depth of the current node
}


bool isBalanced(TreeNode* root) 
{
	int out = 1;
	find_depth(root, out);

	return out;
}