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

map<int,int> preorder_hash_func(vector<int>& preorder)
{
    map<int,int> preorder_hash;
    for (int i=0; i<preorder.size(); i++)
    {
        preorder_hash[preorder[i]] = i;
    }

    return preorder_hash;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
{
    // Exit Condition 1:
    if (preorder.size() == 0)
    {
        return nullptr;
    }

    // Exit Condition 2:
    if(preorder.size() == 1)
    {
        TreeNode* node =  new TreeNode(preorder[0]);
        return node;
    }

    int head_node_val = preorder[0];
    TreeNode head_node = TreeNode(head_node_val);

    map<int, int> inorder_hash = inorder_hash_func(inorder);
    //map<int, int> preorder_hash = preorder_hash_func(preorder);

    int left_subtree_length = inorder_hash[head_node_val];

    // Create preorder and inorder arrays for the left subtree. Build the left subtree and get the left subtree head.
    vector<int> left_subtree_inorder (inorder.begin(), inorder.begin() + left_subtree_length);
    vector<int> left_subtree_preorder (preorder.begin() + 1, preorder.begin() + left_subtree_length);
    TreeNode* left_subtree_head = buildTree(left_subtree_preorder, left_subtree_inorder);
    
    // Create the preorder and inorder arrays for the right subtree. Build the right subtree and get the right subtree head.
    vector<int> right_subtree_inorder (inorder.begin() + left_subtree_length + 1, inorder.end());   // Middle/head_node + 1 --> right end 
    vector<int> right_subtree_preorder (preorder.begin() + left_subtree_length + 1, preorder.end());    // The right subtree section
    TreeNode* right_subtree_head = buildTree(right_subtree_preorder, right_subtree_inorder);

    // Attacht the left and right subtree heads to the current head node.
    head_node.left = left_subtree_head;
    head_node.right = right_subtree_head;

    return &head_node;
}


int main()
{
    cout << "Hello";
    return 0;
}