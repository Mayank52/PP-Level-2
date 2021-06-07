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
/*
Approach: O(n)

We can have 3 kinds of nodes:
1. Leaf Node -> 0
2. Parent of Leaf Node -> 1
3. Every Other node which does not have a camera but is observed by some other camera -> 2

We never place a camera on leaf. Because placing a camera on parent of leaf is always better as we parent can cover more nodes.
So, always place a camera on parent of leaf.

So, if the child returns:
0-> they are leaf, so I am parent, place a camera here
1-> they are parent of leaf, so they have a camera, which , means I am already covered by my child.
2-> My child does not have a camera, but is covered by another camera.


So, apart from leaf nodes and their parents, for all other nodes, 
if both their children are already covered by another camera(returns 2)
Then this node does not have any effect on its children and the children have no effect on this node.
So, This node can be treated as a leaf node. So, it returns 0.

One Edge case is if root is a leaf, or being treated as a leaf. That can be checked in the main function call.
*/
int cameras = 0;
int minCameraCover_(TreeNode *root)
{
    //have no affect on my parent
    if (root == nullptr)
        return 2;

    int leftAns = minCameraCover_(root->left);
    int rightAns = minCameraCover_(root->right);

    //has a leaf node as child -> place camera
    if (leftAns == 0 || rightAns == 0)
    {
        cameras++;
        return 1;
    }
    //I am parent of a leaf node
    else if (leftAns == 1 || rightAns == 1)
        return 2;
    //My children have no affect on me
    else
        return 0;
}
int minCameraCover(TreeNode *root)
{
    int rootAns = minCameraCover_(root);

    //root is leaf or is not affected by its children -> place camera on root
    if (rootAns == 0)
        cameras++;

    return cameras;
}

// 124. Binary Tree Maximum Path Sum
int res = INT_MIN;
int maxPathSum_(TreeNode *root)
{
    if (root == nullptr)
        return 0;

    int leftAns = maxPathSum_(root->left);
    int rightAns = maxPathSum_(root->right);

    int smallAns = max(leftAns, rightAns) + root->val;

    res = max(max(res, smallAns), max(root->val, leftAns + rightAns + root->val));

    return max(smallAns, root->val);
}
int maxPathSum(TreeNode *root)
{
    res = INT_MIN;

    maxPathSum_(root);

    return res;
}

// 99. Recover Binary Search Tree
TreeNode *a, *b, *prev;

void recoverTree_(TreeNode *root)
{
    if (root == nullptr)
        return;

    recoverTree_(root->left);

    if (prev != nullptr && root->val < prev->val)
    {
        if (a == nullptr)
            a = prev;
        b = root;
    }

    prev = root;

    recoverTree_(root->right);
}
void recoverTree(TreeNode *root)
{
    recoverTree_(root);

    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}