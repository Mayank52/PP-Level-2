#include <iostream>
#include <vector>
#include <limits.h>
#include <unordered_map>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Diagonal Traversal of Binary Tree (https://practice.geeksforgeeks.org/problems/diagonal-traversal-of-binary-tree/1#)
/*
On GFG, the diagonal order is taken in DFS form, not in level order.
So, BFS gives the correct elements in a diagonal but in wrong order.

The DFS Solution passes in C++. But in java gets a TLE.
*/
int leftMin = INT_MAX;
int rightMax = INT_MIN;
void diagonal(Node *node, int lvl, unordered_map<int, vector<int>> &mp)
{
    if (node == nullptr)
        return;

    leftMin = min(leftMin, lvl);
    rightMax = max(rightMax, lvl);

    mp[lvl].push_back(node->data);

    diagonal(node->left, lvl - 1, mp);
    diagonal(node->right, lvl + 0, mp);
}
vector<int> diagonal(Node *root)
{
    // your code here
    unordered_map<int, vector<int>> mp;

    diagonal(root, 0, mp);

    vector<int> res;
    for (int i = rightMax; i >= leftMin; i--)
    {
        for (int val : mp[i])
        {
            res.push_back(val);
        }
    }

    return res;
}

// 968. Binary Tree Cameras
int cameras = 0;
int minCameraCover_(TreeNode *root)
{
    if (root == nullptr)
        return 2;

    int leftAns = minCameraCover_(root->left);
    int rightAns = minCameraCover_(root->right);

    if (leftAns == 0 || rightAns == 0) //has a leaf node as child -> place camera
    {
        cameras++;
        return 1;
    }
    else if (leftAns == 1 || rightAns == 1) //I am parent of a leaf node
        return 2;
    else //My children have no affect on meF
        return 0;
}
int minCameraCover(TreeNode *root)
{
    int rootAns = minCameraCover_(root);
    if (rootAns == 0) //root is leaf or is not affected by its children -> place camera on root
        cameras++;

    return cameras;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}