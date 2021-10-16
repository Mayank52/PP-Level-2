#include <bits/stdc++.h>

using namespace std;

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



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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