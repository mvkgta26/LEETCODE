#include <iostream>
#include <stack>
#include <climits>
#include <vector>
#include <algorithm>
#include <unordered_map>

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


// Idea: // Process nodes in the RLC order (Reverse preorder). Process in reverse preorder will give just the reverse sequence of preorder traversal.
		// Start building from tail and build towards the head 		
		// Process in reverse preorder so that the left and right of each node is not overwritten before they are used 
// node is the current node to be processed
// Prev will always hold the last/most-recently processed node
// Attach node to prev
void helper(TreeNode* node, TreeNode* &prev)
{
	if (node == nullptr)
	{
		return;
	}
	
	// Recursive call on right and left nodes
	helper(node->right, prev);
	helper(node->left, prev);
	
	// Process: Attach current node to the prev node
	node->right = prev;
	node->left = nullptr;
	prev = node;	// Update prev to current node
}

void flatten(TreeNode* root) 
{
	TreeNode* prev = nullptr;
	helper(root, prev);
}



// ***** My own version: Not that elegant, invloves just preorder traversal ****
// Flattens the tree with root == node and attach it to the tail node
// void helper(TreeNode* node, TreeNode* &tail)
// {
// 	// Exit condition
// 	if (node == nullptr)
// 	{
// 		return;
// 	}
	
// 	// Attach tail to node
// 	tail->left = nullptr;
// 	tail->right = node;
// 	tail = tail->right;		// Update tail
	
// 	// Store the address of the left node and the right node to the current node in the stack frame. This is because the actual left and right nodes will be changed in place in the actual node
// 	TreeNode* tree_left = node->left;
// 	TreeNode* tree_right = node->right;
	
// 	// Recursively flatten left subtree and attach to the tail of the linked list
// 	helper(tree_left, tail);
	
// 	// Recursively flatten right subtree and attach to the tail of the linked list
// 	helper(tree_right, tail);
// }

