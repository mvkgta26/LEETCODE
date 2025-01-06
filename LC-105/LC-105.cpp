#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

using namespace std;

map<int,int> inorder_hash_func(vector<int>& inorder)
{
    map<int,int> inorder_hash;
    for (int i=0; i<inorder.size(); i++)
    {
        inorder_hash[inorder[i]] = i;
    }

    return inorder_hash;
}

// The function is a recursive function that takes the inorder and preorder of a tree,
// finds the head of the tree, builds left and right subtrees of the head, and attaches them to the head.
// Finally returns this head of the tree.
// in_start and in_end mark the boundaries (the start and end indices) within inorder[] for the current subtree in the resursive call
// Similarly pre_start and pre_end.
// Imagine as if you are passing only the preorder and inorder subarrays relevant to the subtree for the recursive call. But instead of passing the subarray itself, we pass the boundaries of the subarray within the original pre_order and in_order.
TreeNode* buildTreeHelper(vector<int>& preorder, int pre_start, int pre_end, vector<int>& inorder, int in_start, int in_end, map<int, int> &inorder_hash)
{
    // Exit Condition 1: If there is only one element in the preorder array for the current subtree, then it is a leaf node
    // Create the leaf node with the value of the only element in the preorder array.
    if(pre_start == pre_end)
    {
        TreeNode* node =  new TreeNode(preorder[pre_start]);
        return node;
    }

    // Exit Condition 2: If there is no left/right child node for the previous head node. Return NULL
    if (pre_start > pre_end)
    {
        return NULL;
    }
    // NOTE: You can do the same above 2 exit conditions check using in_start and in_end as well.
    


    // Create the head node of the current subtree: Take value of the first element of the preorder array of the current subtree
    TreeNode* head_node = new TreeNode(preorder[pre_start]);
    int left_subtree_length = inorder_hash[preorder[pre_start]] - in_start;    // pre_start marks the start of the preorder array pertaining to the current subtree in the recursive call. The first element in the preorder of the current subtree will be the head node.


    // TreeNode* left_subtree_head = NULL;
    // TreeNode* right_subtree_head = NULL;

          
    // Handle edges cases if there is only left subtree to the current head node (Asymmetry)
    // if ( in_start + left_subtree_length >= in_end)  // left subtree and the head node make up the whole inorder of the tree.
    // {   
    //     right_subtree_head = NULL;
    // }
    
    // Set boundaries for preorder and inorder arrays for the left subtree. Build the left subtree and get the left subtree head returned.
    TreeNode* left_subtree_head = buildTreeHelper(preorder, pre_start + 1, pre_start + left_subtree_length,  inorder, in_start, in_start + left_subtree_length - 1, inorder_hash);     

    // Set boundaries for preorder and inorder arrays for the right subtree. Build the right subtree and get the right subtree head returned.
    TreeNode* right_subtree_head = buildTreeHelper(preorder, pre_start + left_subtree_length + 1, pre_end, inorder, in_start + left_subtree_length + 1, in_end, inorder_hash);
      

    // Attach the left and right subtree heads to the current head node.
    head_node->left = left_subtree_head;
    head_node->right = right_subtree_head;

    return head_node;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
{

    map<int, int> inorder_hash = inorder_hash_func(inorder);

    // Make the call to the recursive helper function
    // Initially the boundaries of preorder and inorder are over the whole arrays, because the recrusive call is on the entire tree.
    TreeNode* root = buildTreeHelper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inorder_hash);

    return root;
}

int main()
{
    vector<int> preorder = {3,9,20,15,7};
    vector<int> inorder = {9,3,15,20,7};

    TreeNode* root = buildTree(preorder, inorder);
    return 0;
}