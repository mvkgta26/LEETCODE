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


bool sameTreeHelper(TreeNode* p, TreeNode* q)
{
    // Exit Condition: If we have reached the leaf nodes in both the trees
    if (p == NULL && q == NULL)
    {
        return 1;
    }

    // Edge Case: Both the nodes are not NULL, but is just 1 of the nodes NULL ??
    // Have we reached the leaf of one tree but not the other
    else if ( p==NULL || q==NULL )      //else if ( (p == NULL && q != NULL) || (p != NULL && q == NULL) )
    {
        return 0;
    }

    // If both the nodes have the same values, recursively check if the left and right subtrees of the current nodes are equal
    if (p->val == q->val)
    {
        return ( sameTreeHelper(p->left, q->left) && sameTreeHelper(p->right, q->right) );
    }

    else
    {
        return 0;
    }
}


bool isSameTree(TreeNode* p, TreeNode* q) 
{
    return sameTreeHelper(p, q);  
}