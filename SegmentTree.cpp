#include <bits/stdc++.h>

using namespace std;

// Segment Tree, Basic Implementations=================================================
/*
https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-6
Memory efficient implementation
Most people use the implementation from the previous section. 
If you look at the array t you can see that it follows the numbering of the tree nodes 
in the order of a BFS traversal (level-order traversal). 
Using this traversal the children of vertex v are 2v and 2v+1 respectively. 
However if n is not a power of two, this method will skip some indices 
and leave some parts of the array t unused. The memory consumption is limited by 4n, 
even though a Segment Tree of an array of n elements requires only 2n−1 vertices.

However it can be reduced. 
We renumber the vertices of the tree in the order of an Euler tour traversal (pre-order traversal), 
and we write all these vertices next to each other.

Lets look at a vertex at index v, 
and let him be responsible for the segment [l,r], and let mid=l+r2. 
It is obvious that the left child will have the index v+1. 
The left child is responsible for the segment [l,mid], 
i.e. in total there will be 2∗(mid−l+1)−1 vertices in the left child's subtree. 
Thus we can compute the index of the right child of v. 
The index will be v+2∗(mid−l+1). 
By this numbering we achieve a reduction of the necessary memory to 2n.
*/

// Range Maximum Query with Node Update
// (https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-interview-prep/segment-tree/max-in-a-interval-range-query-point-update-official/ojquestion)
/*
Approach: 
Update: O(logn)
Query: O(logn)
*/
class SegmentTree
{
private:
    vector<int> tree;
    vector<int> arr;

    void buildTree(int nodeIdx, int lo, int hi)
    {
        if (lo == hi)
        {
            tree[nodeIdx] = arr[lo];
            return;
        }

        int mid = lo + (hi - lo) / 2;

        buildTree(nodeIdx * 2, lo, mid);         // left child
        buildTree(nodeIdx * 2 + 1, mid + 1, hi); // right child

        //current node's max is max of left and right child
        tree[nodeIdx] = max(tree[nodeIdx * 2], tree[nodeIdx * 2 + 1]);
    }

    int query(int nodeIdx, int lo, int hi, int left, int right)
    {
        // current interval is outside target interval
        if (hi < left || lo > right)
            return INT_MIN;

        // leaf node OR current interval is completely inside target interval
        if (lo == hi || (lo >= left && hi <= right))
            return tree[nodeIdx];

        int mid = lo + (hi - lo) / 2;

        // get the left and right max
        int leftMax = query(nodeIdx * 2, lo, mid, left, right);
        int rightMax = query(nodeIdx * 2 + 1, mid + 1, hi, left, right);

        // return the max of both children
        return max(leftMax, rightMax);
    }

    void update(int nodeIdx, int lo, int hi, int pos, int val)
    {
        // base case
        if (lo == hi)
        {
            tree[nodeIdx] = val;
            arr[pos] = val;
            return;
        }

        int mid = lo + (hi - lo) / 2;

        if (pos > mid) // go to right child
            update(nodeIdx * 2 + 1, mid + 1, hi, pos, val);
        else // go to left child
            update(nodeIdx * 2, lo, mid, pos, val);

        // update current node value
        tree[nodeIdx] = max(tree[nodeIdx * 2], tree[nodeIdx * 2 + 1]);
    }

public:
    SegmentTree(vector<int> &arr)
    {
        this->arr = arr;
        tree.resize(4 * arr.size());
        buildTree(1, 0, arr.size() - 1);
    }

    void update(int pos, int val)
    {
        update(1, 0, arr.size() - 1, pos, val);
    }

    int query(int l, int r)
    {
        return query(1, 0, arr.size() - 1, l, r);
    }
};

// 307. Range Sum Query - Mutable
// Approach 1: O(4*n) Segment Tree Size
class NumArray
{
private:
    vector<int> tree;
    vector<int> nums;

    void buildTree(int nodeIdx, int lo, int hi)
    {
        if (lo == hi)
        {
            tree[nodeIdx] = nums[lo];
            return;
        }

        int mid = lo + (hi - lo) / 2;

        buildTree(2 * nodeIdx, lo, mid);
        buildTree(2 * nodeIdx + 1, mid + 1, hi);

        tree[nodeIdx] = tree[2 * nodeIdx] + tree[2 * nodeIdx + 1];
    }

    void update(int nodeIdx, int lo, int hi, int index, int val)
    {
        if (lo == hi)
        {
            tree[nodeIdx] = val;
            nums[index] = val;
            return;
        }

        int mid = lo + (hi - lo) / 2;

        if (index > mid)
            update(2 * nodeIdx + 1, mid + 1, hi, index, val);
        else
            update(2 * nodeIdx, lo, mid, index, val);

        tree[nodeIdx] = tree[2 * nodeIdx] + tree[2 * nodeIdx + 1];
    }

    int sumRange(int nodeIdx, int lo, int hi, int left, int right)
    {
        if (lo > right || hi < left)
            return 0;

        if (lo == hi || lo >= left && hi <= right)
            return tree[nodeIdx];

        int mid = lo + (hi - lo) / 2;

        int leftSum = sumRange(2 * nodeIdx, lo, mid, left, right);
        int rightSum = sumRange(2 * nodeIdx + 1, mid + 1, hi, left, right);

        return leftSum + rightSum;
    }

public:
    NumArray(vector<int> &nums)
    {
        this->nums = nums;
        this->tree.resize(4 * nums.size());
        buildTree(1, 0, nums.size() - 1);
    }

    void update(int index, int val)
    {
        update(1, 0, this->nums.size() - 1, index, val);
    }

    int sumRange(int left, int right)
    {
        return sumRange(1, 0, this->nums.size() - 1, left, right);
    }
};
// Approach 2: Same approach with O(2*n) Segment Tree Size
/*
Instead of storing left child at 2*node, right at 2*node + 1
Store in preorder traversal order
So, left = node + 1
right = node + 2*(mid - lo + 1)

Rest everything remains the exact same
*/
class NumArray
{
private:
    vector<int> tree;
    vector<int> nums;

    void buildTree(int nodeIdx, int lo, int hi)
    {
        if (lo == hi)
        {
            tree[nodeIdx] = nums[lo];
            return;
        }

        int mid = lo + (hi - lo) / 2;

        buildTree(nodeIdx + 1, lo, mid);
        buildTree(nodeIdx + 2 * (mid - lo + 1), mid + 1, hi);

        tree[nodeIdx] = tree[nodeIdx + 1] + tree[nodeIdx + 2 * (mid - lo + 1)];
    }

    void update(int nodeIdx, int lo, int hi, int index, int val)
    {
        if (lo == hi)
        {
            tree[nodeIdx] = val;
            nums[index] = val;
            return;
        }

        int mid = lo + (hi - lo) / 2;

        if (index > mid)
            update(nodeIdx + 2 * (mid - lo + 1), mid + 1, hi, index, val);
        else
            update(nodeIdx + 1, lo, mid, index, val);

        tree[nodeIdx] = tree[nodeIdx + 1] + tree[nodeIdx + 2 * (mid - lo + 1)];
    }

    int sumRange(int nodeIdx, int lo, int hi, int left, int right)
    {
        if (lo > right || hi < left)
            return 0;

        if (lo == hi || lo >= left && hi <= right)
            return tree[nodeIdx];

        int mid = lo + (hi - lo) / 2;

        int leftSum = sumRange(nodeIdx + 1, lo, mid, left, right);
        int rightSum = sumRange(nodeIdx + 2 * (mid - lo + 1), mid + 1, hi, left, right);

        return leftSum + rightSum;
    }

public:
    NumArray(vector<int> &nums)
    {
        this->nums = nums;
        this->tree.resize(2 * nums.size());
        buildTree(1, 0, nums.size() - 1);
    }

    void update(int index, int val)
    {
        update(1, 0, this->nums.size() - 1, index, val);
    }

    int sumRange(int left, int right)
    {
        return sumRange(1, 0, this->nums.size() - 1, left, right);
    }
};

// Lazy Propagation===============================================================
// What's At Idx - Point Query Range Update
// (https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-interview-prep/segment-tree/whats-at-idx-point-query-range-update-official/ojquestion)
class SegmentTree
{
private:
    vector<int> lazy, arr;

    void build(int nodeIdx, int lo, int hi)
    {
        if (lo == hi)
        {
            lazy[nodeIdx] = arr[lo];
            return;
        }

        int mid = lo + (hi - lo) / 2;

        build(nodeIdx + 1, lo, mid);
        build(nodeIdx + 2 * (mid - lo + 1), mid + 1, hi);

        lazy[nodeIdx] = 0;
    }

    void update(int nodeIdx, int lo, int hi, int l, int r, int val)
    {
        if (hi < l || lo > r)
            return;

        if (lo == hi || l <= lo && hi <= r)
        {
            lazy[nodeIdx] += val;
            return;
        }

        int mid = lo + (hi - lo) / 2;

        update(nodeIdx + 1, lo, mid, l, r, val);
        update(nodeIdx + 2 * (mid - lo + 1), mid + 1, hi, l, r, val);
    }

    void propagate(int nodeIdx, int lo, int hi)
    {
        // if leaf node, then return
        if (lo == hi)
            return;

        int mid = lo + (hi - lo) / 2;

        // propagate to left child
        lazy[nodeIdx + 1] += lazy[nodeIdx];

        // propagate to right child
        lazy[nodeIdx + 2 * (mid - lo + 1)] += lazy[nodeIdx];

        // reset current node to 0
        lazy[nodeIdx] = 0;
    }

    int query(int nodeIdx, int lo, int hi, int idx)
    {
        propagate(nodeIdx, lo, hi);

        if (lo == hi)
            return lazy[nodeIdx];

        int mid = lo + (hi - lo) / 2;

        if (idx > mid)
            return query(nodeIdx + 2 * (mid - lo + 1), mid + 1, hi, idx);
        else
            return query(nodeIdx + 1, lo, mid, idx);
    }

public:
    SegmentTree(vector<int> &arr)
    {
        this->arr = arr;
        lazy.resize(2 * arr.size());
        build(1, 0, arr.size() - 1);
    }

    void update(int l, int r, int val)
    {
        update(1, 0, arr.size() - 1, l, r, val);
    }

    int query(int idx)
    {
        return query(1, 0, arr.size() - 1, idx);
    }
};

// Sum Of Range - Range Query Range Update
// (https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-interview-prep/segment-tree/sum-of-range-range-query-range-update-official/ojquestion)
class SegmentTree
{
private:
    vector<int> lazy, arr, tree;

    void build(int nodeIdx, int lo, int hi)
    {
        if (lo == hi)
        {
            tree[nodeIdx] = arr[lo];
            return;
        }

        int mid = lo + (hi - lo) / 2;

        build(nodeIdx + 1, lo, mid);
        build(nodeIdx + 2 * (mid - lo + 1), mid + 1, hi);

        lazy[nodeIdx] = 0;
        tree[nodeIdx] = tree[nodeIdx + 1] + tree[nodeIdx + 2 * (mid - lo + 1)];
    }

    void update(int nodeIdx, int lo, int hi, int l, int r, int val)
    {
        propagate(nodeIdx, lo, hi);

        if (hi < l || lo > r)
            return;

        if (lo == hi)
            tree[nodeIdx] += val;
        else if (l <= lo && hi <= r)
        {
            lazy[nodeIdx] += val;
            propagate(nodeIdx, lo, hi);
        }
        else
        {
            int mid = lo + (hi - lo) / 2;

            update(nodeIdx + 1, lo, mid, l, r, val);
            update(nodeIdx + 2 * (mid - lo + 1), mid + 1, hi, l, r, val);

            tree[nodeIdx] = tree[nodeIdx + 1] + tree[nodeIdx + 2 * (mid - lo + 1)];
        }
    }

    void propagate(int nodeIdx, int lo, int hi)
    {
        // if leaf node, then return
        if (lo == hi)
        {
            tree[nodeIdx] += lazy[nodeIdx];
            lazy[nodeIdx] = 0;
        }

        int mid = lo + (hi - lo) / 2;

        // update the sum in tree
        tree[nodeIdx] += lazy[nodeIdx] * (hi - lo + 1);

        // propagate to left child
        lazy[nodeIdx + 1] += lazy[nodeIdx];

        // propagate to right child
        lazy[nodeIdx + 2 * (mid - lo + 1)] += lazy[nodeIdx];

        // reset current node to 0
        lazy[nodeIdx] = 0;
    }

    int query(int nodeIdx, int lo, int hi, int l, int r)
    {
        propagate(nodeIdx, lo, hi);

        if (hi < l || lo > r)
            return 0;

        if (lo == hi || l <= lo && hi <= r)
            return tree[nodeIdx];

        int mid = lo + (hi - lo) / 2;

        int rightSum = query(nodeIdx + 2 * (mid - lo + 1), mid + 1, hi, l, r);
        int leftSum = query(nodeIdx + 1, lo, mid, l, r);

        return leftSum + rightSum;
    }

public:
    SegmentTree(vector<int> &arr)
    {
        this->arr = arr;
        lazy.resize(2 * arr.size());
        tree.resize(2 * arr.size());
        build(1, 0, arr.size() - 1);
    }

    void update(int l, int r, int val)
    {
        update(1, 0, arr.size() - 1, l, r, val);
    }

    int query(int l, int r)
    {
        return query(1, 0, arr.size() - 1, l, r);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // input
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    SegmentTree *treeObj = new SegmentTree(arr);

    int q;
    cin >> q;

    while (q--)
    {
        int x;
        cin >> x;

        if (x == 0)
        {
            int pos, val;
            cin >> pos >> val;

            treeObj->update(pos, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;

            cout << treeObj->query(l, r) << endl;
        }
    }

    return 0;
}