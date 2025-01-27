#include <iostream>
#include <stdio.h>


using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


bool recursionHelper(TreeNode* p, TreeNode* q)
{
    // If we have reached the lead nodes in both the trees
    if (p == NULL && q == NULL)
    {
        return 1;
    }

    else if ( (p == NULL && q != NULL) || (p != NULL && q == NULL) )
    {
        return 0;
    }

    if (p->val == q->val)
    {   
        // Check if the left subtrees of both the tree nodes are equal
        // if (recursionHelper(p->left, q->left))
        // {
        //     // Check if right subtree of the both the tree nodes are equal
        //     if (recursionHelper(p->right, q->right))
        //     {
        //         return 1;
        //     }
        // }

        // else 
        // {
        //     return 0;
        // }


        return ( recursionHelper(p->left, q->left) && recursionHelper(p->right, q->right) );
    }

    else
    {
        return 0;
    }
}

bool isSameTree(TreeNode* p, TreeNode* q) 
{

        
}