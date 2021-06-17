#include <bits/stdc++.h>

using namespace std;

//Construction of Fenwick Tree (Also Called : Binary Indexed Tree)===============================================
vector<long long> farr;

long long prefixSum(int idx)
{
    long long sum = 0;
    while (idx > 0)
    {
        sum += farr[idx];
        idx -= (idx & -idx);
    }

    return sum;
}

long long query(int l, int r)
{
    return prefixSum(r) - prefixSum(l - 1);
}

void update(int idx, int delta)
{
    while (idx < farr.size())
    {
        farr[idx] += delta;
        idx += (idx & -idx);
    }
}

void construct(vector<long long> &arr)
{
    for (int i = 1; i < arr.size(); i++)
    {
        update(i, arr[i]);
    }
}

void fenwickTree(vector<long long> &arr)
{
    int n = arr.size();

    farr.resize(n);

    construct(arr);

    for (int ele : farr)
        cout << ele << " ";
    cout << endl;

    int q;
    cin >> q;
    while (q-- > 0)
    {
        char ch;
        cin >> ch;

        if (ch == 'q')
        {
            int l, r;
            cin >> l >> r;

            long long ans = query(l, r);
            cout << ans << endl;
        }
        else
        {
            int idx, delta;
            cin >> idx >> delta;

            update(idx, delta);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> arr(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    fenwickTree(arr);

    return 0;
}

//Leetcode Question=============================================
// 303. Range Sum Query - Immutable
/*
Approach : Prefix Sum
Preprocessing: O(n), O(n)
Query : O(1) (Range Sum)

*/
class NumArray {
public:
    vector<int> prefixSum;
    
    NumArray(vector<int>& nums) {
        int n = nums.size();
        
        prefixSum.resize(n);
        prefixSum[0] = nums[0];
        
        for(int i = 1; i < n; i++)
            prefixSum[i] = prefixSum[i-1] + nums[i];
    }
    
    int sumRange(int left, int right) {
        if(left == 0) return prefixSum[right];
        
        return prefixSum[right] - prefixSum[left-1];
    }
};

// 307. Range Sum Query - Mutable
/*
Approach : Fenwick Tree
Preprocessing: O(nlogn), O(n)
Query : O(logn) (Range Sum)
Update : O(logn)
*/
class NumArray
{
public:
    vector<int> farr;
    vector<int> nums;

    void construct(vector<int> &arr)
    {
        for (int i = 1; i < arr.size(); i++)
        {
            updateFenwickArray(i, arr[i]);
        }
    }
    void updateFenwickArray(int idx, int delta)
    {
        while (idx < farr.size())
        {
            farr[idx] += delta;
            idx += (idx & -idx);
        }
    }
    int prefixSum(int idx)
    {
        int sum = 0;
        while (idx > 0)
        {
            sum += farr[idx];
            idx -= (idx & -idx);
        }

        return sum;
    }

    NumArray(vector<int> &nums)
    {
        int n = nums.size();

        this->nums = nums;

        vector<int> arr(n + 1);
        farr.resize(n + 1);

        for (int i = 1; i <= n; i++)
            arr[i] = nums[i - 1];

        construct(arr);
    }

    void update(int index, int val)
    {
        int delta = val - nums[index];
        nums[index] = val;

        updateFenwickArray(index + 1, delta);
    }
    int sumRange(int left, int right)
    {
        return prefixSum(right + 1) - prefixSum(left - 1 + 1);
    }
};
