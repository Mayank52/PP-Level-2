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
Since it is a Complete Tree,
In a Complete tree, of height h, the number of nodes = 2 ^ h - 1

So, for each node we check if the height of its left and right child is equal
If it is equal then it is a complete tree and directly return 2 ^ h - 1
Else do the same thing for its left and right child
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
        return (1 << lh) - 1;   // 2 ^ lh - 1

    return countNodes(root->left) + countNodes(root->right) + 1;
}

// 900 · Closest Binary Search Tree Value (Lintcode)
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
//Approach 1:
void closestKValues(TreeNode *root, double target, int k, priority_queue<vector<double>, vector<vector<double>>> &pq)
{
    if (root == nullptr)
        return;

    closestKValues(root->left, target, k, pq);

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

// 297. Serialize and Deserialize Binary Tree
// Encodes a tree to a single string.
string serialize(TreeNode *root)
{
    if (root == nullptr)
        return "n,"; //n for null

    return to_string(root->val) + "," + serialize(root->left) + serialize(root->right);
}

// Decodes your encoded data to tree.
int idx = 0;
TreeNode *deserialize(string data)
{
    if (idx == data.size() || data[idx] == 'n')
    {
        if (data[idx] == 'n')
        {
            idx += 2;
        }
        return nullptr;
    }

    int val = 0, sign = 0; //0=+ve , 1=-ve
    //get the sign: +ve or -ve
    if (data[idx] == '-')
    {
        sign = 1;
        idx++;
    }

    //get the node value
    while (data[idx] != ',')
        val = val * 10 + (data[idx++] - '0');

    if (sign == 1)
        val *= -1;

    TreeNode *root = new TreeNode(val);
    idx++;
    root->left = deserialize(data);
    root->right = deserialize(data);

    return root;
}

// https://codeforces.com/contest/1534/problem/D
/*
Approach:
1. Consider 1 as root. And print ? 1 as first query.
2. Then from the distance array find which node is at even level from 1 and which is at odd level.
    Node 1 is at level 0 which is even.
3. Either the nodes at even or odd level will definately be <=n/2.
4. So, print those nodes one by one as queries.
5. For each distance array, for all distance = 1, mark an edge.

This way we will get all the edges. We can use an adjacency matrix to mark edges.
Ans print the lower half diagonal to avoid printing same edges twice.
*/
void makeTree(vector<int> &level, int n, vector<vector<int>> &graph, bool isEven)
{
    for (int i = isEven ? 1 : 0; i < level.size(); i++)
    {
        cout << "? " << level[i] << endl;
        // cout.flush();

        //for all nodes get the distance array
        for (int j = 0; j < n; j++)
        {
            int dist;
            cin >> dist;

            // mark edges for distance = 1
            if (dist == 1)
            {
                graph[level[i]][j + 1] = 1;
                graph[j + 1][level[i]] = 1;
            }
        }
    }
}
void printTree(vector<vector<int>> &graph)
{
    cout << "!" << endl;
    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (graph[i][j] == 1)
                cout << i << " " << j << endl;
        }
    }
}
void lostTree()
{
    int n;
    cin >> n;

    cout << "? " << 1 << endl;
    // cout.flush();

    vector<int> evenLevel, oddLevel;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1));

    evenLevel.push_back(1);

    for (int i = 0; i < n; i++)
    {
        int dist;
        cin >> dist;

        //for node 1, mark add edge in adjacency matrix for all nodes at distance 1
        if (dist == 1)
        {
            graph[1][i + 1] = 1;
            graph[i + 1][1] = 1;
        }

        // get all even level nodes from 1
        if (dist % 2 == 0)
        {
            if (i > 0)
                evenLevel.push_back(i + 1);
        }
        //get all odd level nodes from 1
        else
        {
            oddLevel.push_back(i + 1);
        }
    }

    // make the tree using level with less nodes
    if (evenLevel.size() <= oddLevel.size())
    {
        makeTree(evenLevel, n, graph, true);
    }
    else
    {
        makeTree(oddLevel, n, graph, false);
    }

    printTree(graph);
}

// Extra(Not in List)==================================================================================
// 617. Merge Two Binary Trees

// 617. Merge Two Binary Trees
TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
{
    if (root1 == nullptr && root2 == nullptr)
        return nullptr;

    // if either node is null, then just return the not null node
    if (root1 == nullptr || root2 == nullptr)
        return root1 ? root1 : root2;

    // else merge the children of both trees, and overlap this node of both trees
    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);
    root1->val += root2->val;

    return root1;
}

// 669. Trim a Binary Search Tree
TreeNode *trimBST(TreeNode *root, int low, int high)
{
    if (root == nullptr)
        return nullptr;

    // if this node is less than range, then return trimmed right node
    if (root->val < low)
        return trimBST(root->right, low, high);
    // if this node is greater than range, then return trimmed left node
    else if (root->val > high)
        return trimBST(root->left, low, high);
    // else trim the left and right childs, and return this node
    else
    {
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    }
}

// 863. All Nodes Distance K in Binary Tree
vector<int> res;
void kDown(TreeNode *root, int k, TreeNode *blockNode)
{
    if (root == nullptr || root == blockNode)
        return;

    if (k == 0)
        res.push_back(root->val);

    kDown(root->left, k - 1, blockNode);
    kDown(root->right, k - 1, blockNode);
}
int allNodesKAway(TreeNode *root, int k, TreeNode *target)
{
    if (root == nullptr)
        return -1;

    if (root == target)
    {
        kDown(root, k, nullptr);
        return 1;
    }

    int leftDistance = allNodesKAway(root->left, k, target);
    if (leftDistance != -1)
    {
        kDown(root, k - leftDistance, root->left);
        return leftDistance + 1;
    }

    int rightDistance = allNodesKAway(root->right, k, target);
    if (rightDistance != -1)
    {
        kDown(root, k - rightDistance, root->right);
        return rightDistance + 1;
    }

    return -1;
}
vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
{
    allNodesKAway(root, k, target);
    return res;
}

// 662. Maximum Width of Binary Tree
/*
Approach: O(n)
To get the max level width, use the binary heap property to find left and right child index
left Child = 2 * parentIdx
right Child = 2 * parentIdx + 1

Then for each level find the min idx and max idx
And width of level = max idx - min idx + 1

Also, to prevent overflow in 2 * parentIdx for deep nodes,
use parentIdx = parentIdx - left most parent idx of that level
*/
int widthOfBinaryTree(TreeNode *root)
{
    typedef pair<TreeNode *, long long> pair;

    queue<pair> que;
    que.push({root, 0});

    long long width = 0, leftMostIdx = 0;

    while (que.size() > 0)
    {
        int size = que.size();
        long long leftMin = LONG_MAX, rightMax = LONG_MIN;

        while (size-- > 0)
        {
            pair rpair = que.front();
            que.pop();

            TreeNode *node = rpair.first;
            long long idx = rpair.second - leftMostIdx;

            leftMin = min(leftMin, idx);
            rightMax = max(rightMax, idx);

            if (node->left)
                que.push({node->left, idx * 2});
            if (node->right)
                que.push({node->right, idx * 2 + 1});
        }

        width = max(width, rightMax - leftMin + 1);
        leftMostIdx = leftMin;
    }

    return (int)width;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}