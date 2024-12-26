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


TreeNode* invertTree(TreeNode* root) 
{
    TreeNode* node = root;


    // Exit Condition
    if (node == NULL)
        return NULL;


    invertTree(node->left);    //Recursive call on the left subtree
    invertTree(node->right);   //Recursive call on the right subtree


    // Swap the left and right child nodes of the current node
    TreeNode* temp;
    temp = node->left;
    node->left = node->right;
    node->right = temp;

    return node;
}

int main()
{
    cout << "Hello World" << endl;
    return 0;
}