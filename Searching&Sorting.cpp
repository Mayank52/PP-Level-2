#include <bits/stdc++.h>

using namespace std;

// 704. Binary Search
/* 
Approach: O(logn) Base of log = 2
We keep low = 0, high = size - 1
and mid = low + (high - low)/2

And if arr[mid] < target
Then we reject everything on left
Else we reject everthing in right of mid

This way we get the lower_bound i.e. the smallest number >= target
*/
// Approach: O(logn)
int search(vector<int> &nums, int target)
{
    int lo = 0, hi = nums.size() - 1;

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] < target)
            lo = mid + 1;
        else
            hi = mid;
    }

    return nums[lo] == target ? lo : -1;
}

// Ternary Search
/*
Approach: O(logn) Base of log = 3
In ternary search we reject 2/3 of the array instead of 1/2 in binary search
We find 2 mids: 
mid1 = lo + (hi - lo)/3
mid2 = hi - (hi - lo)/3

And then we move to either:
1. < mid1
2. > mid2
3. > mid1 && < mid2

This way get a complexity of O(logn) base3

In binary search we have log(2)n , here we have log(3)n
But in binary search we do 1 comparison, here we do 2 comparisons to reject
So, here the complexity becomes O(2*log(3)n)
And now, log(2)n < 2 * log(3)n
So, binary search is better
*/
int ternarySearch(int key, vector<int> &arr)
{
    int l = 0, r = arr.size() - 1;

    while (r >= l)
    {

        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;

        if (arr[mid1] == key)
            return mid1;
        if (arr[mid2] == key)
            return mid2;

        if (key < arr[mid1])
            r = mid1 - 1;
        else if (key > arr[mid2])
            l = mid2 + 1;
        else
        {
            l = mid1 + 1;
            r = mid2 - 1;
        }
    }

    // Key not found
    return -1;
}

// 4. Median of Two Sorted Arrays
/*
Approach: O(log(n+m))
We find the mid of first array
*/
int leftMax(vector<int> &nums, int idx)
{
    if (idx - 1 < 0)
        return INT_MIN;

    return nums[idx - 1];
}
int rightMin(vector<int> &nums, int idx)
{
    if (idx == nums.size())
        return INT_MAX;

    return nums[idx];
}
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
    int totalSize = nums1.size() + nums2.size();

    if (nums1.size() > nums2.size())
        swap(nums1, nums2);

    int lo = 0, hi = nums1.size();
    int splitSize = (totalSize + 1) / 2;

    while (lo <= hi)
    {
        int mid1 = lo + (hi - lo) / 2;
        int mid2 = splitSize - mid1;

        int leftMax1 = leftMax(nums1, mid1), rightMin1 = rightMin(nums1, mid1);
        int leftMax2 = leftMax(nums2, mid2), rightMin2 = rightMin(nums2, mid2);

        if (leftMax1 <= rightMin2 && leftMax2 <= rightMin1)
        {
            if (totalSize % 2 == 0)
                return (max(leftMax1, leftMax2) + min(rightMin1, rightMin2)) / 2.0;
            else
                return max(leftMax1, leftMax2);
        }
        else if (leftMax1 > rightMin2)
            hi = mid1 - 1;
        else
            lo = mid1 + 1;
    }

    return -1;
}

// 1283. Find the Smallest Divisor Given a Threshold
int smallestDivisor(vector<int> &nums, int threshold)
{
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
