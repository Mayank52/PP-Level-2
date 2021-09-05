#include <bits/stdc++.h>

using namespace std;

// 704. Binary Search=========================================================================================================
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
Approach: Binary Search, Time: O(log(min(n,m))), Space: O(1)
Find the size of the split half of the merged array: (nums1.size() + nums2.size() + 1) / 2
We take +1 beacuse we want ceil in case of odd number length

Then, We perform binary search on the smaller length array
mid1 = mid of arr1
Now, we want half elements of both combined on left, and half on right
So, mid1 gives the number of elements of arr1 on left. 
Remaining elements will be from the second array
So, mid2 = split - mid1

Now to make sure that the mid1 , mid2 divides the array into left and right half
such that all elements in left half <= right half
We check that the leftMax of arr1 <= rightMin of arr2
and leftMax of arr2 <= rightMin of arr1

If this condition is satisfied then we are in middle of the merged array, and we can find the median

Else if leftMax of arr1 > rightMin2, then we reject the right half , because we need to satisfy leftMax <= rightMin
Else we reject the left half
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
    if (nums1.size() > nums2.size())
        return findMedianSortedArrays(nums2, nums1);

    int totalSize = nums1.size() + nums2.size();
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
/*
Approach: Binary Search O(n*log(max divisor))
We use binary search on the answer i.e. We find the divisor using binary search
The max divisor we can get = max element of the array
Because every number greater than that will give the same quotients

And the minimum will be 1.

So, we use binary search for the range 1 to maxNum

And each time the mid will be the divisor
Using mid as divisor we find the sum of all quotients
Now,
If sum < threshold: Then as we want the minimum value, and since sum <= threshold
    so, it is a possible ans, and everything on its right is rejected.
    And we try to find a smaller answer on its left side
Else
    If the current mid gave a sum > threshold, then everything on its left, i.e. 
    everything smaller than mid will just give even greater values. So, we reject 
    everything on left
*/
int smallestDivisor(vector<int> &nums, int threshold)
{
    int maxDivisor = 0;
    for (int val : nums)
        maxDivisor = max(maxDivisor, val);

    int lo = 1, hi = maxDivisor;

    while (lo < hi)
    {
        double mid = lo + (hi - lo) / 2;

        int res = 0;
        for (int val : nums)
            res += ceil(val / mid);

        if (threshold < res)
            lo = mid + 1;
        else
            hi = mid;
    }

    return lo;
}

// 1011. Capacity To Ship Packages Within D Days
/*
Approach: O(n * log(totalSum of Weights))
We do binary search to find the minimum weight 
low = max weight value, as we need atleast that much to carry all weights
high = total sum of all weights

Eg: [1,2,3,1,1]
Here, the ship has to be able to carry atleast 3 weight otherwise it wont be able to carry package at index 2.
And the max is the sum of weights which will take the ship 1 day to carry as it can carry it all at once.

Then use binary search to find the minimum weight
If the current mid weight requires d days, then
If d < days: Then d is a possible answer, and we want minimum, so reject the right side
Else reject the left side
*/
int shipWithinDays(vector<int> &weights, int days)
{
    int totalWeight = 0, maxWeight = weights[0];
    for (int val : weights)
    {
        totalWeight += val;
        maxWeight = max(maxWeight, val);
    }

    int lo = maxWeight, hi = totalWeight;

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        int requiredDays = 1, currWeight = 0;
        for (int val : weights)
        {
            currWeight += val;
            if (currWeight > mid)
            {
                requiredDays++;
                currWeight = val;
            }
        }

        if (requiredDays > days)
            lo = mid + 1;
        else
            hi = mid;
    }

    return lo;
}

// 875. Koko Eating Bananas
/*
Approach: O(n * log(max pile size))
We perform Binary Search to find the minimum pile size
lo = 1, hi = max pile size
*/
int minEatingSpeed(vector<int> &piles, int h)
{
    int lo = 1, hi = piles[0];

    for (int val : piles)
    {
        lo = min(lo, val);
        hi = max(hi, val);
    }

    while (lo < hi)
    {
        double mid = lo + (hi - lo) / 2;

        int hours = 0;
        for (int val : piles)
        {
            hours += ceil(val / mid);
        }

        if (hours > h)
            lo = mid + 1;
        else
            hi = mid;
    }

    return lo;
}

// Painter's Partition Problem
/*
Approach: O(n * log(totalTime))
Similar to 1011. Capacity To Ship Packages Within D Days
All A painters will work parallely, so, we need to find the minimum time that one painter is allowed such that
with that time, the number of painters <= A

So, we do binary search to find the time for one painter
lo = maxTime required for one job
hi = totalTime required for all jobs

Now for each mid, the maxTime a painter can use = mid
Now, for this time, we find the number of painters we need 
If they are <= A, then this is a possible answer, and we need minimum, so reject right side
Else we reject left side

*/
int paint(int A, int B, vector<int> &C)
{
    long long totalTime = 0, maxTime = C[0];
    for (long long val : C)
    {
        totalTime += val * B;
        maxTime = max(maxTime, val * B);
    }

    long long lo = maxTime, hi = totalTime;

    while (lo < hi)
    {
        long long mid = lo + (hi - lo) / 2;

        long long requiredPainters = 1, currTime = 0;

        for (long long val : C)
        {
            currTime += val * B;

            if (currTime > mid)
            {
                requiredPainters++;
                currTime = val * B;
            }
        }

        if (requiredPainters > A)
            lo = mid + 1;
        else
            hi = mid;
    }

    return lo % 10000003;
}

// 410. Split Array Largest Sum
/*
Approach: O(n * log(totalSum))
Same as 1011. Capacity To Ship Packages Within D Days

lo = max value in array, as you need to be able to fit each element into a subarray
hi = totalSum, we can put all elements in a single subarray

Eg: [7,2,5,10,8]
So, lo = 10 (minimum subarray sum)
If it is < 10 then 10 cannot be put in any subarray
*/
int splitArray(vector<int> &nums, int m)
{
    int maxVal = nums[0], totalSum = 0;
    for (int val : nums)
    {
        maxVal = max(maxVal, val);
        totalSum += val;
    }

    int lo = maxVal, hi = totalSum;

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        int subArrCount = 1, currSum = 0;
        for (int val : nums)
        {
            currSum += val;

            if (currSum > mid)
            {
                subArrCount++;
                currSum = val;
            }
        }

        if (subArrCount > m)
            lo = mid + 1;
        else
            hi = mid;
    }

    return lo;
}

// 786. K-th Smallest Prime Fraction
vector<int> kthSmallestPrimeFraction(vector<int> &arr, int k)
{
    int n = arr.size();

    double lo = 0.0, hi = 1.0;

    while (lo <= hi)
    {
        double mid = lo + (hi - lo) / 2;

        int i = 0, j = n - 1;
        int num = 0, den = 1;

        while ()
    }
}

// 153. Find Minimum in Rotated Sorted Array
/*
Approach : O(logn)
Minimum element is the pivot of the rotated sorted array
So, we have to find the first element of the sorted array before it was rotated
Using binary search
If arr[mid] > arr[hi]:
    This means the mid element was brought to the front after rotation. So, the minimum element would lie to its right
Else the minimium element is to its left
*/
int findMin(vector<int> &nums)
{
    int lo = 0, hi = nums.size() - 1;

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] > nums[hi])
            lo = mid + 1;
        else
            hi = mid;
    }

    return nums[lo];
}

// 154. Find Minimum in Rotated Sorted Array II
/*
Approach: O(n)
We use the same approach as with non duplicates
But in case of duplicates 
if arr[mid] == arr[hi], then we do hi--
We can have following cases:
[2,2,2,0,1]
[2,2,2,0,2]
[2,2,2,2,2]

So, in worst case we will need a linear search to find the min element
Because there is no way to find which side to go if arr[mid] == arr[hi]
So, we just reduce the upper limit by 1, and check again
*/
int findMin(vector<int> &nums)
{
    int lo = 0, hi = nums.size() - 1;

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] > nums[hi])
            lo = mid + 1;
        else if (nums[mid] < nums[hi])
            hi = mid;
        else
            hi--;
    }

    return nums[lo];
}

// 33. Search in Rotated Sorted Array
/*
Approach: O(logn)
1. Find the pivot index of array
2. If target > last element of array, then it lies in left of pivot
   Else it lies in right of pivot
*/
int search(vector<int> &nums, int target)
{
    int n = nums.size();

    // find pivot index
    int lo = 0, hi = n - 1;

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] > nums[hi])
            lo = mid + 1;
        else
            hi = mid;
    }

    int pivot = lo;

    lo = 0, hi = n - 1;

    // if target > last element then it lies in left side of pivot
    if (target > nums[n - 1])
        hi = pivot - 1;
    // if target <= last element, then it lies in right side of pivot
    else
        lo = pivot;

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

// 81. Search in Rotated Sorted Array II
bool search(vector<int> &nums, int target)
{
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
