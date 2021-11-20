#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>
#include <math.h>
#include <list>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
};
class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
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

// 987. Vertical Order Traversal of a Binary Tree
/*
Approach: Level Order Traversal
On leetcode, in case two node in a vertical level are at the same horizontal,
then we have to sort them in increasing order of their values
So, we make a map of vertical levels: verticalLevel : list of {value, horizontal level}
Then after the BFS, we sort every vertical level in order of horizontal level, and if level is =, then 
in order of values, and add the sorted level to answer.
*/
vector<vector<int>> verticalTraversal(TreeNode *root)
{
    unordered_map<int, vector<pair<int, int>>> verticalLevels;

    queue<pair<TreeNode *, int>> que;
    que.push({root, 0});

    int hl = 0, minLeft = INT_MAX, maxRight = INT_MIN;
    while (que.size() > 0)
    {
        int size = que.size();

        while (size--)
        {
            pair<TreeNode *, int> rnode = que.front();
            que.pop();

            minLeft = min(minLeft, rnode.second);
            maxRight = max(maxRight, rnode.second);

            verticalLevels[rnode.second].push_back({rnode.first->val, hl});

            if (rnode.first->left != nullptr)
                que.push({rnode.first->left, rnode.second - 1});
            if (rnode.first->right != nullptr)
                que.push({rnode.first->right, rnode.second + 1});
        }

        hl++;
    }

    vector<vector<int>> res;
    for (int i = minLeft; i <= maxRight; i++)
    {
        // sort according to horizontal level
        sort(verticalLevels[i].begin(), verticalLevels[i].end(), [&](pair<int, int> p1, pair<int, int> p2)
             {
                 if (p1.second == p2.second)
                     return p1.first < p2.first;
                 else
                     return p1.second < p2.second;
             });

        // add the level to result
        vector<int> level;
        for (int j = 0; j < verticalLevels[i].size(); j++)
            level.push_back(verticalLevels[i][j].first);

        res.push_back(level);
    }

    return res;
}

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
/*
Approach 1: O(n)
Traverse in inorder, keep a prev node
When prev node in inorder is the target node, then current node is its successor

Approach 2: O(h) h = height of BST
Inorder Successor will be the node with just greater value
Cases:
1. The leftmost child of target's right subtree. Eg: 8's Successor is 10
2. If the right child does not have a left child, then right child itself is successor. Eg: 12's is 14
3. If the node does not have a right child, then its inorder successor will be the first node in its node to root path
   that has the target node in its left subtree. Eg: 14's is 20 and 10's is 12

            20
           /  \
          8    22
        /  \
       4    12
           /  \
          10  14

So, first find the target in the BST
Then if the node has a right child, then its successor, is right child's leftmost child, and return false, as successor has been found
If it does not have a right child, then return true
So, now if a node get true from its left child, then this node is the successor
Make it the successor  and return false as now the successor was found
*/
// Approach 1: O(n)
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
// Approach 2: O(h)
TreeNode *succ = nullptr;
bool inorderSuccessor_(TreeNode *root, TreeNode *p)
{
    if (root == nullptr)
        return false;

    if (root->val < p->val)
        return inorderSuccessor_(root->right, p);
    else if (root->val > p->val)
    {
        // if target node is in its left subtree, then make this the successor
        bool leftAns = inorderSuccessor_(root->left, p);
        if (leftAns)
            succ = root;
    }
    else
    {
        // inorder successor
        // right child != null, so succ is leftmost of right child
        if (root->right != nullptr)
        {
            TreeNode *rightNode = root->right;
            while (rightNode->left != nullptr)
                rightNode = rightNode->left;

            succ = rightNode;
        }
        // right child == null, return true to indicate that target node is present in this path
        else
            return true;
    }

    return false;
}
TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
{
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

At each level, atleast one of the left and right child will be complete,
So, that call will return directly, so, it will reduce the tree by half at each step
So, the Time complexity = O(logn * 2logn) = O(logn * logn)
And in tree height = logn 
So, Time complexity = O(h*h) 
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
        return (1 << lh) - 1; // 2 ^ lh - 1

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

Approach 3: O(n), O(n)
Get the inorder of the BST in an array, then get the lower_bound of target in array
Then we take 2 pointer, one left just before the target, and one right at the target
And now left moves backward, and right moves forward.
Now until we have k values, we check the absolute with both left and right elements
And whichever one is smaller we add that to answer and move that pointer ahead.

Approach 4: Time: O(logn + k), Space: O(logn)
Now using approach 3, we can do same thing with 2 stacks like in 653. Two Sum IV - Input is a BST
This approach is same as 653. Two Sum IV - Input is a BST

Here we use 2 stacks, one to maintain the increasing order, and one to maintain to decreasing order
So, in increasing stack the top element is min, and in decreasing stack top element is max
And in the BST, we first find the target in tree in logn, and add the nodes in that path into 2 stacks
If the current node < target, then add to decreasing stack and go to right
And if current node > target, then add to increasing stack and go to left
And start k closest values to result
Compare the difference of target with top of both left and right stack, and whichever is smaller 
add it to result and move that ahead.
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
// Approach 3:
void inorderTraversal(TreeNode *node, vector<double> &inorder){
    if(node == nullptr) return;

    inorderTraversal(node->left, inorder);

    inorder.push_back(node->val);

    inorderTraversal(node->right, inorder);
}
vector<int> closestKValues(TreeNode *root, double target, int k)
{
    // write your code here
    vector<double> inorder;
    inorderTraversal(root, inorder);

    int idx = lower_bound(inorder.begin(), inorder.end(), target) - inorder.begin();

    cout<<idx<<endl;

    int i = (idx == inorder.size()) ? idx - 1 : idx, j = i + 1;
    vector<int> res;
    while(k-- > 0){
        if(j >= inorder.size() || i >= 0 && abs(inorder[i] - target) < abs(inorder[j] - target)){
            res.push_back(inorder[i]);
            i--;
        }
        else{
            res.push_back(inorder[j]);
            j++;
        }
    }

    return res;
}
//Approach 4:
void findNode(TreeNode *root, double target, stack<TreeNode *> &leftStack, stack<TreeNode *> &rightStack)
{
    TreeNode *curr = root;

    while (curr != nullptr)
    {
        if (curr->val < target)
        {
            rightStack.push(curr);
            curr = curr->right;
        }
        else
        {
            leftStack.push(curr);
            curr = curr->left;
        }
    }
}
void moveLeftToNext(stack<TreeNode *> &leftStack)
{
    TreeNode *curr = leftStack.top()->right;
    leftStack.pop();

    while (curr != nullptr)
    {
        leftStack.push(curr);
        curr = curr->left;
    }
}
void moveRightToNext(stack<TreeNode *> &rightStack)
{
    TreeNode *curr = rightStack.top()->left;
    rightStack.pop();

    while (curr != nullptr)
    {
        rightStack.push(curr);
        curr = curr->right;
    }
}
vector<int> closestKValues(TreeNode *root, double target, int k)
{
    // write your code here
    stack<TreeNode *> leftStack, rightStack;

    findNode(root, target, leftStack, rightStack);

    vector<int> res;

    while (k-- > 0)
    {
        if (rightStack.size() == 0 || (leftStack.size() > 0 && abs(leftStack.top()->val - target) < abs(rightStack.top()->val - target)))
        {
            res.push_back(leftStack.top()->val);
            moveLeftToNext(leftStack);
        }
        else
        {
            res.push_back(rightStack.top()->val);
            moveRightToNext(rightStack);
        }
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

// 117. Populating Next Right Pointers in Each Node II
/*
Approach: Time: O(n), Space: O(1)
On each level, 
Keep a head of next level node, and a previous node
So, we treat every level like a linked list
And for every node instead of connecting its children's next to the next node's children, 
We keep a previous and connect it's next to current node's children, then they become previous, and so on
So, For the current node, if its left child exists, then connect the previous node's next to the left child
Also for the first node of each level previous is null, and this node is the head of next level
And we need to move to this node after current level is done, so if previous is null, then
current node becomes the head
*/
Node *connect(Node *root)
{
    Node *curr = root;

    while (curr != nullptr)
    {
        Node *nextLevelHead = nullptr;
        Node *prev = nullptr;

        // connect current level
        while (curr != nullptr)
        {
            // connect previous node's next to left child
            if (curr->left != nullptr)
            {
                if (prev != nullptr)
                    prev->next = curr->left;
                else
                    nextLevelHead = curr->left;

                prev = curr->left;
            }

            // connect previous node's next to right child
            if (curr->right != nullptr)
            {
                if (prev != nullptr)
                    prev->next = curr->right;
                else
                    nextLevelHead = curr->right;

                prev = curr->right;
            }

            // move to next node on same level
            curr = curr->next;
        }

        // move to next level
        curr = nextLevelHead;
    }

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

// 1373. Maximum Sum BST in Binary Tree
/*
Approach: O(n)
For each node, for that subtree to be a BST, the current node which is the root of the subtree
should be greater than max node in its left subtree and smaller than min node in its
right subtree. Also, its left and right subtree should also be BST
So, for each node, first check if its left and right subtree is a BST.
If they are not, then current node cannot be a BST
and nothing above the current node can be a BST either so return false directly as

And if its subtrees are BSTs, then check
max in left < current node value < min in right
for the current node and return the min and max value and subtree sum.
*/
vector<int> maxSumBST(TreeNode *root, int &maxSum)
{
    // return value: max element in subtree, min element in substree, sum of subtree, isBST(0->false, 1->True)
    if (root == nullptr)
        return {INT_MIN, INT_MAX, 0, 1};
    // leaf node
    if (root->left == nullptr && root->right == nullptr)
    {
        maxSum = max(maxSum, root->val);
        return {root->val, root->val, root->val, 1};
    }

    vector<int> leftAns = maxSumBST(root->left, maxSum);
    vector<int> rightAns = maxSumBST(root->right, maxSum);

    // if current node is a BST, then update maxSum
    if (leftAns[3] && rightAns[3] && leftAns[0] < root->val && root->val < rightAns[1])
    {
        maxSum = max(maxSum, leftAns[2] + root->val + rightAns[2]);
        return {max({leftAns[0], rightAns[0], root->val}), min({leftAns[1], rightAns[1], root->val}), leftAns[2] + root->val + rightAns[2], 1};
    }

    // if current node is not BST, then anything above it wont be either
    // so values dont matter to them
    return {0, 0, 0, 0};
}
int maxSumBST(TreeNode *root)
{
    int maxSum = INT_MIN;

    maxSumBST(root, maxSum);

    return max(maxSum, 0);
}

// 1483. Kth Ancestor of a Tree Node
/*
Approach: Binary Lifting
Preprocessing: O(nlogn)
Query: O(logn)
*/
class TreeAncestor
{
private:
    vector<vector<int>> ancestors;
    int maxBitCount;

    void findAllAncestors(vector<int> &parent)
    {
        int n = parent.size();

        // count the number of bits in total node count
        maxBitCount = 0;
        while (1 << (maxBitCount) <= n)
            maxBitCount++;

        ancestors.resize(n, vector<int>(maxBitCount, -1));

        // mark the first ancestors of every node with their parents
        for (int i = 0; i < n; i++)
            ancestors[i][0] = parent[i];

        for (int i = 1; i < maxBitCount; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // if (i-1)th ancestor of jth node is not -1
                if (ancestors[j][i - 1] != -1)
                    ancestors[j][i] = ancestors[ancestors[j][i - 1]][i - 1];
            }
        }
    }

public:
    TreeAncestor(int n, vector<int> &parent)
    {
        findAllAncestors(parent);
    }

    int getKthAncestor(int node, int k)
    {
        int ancestor = node;
        for (int i = 0; i < maxBitCount; i++)
        {
            if (k & (1 << i))
                ancestor = ancestors[ancestor][i];

            if (ancestor == -1)
                return -1;
        }

        return ancestor;
    }
};

// Sum of all nodes whose kth ancestor is even (Interview Experience Question)
/*
Question: 
For a given binary tree, find the sum of values of all nodes whose kth ancestor is even.
Solution has not been tested as question or solution is not available anywhere

Approach: O(n), DFS
We use DFS and keep a deque to store the root to node path for the current node
And we also keep the level count of current node

We use the deque to maintain the root to node path for current node
Also, we keep the size of queue to k, so that the front of queue is always the kth ancestor
So, for each node we add it to the deque before calling for its children

For the current node if its level is < k, then just add it to the path i.e. the deque
As if its level < k, then its kth ancestor does not exist.
And if level >= k, then the front of queue is kth ancestor, so we check if that is even
and accordingly add current node to answer
Then we pop the front element and push the current node value to end so that now the front
of queue is the kth ancestor of current node's children

*/
void helper(TreeNode *node, int k, int lvl, deque<int> &que, int &evenSum)
{
    if (node == nullptr)
        return;

    // if current node's level >= k, then check front of queue
    if (lvl >= k)
    {
        // if kth ancestor is even, add current value to sum
        if (que.front() % 2 == 0)
            evenSum += node->val;

        // pop the front element
        que.pop_front();
    }

    // then add current node to the path
    que.push_back(node->val);

    // call for left and right children
    helper(node->left, k, lvl + 1, que, evenSum);
    helper(node->right, k, lvl + 1, que, evenSum);

    // remove current node from path
    que.pop_back();
}
int getSumofNodesWithEvenKthAncestor(TreeNode *root, int k)
{
    int evenSum = 0;
    deque<int> que;

    helper(root, k, 0, que, evenSum);

    return evenSum;
}

// 173. Binary Search Tree Iterator
/*
Approach: Time: O(1), Space: O(h), Using Stack
Brute Force would be to store the inorder in an array and then just return next element in O(1) time
But this takes O(n) space.
We can do in O(h) space using stack
In the stack we maintain it such that top of stack is always the next element
So, initially the first element in inorder is the smallest element which is lefmost of the BST
So, push the root into stack and keep going left and pushing elements until the leftmost element

Then when next is called, we have the next element on top.
So, we pop that and return it. Also, now we need to put the next element in inorder at top
So, if the element we just removed has a right child, then the next element again would be
leftmost of that right child. So, push every node in that path into the stack again.
And if there is no right child, then the top of the stack would be the removed element's root, 
which would have been the next element in inorder, so it is correct.

The space in stack can go at most the height of tree.
Also, although next() seems O(h), it is actually amortised O(1) as every node 
is only being visited once while being pushed into stack.
So, when the whole inorder is done, total would have been O(n).
*/
class BSTIterator
{
private:
    stack<TreeNode *> st;

public:
    BSTIterator(TreeNode *root)
    {
        TreeNode *curr = root;
        while (curr != nullptr)
        {
            st.push(curr);
            curr = curr->left;
        }
    }

    int next()
    {
        TreeNode *nextEle = st.top();
        st.pop();

        TreeNode *curr = nextEle->right;
        while (curr != nullptr)
        {
            st.push(curr);
            curr = curr->left;
        }

        return nextEle->val;
    }

    bool hasNext()
    {
        return st.size() > 0;
    }
};

// 653. Two Sum IV - Input is a BST
/*
Approach 1: Hashmap, Time: O(n), Space: O(n)
Go in inorder, and check if sum - val is present in hashmap, then return true
This works for any tree, not just BST

Approach 2: Inorder Array, Time: O(n), Space: O(n)
Put the inorder traversal in an array, and use 2 pointers to find the 2sum

Approach 3: 2 Stacks, Time: O(n), Space: O(h)
Like in BST Iterator, we keep the increasing inorder in first stack, and 
decreasing inorder in second stack, and use the same 2 pointer technique to get 2sum
*/
bool findTarget(TreeNode *root, int k)
{
    stack<TreeNode *> leftStack, rightStack;

    TreeNode *curr = root;
    while (curr != nullptr)
    {
        leftStack.push(curr);
        curr = curr->left;
    }
    curr = root;
    while (curr != nullptr)
    {
        rightStack.push(curr);
        curr = curr->right;
    }

    // while i < j
    while (leftStack.size() > 0 && rightStack.size() > 0 && leftStack.top() != rightStack.top())
    {
        int sum = leftStack.top()->val + rightStack.top()->val;

        if (sum == k)
            return true;
        else if (sum < k) // move left pointer forward
        {
            TreeNode *curr = leftStack.top()->right;
            leftStack.pop();

            while (curr != nullptr)
            {
                leftStack.push(curr);
                curr = curr->left;
            }
        }
        else // move right pointer backward
        {
            TreeNode *curr = rightStack.top()->left;
            rightStack.pop();

            while (curr != nullptr)
            {
                rightStack.push(curr);
                curr = curr->right;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}