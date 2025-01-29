#include <stdio.h>
#include <iostream>

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


int find_max_depth(TreeNode* root, int check_depth_flag)
{
    // Recurrence relation:
        // The max_depth of a root {r = max [ max_depth(root->left), max_depth(root->right) ] + 1}

    
    // Exit condition
    if (root == NULL)
        return -1;
    
    int max_depth = max( find_max_depth(root->left), find_max_depth(root->right) ) + 1;


    if (max_depth)

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
                    
}