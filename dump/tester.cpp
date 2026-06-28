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


// Flattens the tree with root == node and attach it to the tail node
void helper(TreeNode* node, TreeNode* &tail)
{
	// Exit condition
	if (node == nullptr)
	{
		return;
	}
	
	// Attach tail to node
	tail->left = nullptr;
	tail->right = node;
	tail = tail->right;		// Update tail
	
	// Store the address of the left node and the right node to the current node in the stack frame. This is because the actual left and right nodes will be changed in place in the actual node
	TreeNode* tree_left = node->left;
	TreeNode* tree_right = node->right;
	
	// Recursively flatten left subtree and attach to the tail of the linked list
	helper(tree_left, tail);
	
	// Recursively flatten right subtree and attach to the tail of the linked list
	helper(tree_right, tail);
}


void flatten(TreeNode* root) 
{
	TreeNode* dummy_head = new TreeNode(0, nullptr, root);
	TreeNode* tail = dummy_head;
	
	helper(root, tail);
	
	tail->right = nullptr;
	delete dummy_head;
}