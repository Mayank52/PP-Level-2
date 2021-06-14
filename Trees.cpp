#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <math.h>
#include <list>
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

// 448 · Inorder Successor in BST
TreeNode *succ = nullptr, *prev = nullptr;
void inorderSuccessor_(TreeNode *root, TreeNode *p)
{
    if (root == nullptr)
        return;

    inorderSuccessor_(root->left, p);

    if (prev == p)
    {
        succ = root;
    }

    prev = root;

    inorderSuccessor_(root->right, p);
}
TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
{
    // write your code here
    inorderSuccessor_(root, p);

    return succ;
}

// 222. Count Complete Tree Nodes
/*
Approach : O(h*2h)
*/
int getLeftHeight(TreeNode *root)
{
    int count = 1;
    while (root->left != nullptr)
    {
        root = root->left;
        count++;
    }

    return count;
}
int getRightHeight(TreeNode *root)
{
    int count = 1;
    while (root->right != nullptr)
    {
        root = root->right;
        count++;
    }

    return count;
}
int countNodes(TreeNode *root) //O(h)
{
    if (root == nullptr)
        return 0;

    int lh = getLeftHeight(root);  //O(h)
    int rh = getRightHeight(root); //O(h)

    if (lh == rh)
        return (1 << lh) - 1;

    return countNodes(root->left) + countNodes(root->right) + 1;
}

// 900 · Closest Binary Search Tree Value
/*
Approach: O(h)
Use the find target in BST approach.
At each node check its absolute difference with target, and update the closest node.
*/
int closestValue(TreeNode *root, double target)
{
    // write your code here
    TreeNode *curr = root;
    int closestVal = -1;

    while (curr != nullptr)
    {
        //for each node check the absolute difference and update the closest node
        if (abs(target - curr->val) < abs(target - closestVal))
            closestVal = curr->val;

        if (target < curr->val)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    return closestVal;
}

// 901 · Closest Binary Search Tree Value II
/*
Approach 1: O(nlogk), O(k)
Using Priority Queue 
Keep {abs diff, node val} in priority queue of size k
Go to all nodes and update the pq

Approach 2: O(n), O(k)
Use a Sliding window of size k
Keep a queue of size of K
Move in inorder
For each element if its absolute difference is less than front of queue, then pop the front, and add this element to last
If current element cant beat the front element then, no element after it can do so either as we are moving in increasing order.

Approach 3:
For balanced BST,we can get less than O(n)
*/

int leftCount = 0, rightCount = 0;
//Approach 1:
void closestKValues(TreeNode *root, double target, int k, priority_queue<vector<double>, vector<vector<double>>> &pq)
{
    if (root == nullptr)
        return;

    closestKValues(root->left, target, k, pq);

    if (root->val > target)
        rightCount++;

    if (rightCount == k)
        return;

    if (pq.size() < k)
    {
        pq.push({abs(target - root->val), (double)root->val});
    }
    else
    {
        vector<double> top = pq.top();
        if (abs(target - root->val) < top[0])
        {
            pq.pop();
            pq.push({abs(target - root->val), (double)root->val});
        }
    }

    closestKValues(root->right, target, k, pq);
}
vector<int> closestKValues(TreeNode *root, double target, int k)
{
    priority_queue<vector<double>, vector<vector<double>>> pq;

    closestKValues(root, target, k, pq);

    vector<int> res;
    while (pq.size() != 0)
    {
        vector<double> rVal = pq.top();
        pq.pop();
        res.push_back((int)rVal[1]);
    }

    return res;
}
//Approach 2:
void closestKValues(TreeNode *root, double target, int k, list<int> &res)
{
    if (root == nullptr)
        return;

    closestKValues(root->left, target, k, res);

    if (res.size() < k)
    {
        res.push_back(root->val);
    }
    else
    {
        if (abs(target - root->val) < abs(target - res.front()))
        {
            res.pop_front();
            res.push_back(root->val);
        }
        else
            return;
    }

    closestKValues(root->right, target, k, res);
}
vector<int> closestKValues(TreeNode *root, double target, int k)
{
    list<int> window;

    closestKValues(root, target, k, window);

    vector<int> res;
    while (window.size() != 0)
    {
        int rVal = window.front();
        window.pop_front();
        res.push_back(rVal);
    }

    return res;
}

// https://codeforces.com/gym/304970/problem/A
/*
Approach : O(2n) = O(n)

Make a tree(graph) using the edges given

Now for each node check if its respect is 1, and all its children's respect is 1
Then it can be removed

Store all nodes to be deleted in the res and print at end
*/
void queen()
{
    int n;
    cin >> n;
    vector<vector<int>> tree(n);
    vector<int> respect(n);

    for (int i = 0; i < n; i++)
    {
        int p, c;
        cin >> p >> c;

        if (p != -1)
            tree[p - 1].push_back(i);
        respect[i] = c;
    }

    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        //if current node does not respect its parent
        if (respect[i] == 1)
        {
            bool flag = false;
            //check if all its children respect it
            for (int child : tree[i])
            {
                if (respect[child] == 0)
                {
                    flag = true;
                    break;
                }
            }

            //no child respects it, then delete it
            if (!flag)
                res.push_back(i + 1);
        }
    }

    if (res.size() == 0)
    {
        cout << -1;
        return;
    }

    for (int e : res)
        cout << e << " ";
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}