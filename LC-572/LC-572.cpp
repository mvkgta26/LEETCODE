#include <stdio.h>
#include <iostream>
#include <vector>


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

vector<TreeNode*> all_subtree_roots_with_same_depth;

int find_max_depth(TreeNode* root, int check_depth)
{


    // Recurrence relation:
        // The max_depth of a root {r = max [ max_depth(root->left), max_depth(root->right) ] + 1}
    
    // Exit condition
    if (root == NULL)
        return -1;
    
    int max_depth = max( find_max_depth(root->left, check_depth), find_max_depth(root->right, check_depth) ) + 1;

    // The current root TreeNode* has the same max_depth as the subtree subroot
    // There is a chance that this subtree from this root could be the same as the subtree subroot
    // Add this to a vector to be compared later on
    if (max_depth == check_depth)
    {
        all_subtree_roots_with_same_depth.push_back(root);
    }

    return max_depth;
}

bool same_tree_helper(TreeNode* a, TreeNode* b)
{
    if ( a==NULL && b==NULL )
    {
        return 1;
    }

    else if ( a==NULL || b==NULL )
    {
        return 0;
    }

    if (a->val == b->val)
    {
        return ( same_tree_helper(a->left, b->left) && same_tree_helper(a->right, b->right) );
    }

    else
    {
        return 0;
    }

}


bool isSubtree(TreeNode* root, TreeNode* subRoot) 
{

    int subRootDepth = find_max_depth(subRoot, -1);     // give check_depth a dummy value of -1, there is no need to check to check for subtree with given depth when finding the depth of the subtree

    int mainTreedDepth = find_max_depth(root, subRootDepth);    // Recursively checks and stores all the subtrees in root tree that have the depth = subRootDepth

    for (int i=0; i<all_subtree_roots_with_same_depth.size(); i++)
    {
        TreeNode* node_to_be_checked = all_subtree_roots_with_same_depth[i];
        
        if ( same_tree_helper( node_to_be_checked, subRoot ) )
        {
            return 1;
        }
    }

    // All the nodes in the main tree with same depth as the subRoot subtree have been checked. No match found.
    return 0;

}