#include <queue>
#include <vector>


using namespace std;

//Definition for a binary tree node.
struct TreeNode 
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};



vector<vector<int>> levelOrder(TreeNode* root) 
{
	
	if (root == NULL)
		return {};
	
	vector<vector<int>> output;
	
	queue<TreeNode*> bfs_q;
	bfs_q.push(root);
	
	while ( !bfs_q.empty() )
	{
		int q_size = bfs_q.size();	// Number of element in the BFS que
		vector<int> curr_level;		// Will hold all the node values in the current level
		
		
		// Iterate all the nodes in the bfs que at THIS LEVEL
		for (int i=0; i < q_size; i++)
		{	
			TreeNode* curr_node = bfs_q.front();	
			bfs_q.pop();
			curr_level.push_back(curr_node->val);
		
			TreeNode* left_child = curr_node->left;
			TreeNode* right_child = curr_node->right;
			
			if (left_child != NULL)
			{
				bfs_q.push(left_child);	
			}
			
			if (right_child != NULL)
			{
				bfs_q.push(right_child);	
			}
			
		}
		
		output.push_back(curr_level);
	}
	
	return output;
}