/*
	Ancestor definition: In a binary tree with root node r, The node u is an ancestor of node v, if there is a 'simple path' from r to v through u
							( Simple path intuition: You don't visit the same node twice in the path )

	Algorithm:
		Recursively iterate through the nodes in BST, starting from root node, and check if each node is the LCA.
		At each node, evaluate:
			Case-1: Both p and q lie on the left subtree of current node (Both p and q values are smaller than curr node). LCA surely lies in the left subtree, check if left child is the LCA. Do DFS(node->left). 
			Case-2: Both p and q lie on the right subtree of current node (Both p and q values are larger than curr node). LCA surely lies in the right subtree, check if right child is the LCA. Do DFS(node->right).
			Case-3: p and q lie on each side subtrees of current node (curr_node value is in between p and q values) : This means current node is the LCA. Return this node.


	Pretty intuitive, not doing rigorous proof of correctness
*/


#include <vector>
#include <algorithm>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

using namespace std;


TreeNode* dfs_helper(TreeNode* node, int low_val, int high_val)
{	
	int curr_val = node->val;
	
	// If the curent node->val lies between the low_val and the high_val, that means the current node is the LCA.
	// Note corner case: p or q could be same as current node
	if ( low_val <= curr_val && high_val >= curr_val )
	{
		return node;
	}
	
	// If both the low_val and high_val lie on the left subtree of node
	else if ( low_val <=  curr_val && high_val <= curr_val )
	{
		// Recursive Call dfs on the left subtree
		return dfs_helper(node->left, low_val, high_val);
	}
	
	// If both the low_val and high_val lie on the right subtree of node
	else if (low_val >= curr_val && high_val >= curr_val )
	{
		// Recursive Call dfs on the right subtree
		return dfs_helper(node->right, low_val, high_val);
	}
	
	return NULL;	// dummy return
}


TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
	TreeNode* output = dfs_helper(root, min(p->val, q->val), max(p->val, q->val));
	
	return output;
}