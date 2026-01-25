/*
	In-Order Traversal: L-C-R
	Keep count of the number of nodes you iterated so far.
	If it reaches k, return the node value
*/

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


int count_nodes = 0;	// Global variable to keep track of the number of integers traversed so far 

void inorder_dfs(TreeNode* node, int& k, int& out)`
{
	if (node == nullptr)
		return;
		
	// Prevent unnecessary extra traversals
	if (count_nodes > k)
		return;
	
	inorder_dfs(node->left, k, out);
	
	node->val;	// Curr node. Just for representation. This line does nothing.
	
	count_nodes++;
	if (count_nodes == k)
	{
		out = node->val;
		return;
	}
	
	inorder_dfs(node->right, k, out);

	return;
}


int kthSmallest(TreeNode* root, int k) 
{
	count_nodes = 0;		// Reset global variable to prepre for test cases
	int out = 0;
	inorder_dfs(root, k, out);
	
	return out;
}


void main()
{

}