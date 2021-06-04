#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
};

// Diagonal Traversal of Binary Tree (https://practice.geeksforgeeks.org/problems/diagonal-traversal-of-binary-tree/1#)
/*
On GFG, the diagonal order is taken in DFS form, not in level order.
So, BFS gives the correct elements in a diagonal but in wrong order.

The DFS Solution passes in C++. But in java gets a TLE.
*/
int leftMin = INT_MAX;
int rightMax = INT_MIN;
void diagonal(Node *node, int lvl, map<int, vector<int>> &mp)
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
    map<int, vector<int>> mp;

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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}