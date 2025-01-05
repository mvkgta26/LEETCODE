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

TreeNode* buildTreeHelper(vector<int>& preorder, vector<int>& inorder, map<int, int> &inorder_hash)
{
    // Exit Condition 1:
    if(preorder.size() == 1)
    {
        TreeNode* node =  new TreeNode(preorder[0]);
        node->left = NULL;
        node->right = NULL;
        return node;
    }


    int head_node_val = preorder[0];
    TreeNode* head_node = new TreeNode(head_node_val);


    int left_subtree_length = inorder_hash[head_node_val];


    TreeNode* left_subtree_head = NULL;
    TreeNode* right_subtree_head = NULL;

    if (left_subtree_length == 0)  // Handle edges cases if there is only right subtree to the current head node (Asymmetry)
    {
        left_subtree_head = NULL;
    }    
    
    else
    {    // Create preorder and inorder arrays for the left subtree. Build the left subtree and get the left subtree head.
        vector<int> left_subtree_inorder (inorder.begin(), inorder.begin() + left_subtree_length);
        vector<int> left_subtree_preorder (preorder.begin() + 1, preorder.begin() + left_subtree_length + 1);
        left_subtree_head = buildTree(left_subtree_preorder, left_subtree_inorder);
    }  

    // Handle edges cases if there is only left subtree to the current head node (Asymmetry)
    if (left_subtree_length + 1 >= inorder.size())  // left subtree and the head node make up the whole inorder of the tree.
    {   
        right_subtree_head = NULL;
    }
    
    else
    {    
        // Create the preorder and inorder arrays for the right subtree. Build the right subtree and get the right subtree head.
        vector<int> right_subtree_inorder (inorder.begin() + left_subtree_length + 1, inorder.end());   // Middle/head_node + 1 --> right end 
        vector<int> right_subtree_preorder (preorder.begin() + left_subtree_length + 1, preorder.end());    // The right subtree section
        right_subtree_head = buildTree(right_subtree_preorder, right_subtree_inorder);
    }  

    // Attach the left and right subtree heads to the current head node.
    head_node->left = left_subtree_head;
    head_node->right = right_subtree_head;

    return head_node;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
{

    map<int, int> inorder_hash = inorder_hash_func(inorder);

    TreeNode* root = buildTreeHelper(preorder, inorder, inorder_hash);

    return root;
}

int main()
{
    vector<int> preorder = {3,9,20,15,7};
    vector<int> inorder = {9,3,15,20,7};

    TreeNode* root = buildTree(preorder, inorder);
    return 0;
}