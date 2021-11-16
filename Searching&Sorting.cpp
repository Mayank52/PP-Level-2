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
We take +1 because we want ceil in case of odd number length

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

// K-th element of two sorted Arrays  (https://practice.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1317/1)
/*
Brute Force: O(K)
Same as merge two sorted arrays using 2 pointers.

Best Approach: Binary Search, O(log(min(m,n)))
Same as median of 2 sorted arrays.
We take the smaller array as arr1 to get O(log(min(m,n)))
Then we find the
mid1 = lo + (hi - lo) / 2
And mid2 = k - mid1
This way we get k elements on left side and remaining on right side

Now, if the condition:
leftMax1 <= rightMin2 && leftMax2 <= rightMin1
is satisfied then max(leftMax1, leftMax2) is the answer
Else if leftMax1 > rightMin2 then we go to right side
Else we go to left side

Also, we take
lo == max(0, k - m)
Because if k = 7 and n = 4, m = 6
Then even if we take the complete second array, we still need atleast 1 element
from 1st array. So, the lo cannot start from 0.
So, lo = max(0, k - m)
Similarly hi = min(k, n)
As if k = 3, n = 4, m = 6
Then we can never get the 4th element of first array as answer.

Edge Case: if the kth element of one array is the kth smallest element.
Then the other array will contribute 0 elements to the left side
So, check this in base case
*/
int kthElement(int arr1[], int arr2[], int n, int m, int k)
{
    // take the smaller array as arr1
    if (n > m)
        return kthElement(arr2, arr1, m, n, k);

    // if kth element of 1st array is the answer
    if (n >= k && arr1[k - 1] <= arr2[0])
        return arr1[k - 1];
    // if kth element of 2nd array is the answer
    if (m >= k && arr2[k - 1] <= arr1[0])
        return arr2[k - 1];

    int lo = max(0, k - m), hi = min(k, n);

    while (lo <= hi)
    {
        int mid1 = lo + (hi - lo) / 2;
        int mid2 = k - mid1;

        int leftMax1 = mid1 - 1 > 0 ? arr1[mid1 - 1] : INT_MIN;
        int leftMax2 = mid2 - 1 > 0 ? arr2[mid2 - 1] : INT_MIN;
        int rightMin1 = mid1 < n ? arr1[mid1] : INT_MAX;
        int rightMin2 = mid2 < m ? arr2[mid2] : INT_MAX;

        if (leftMax1 <= rightMin2 && leftMax2 <= rightMin1)
            return max(leftMax1, leftMax2);
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

// Allocate Books (https://www.interviewbit.com/problems/allocate-books/)
/*
Approach: O(nlog(totalSum))
We have to minimize the page number sum for each student
So, we run a binary search on page numbers
lo = max page number a book has
hi = total sum of all page numbers

Everytime, the mid represents the max total number of pages we can assign to one student
So, using this find the count of students you can give the books to
If the count > B, then we need to increase page numbers per student so move to right side
Else move to left side
*/
int books(vector<int> &A, int B)
{
    if (A.size() < B)
        return -1;

    int totalPages = 0, maxPages = INT_MIN;
    for (int val : A)
    {
        totalPages += val;
        maxPages = max(maxPages, val);
    }

    int lo = maxPages, hi = totalPages;

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        int count = 1, currSum = 0;
        for (int val : A)
        {
            currSum += val;

            if (currSum > mid)
            {
                currSum = val;
                count++;
            }
        }

        if (count > B)
            lo = mid + 1;
        else
            hi = mid;
    }

    return lo;
}

// 786. K-th Smallest Prime Fraction
/*
Approach: Binary Search, O(nlogn)
We do a binary search on the value of fraction
lo = 0, hi = 1
Since they are all prime fractions, so they are in range 0 to 1

Now if we consider a group of fractions, and each fraction in this group is <= mid
then, if the number of fractions in the group = k
Then there are only those k fractions that are <= mid
This means the max of that group is the kth smallest prime fraction
If our count > k, then we need to increase the allowed value, so check in right side
Else left side

Eg:
[1,2,3,5,7,13]

1/7 1/5 1/3 1/2
2/7 2/5 2/3
3/7 3/5
5/7

Now lo = 0, hi = 1
mid = (0 + 1)/2 = 0.5

We take all fractions <= 0.5
1/7 1/5 1/3 1/2
2/7 2/5
3/7

If we take this fractions in sorted form
1
*/
vector<int> kthSmallestPrimeFraction(vector<int> &arr, int k)
{
    int n = arr.size();

    double lo = 0.0, hi = 1.0;

    while (lo <= hi)
    {
        double mid = lo + (hi - lo) / 2;

        int j = n - 1;
        int num = 0, den = 1, count = 0;

        // find the count of fractions < mid
        for (int i = 0; i < n - 1; i++)
        {
            while (j > 0 && arr[i] > mid * arr[n - j])
                j--;

            count += j;

            // update the max fraction of current group
            if (j > 0 && arr[i] * den > num * arr[n - j])
            {
                num = arr[i];
                den = arr[n - j];
            }
        }

        // when count of fractions < mid is equal to k, then the max fraction is the answer
        if (count == k)
            return {num, den};
        else if (count > k)
            hi = mid - 0.000000001;
        else
            lo = mid + 0.000000001;
    }

    return {};
}

// 378. Kth Smallest Element in a Sorted Matrix
/*
Approach: O(nlog(max - min))
Use Binary Search to find the answer
The range is min value in matrix to max value in matrix
If the count of elements <= mid is less than k, then we need to increase mid,
So, we reject left side
Else reject right side
At the end when lo==hi, lo is the answer

In this way of binary search, we find the element which is equal to the answer
And if answer is not present we find the just greater element
At the end lo, hi, mid are all equal and we return lo as the answer
So, we can only get the answer count == k, when this happens we 3 cases:
1. ans = mid, in this case, we just keep searching in range lo to mid.
2. ans < mid, in this case also, we just keep searching in range lo to mid.
3. ans > mid, this is not possible, because if ans > mid, then count of elements <= mid would be less than k

So, we eventually mid will be equal to the ans.
Because the ans is always in lo to mid range, as we only move lo when the count < k (which is condition for 
answer cannot be in lo to mid range). So, since we decrease hi, whenever we find a possible answer, so, at
the end lo is equal to answer.

So, when the search stops, mid will definetely be present in the matrix, as we are finding the lower bound using
binary search. So, there cannot be any number present in the matrix that will be smaller than lo.

*/
int kthSmallest(vector<vector<int>> &matrix, int k)
{
    int n = matrix.size(), m = matrix[0].size();

    int lo = matrix[0][0], hi = matrix[n - 1][m - 1];

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        int j = m - 1, count = 0;

        // find the count of numbers <= mid in the matrix
        for (int i = 0; i < n; i++)
        {
            while (j >= 0 && matrix[i][j] > mid)
                j--;

            count += j + 1;
        }

        if (count < k)
            lo = mid + 1;
        else
            hi = mid;
    }

    return lo;
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
Approach 1: O(logn)
1. Find the pivot index of array
2. If target > last element of array, then it lies in left of pivot
   Else it lies in right of pivot
3. Use binary on that side, as that side will be completely sorted

Approach 2: O(logn)
We can also do it without finding the pivot first
We take lo = 0, hi = n-1
Then we take the mid

We have following cases:
1. If both the target and mid, lie on same side of pivot, then we have 2 cases:
    1. If nums[mid] < target: check on right side of mid
    2. Else check on left of mid
2. Else, we check which side of pivot target lies on:
    If target > nums[n-1] then we check on left of mid.
    Else we check on right of mid

Because if they both lie on same side of pivot i.e. left or right side of pivot,
then they will both lie in sorted order, as left and right side of pivot are sorted
So, in this case we can find which side to reject by comparing target and mid value

But if they lie in different sides, then to compare mid and target directly, we need
to know which side they both lie on. As if mid is in left side, then it will be greater then 
all elements on right of pivot. In this case if target < nums[mid], then we need to check 
in right. So, in case of different sides, we just check which side the target lies on,
And accordingly change the search space instead of comparing target and mid

For better visualization: https://leetcode.com/problems/search-in-rotated-sorted-array-ii/solution/
*/
// Approach 1:
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
// Approach 2:
int search(vector<int> &nums, int target)
{
    int n = nums.size();

    int lo = 0, hi = n - 1;

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        //target and mid are on the same side
        if ((target > nums[hi]) == (nums[mid] > nums[hi]))
        {
            if (nums[mid] < target)
                lo = mid + 1;
            else
                hi = mid;
        }
        // target on the left side
        else if (target > nums[n - 1])
            hi = mid;
        // target on the right side
        else
            lo = mid + 1;
    }

    return nums[lo] == target ? lo : -1;
}

// 81. Search in Rotated Sorted Array II
/*
Approach: O(n)
Using the 2nd approach of previous question.
Here as there are duplicates so, each time first check is mid element is equal to the last element
If it is equal then just reduce upper limit by 1 and move next iteration.
Rest is the same.
*/
bool search(vector<int> &nums, int target)
{
    int n = nums.size();

    int lo = 0, hi = n - 1;

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        // if mid of current search space == end of current search space
        if (nums[mid] == nums[hi])
        {
            hi--;
            continue;
        }

        //target and mid are on the same side
        if ((target > nums[hi]) == (nums[mid] > nums[hi]))
        {
            if (nums[mid] < target)
                lo = mid + 1;
            else
                hi = mid;
        }
        // target on the left side
        else if (target > nums[n - 1])
            hi = mid;
        // target on the right side
        else
            lo = mid + 1;
    }

    return nums[lo] == target;
}

// F1. Guess the K-th Zero (Easy version) (https://codeforces.com/problemset/problem/1520/F1#)
/*
Approach: O(logn)
lo = 1, hi = n
We print the range 0 to mid
The sum it returns would be equal to count of 1s in that range.
So, zeroCount  = total length of that range - oneCount in that range = hi - lo + 1 - oneCount

If this zeroCount < k, then we need to find the (k - zeroCount)th zero in mid + 1 to hi
As, zeroCount number of zeroes are already present in the left side, so the kth zero in the right side 
would be (k - zeroCount)th zero
Else we need to find the kth zero in the lo to mid

*/
void kthZero()
{
    int n, t;
    cin >> n >> t;

    while (t-- > 0)
    {
        int k;
        cin >> k;

        int lo = 1, hi = n;

        while (lo < hi)
        {
            int mid = lo + (hi - lo) / 2;

            cout << "? " << lo << " " << mid << endl;

            int oneCount;
            cin >> oneCount;

            int zeroCount = mid - lo + 1 - oneCount;

            if (zeroCount < k)
            {
                lo = mid + 1;
                k -= zeroCount;
            }
            else
                hi = mid;
        }

        cout << "! " << lo << endl;
    }
}

// 136. Single Number
/*
Approach 1: O(n)
Using XOR

Approach 2: O(nlogn), Binary Search
If in this array every number duplicate number was present adjacent to each other
Eg: 2 2 3 3 4 4 7 7 5 5 1 6 6

Here every element that is present twice is adjacent.
In this case we can use binary search.

Array: 2 2 3 3 4 4 7 7 5 5 1  6  6
Index: 0 1 2 3 4 5 6 7 8 9 10 11 12
If we look at the array now, the single element divides the array into 2 parts:
1. Left part: Here if an element is present at odd index, then its duplicate is at its previous index.
                And if it is at even index, then duplicate is at next index
2. Right part: Here it is reverse of left side
        Here if the element is present at odd index, then duplicate is at its next index
        And for even index, duplicate is at previous index

So, we start our binary search with
lo = 0, hi = n - 1
mid = (lo + hi) / 2

Now for the mid element we check the above condition to check which region we are in
If mid is in left side, then we update lo = mid + 1, to go to right side, and 
if mid is right side, then update hi = mid - 1, to go to left side
This way, when lo==hi, then mid element is the single element

Also, this same approach works if every element is duplicate, and one is 3 times
Because it is the same case, we can consider 2 out of 3 copies of that element as different elements

Using this approach when duplicates are not adjacent is O(nlogn) as will have to sort to bring them 
adjacent first or bring them adjacent some other way.
Then binary search is just O(logn)

However this approach is O(logn) so it will be better than XOR sum if elements are adjacent from starting.
*/
int singleNumber(vector<int> &nums)
{
    int n = nums.size();

    sort(nums.begin(), nums.end());

    // base cases, as we start lo = 1, hi = n - 2 to avoid conditions in while loop
    if (n == 1)
        return nums[0];
    if (n > 1 && nums[0] != nums[1])
        return nums[0];
    if (n > 1 && nums[n - 1] != nums[n - 2])
        return nums[n - 1];

    int lo = 1, hi = n - 2;

    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1])
            return nums[mid];
        else if (mid % 2 != 0) // mid is odd
        {
            if (nums[mid] == nums[mid - 1]) // move to right side
                lo = mid + 1;
            else // move to left side
                hi = mid - 1;
        }
        else // mid even
        {
            if (nums[mid] == nums[mid + 1]) // move to right side
                lo = mid + 1;
            else // move to left side
                hi = mid - 1;
        }
    }

    return -1;
}

// Sorting=================================================================================================

// 912. Sort an Array (Merge Sort)
void mergeSort(vector<int> &arr, int si, int ei)
{
    if (si == ei)
        return;

    int mid = si + (ei - si) / 2;

    // sort left half
    mergeSort(arr, si, mid);
    // sort right half
    mergeSort(arr, mid + 1, ei);

    // merge both sorted arrays
    merge(arr, si, mid, ei);
}
void merge(vector<int> &arr, int si, int mid, int ei)
{
    vector<int> res;

    int i = si, j = mid + 1;
    int n = mid + 1, m = ei + 1;

    while (i < n && j < m)
    {
        if (arr[i] < arr[j])
            res.push_back(arr[i++]);
        else
            res.push_back(arr[j++]);
    }

    while (i < n)
        res.push_back(arr[i++]);
    while (j < m)
        res.push_back(arr[j++]);

    for (int k = si; k <= ei; k++)
        arr[k] = res[k - si];
}
vector<int> sortArray(vector<int> &nums)
{
    mergeSort(nums, 0, nums.size() - 1);
    return nums;
}

// Count Inversions (https://practice.geeksforgeeks.org/problems/inversion-of-array-1587115620/1)
/*
Approach: O(nlogn)
Merge Sort
While merging the sorted arrays we count the inversions
*/
long long countInversions(long long *arr, long long si, long long ei)
{
    if (si == ei)
        return 0;

    long long mid = si + (ei - si) / 2;

    // sort left half
    long long leftCount = countInversions(arr, si, mid);
    // sort right half
    long long rightCount = countInversions(arr, mid + 1, ei);

    // merge both sorted arrays
    long long myCount = merge(arr, si, mid, ei);

    return leftCount + rightCount + myCount;
}
long long merge(long long *arr, long long si, long long mid, long ei)
{
    long long i = si, j = mid + 1;
    long long n = mid + 1, m = ei + 1;
    long long inversionCount = 0;

    vector<long long> res;

    while (i < n && j < m)
    {
        if (arr[i] <= arr[j])
        {
            res.push_back(arr[i++]);
        }
        else
        {
            inversionCount += n - i;
            res.push_back(arr[j++]);
        }
    }

    while (i < n)
        res.push_back(arr[i++]);
    while (j < m)
        res.push_back(arr[j++]);

    for (int k = si; k <= ei; k++)
        arr[k] = res[k - si];

    return inversionCount;
}
long long int inversionCount(long long arr[], long long N)
{
    // Your Code Here
    return countInversions(arr, 0, N - 1);
}

// Chocolate Distribution problem (https://practice.geeksforgeeks.org/problems/chocolate-distribution-problem3825/1)
/*
Approach: O(nlogn)

*/
long long findMinDiff(vector<long long> arr, long long n, long long m)
{
    sort(arr.begin(), arr.end());

    long long minDiff = arr[arr.size() - 1] - arr[0];

    for (long long i = m - 1; i < n; i++)
    {
        minDiff = min(minDiff, arr[i] - arr[i - m + 1]);
    }

    return minDiff;
}

// Counting Sort (https://practice.geeksforgeeks.org/problems/largest-even-number3821/1)
void countSort(vector<int> &nums)
{
    // find the min and max element of array
    int minNum = INT_MAX, maxNum = INT_MIN;
    for (int val : nums)
    {
        minNum = min(minNum, val);
        maxNum = max(maxNum, val);
    }

    // get the count of each element
    vector<int> freq(maxNum - minNum + 1);
    for (int val : nums)
        freq[val - minNum]++;

    // find prefix sum for each index in frequency array
    for (int i = 1; i < freq.size(); i++)
        freq[i] += freq[i - 1];

    // put all elements in sorted order in the result (stable sort)
    vector<int> res(nums.size());
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        int pos = freq[nums[i] - minNum] - 1;
        res[pos] = nums[i];
        freq[nums[i] - minNum]--;
    }

    // put the sorted array back into original array
    for (int i = 0; i < res.size(); i++)
        nums[i] = res[i];
}

// Radix Sort
void countSort(vector<int> &nums, int exp)
{
    // get the count of each element
    vector<int> freq(10);
    for (int val : nums)
        freq[(val / exp) % 10]++;

    // find prefix sum for each index in frequency array
    for (int i = 1; i < freq.size(); i++)
        freq[i] += freq[i - 1];

    // put all elements in sorted order in the result (stable sort)
    vector<int> res(nums.size());
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        int pos = freq[(nums[i] / exp) % 10] - 1;
        res[pos] = nums[i];
        freq[(nums[i] / exp) % 10]--;
    }

    // put the sorted array back into original array
    for (int i = 0; i < res.size(); i++)
        nums[i] = res[i];
}
void radixSort(vector<int> &nums)
{
    int maxVal = INT_MIN;

    for (int i = 0; i < nums.size(); i++)
        maxVal = max(maxVal, nums[i]);

    // call count sort for every digit right to left
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countSort(nums, exp);
}

// QuickSort
int partition(vector<int> &nums, int lo, int hi, int pivot)
{
    int i = lo, j = lo;

    // partition everything < pivot to its left, and > pivot to its right
    while (i <= hi)
    {
        if (nums[i] <= pivot)
        {
            swap(nums[i], nums[j]);
            i++;
            j++;
        }
        else
            i++;
    }

    // return pivot's index
    return j - 1;
}
void quickSort(vector<int> &nums, int lo, int hi)
{
    if (lo > hi)
        return;

    int pivot = nums[hi];
    int pidx = partition(nums, lo, hi, pivot);

    quickSort(nums, lo, pidx - 1);
    quickSort(nums, pidx + 1, hi);
}
vector<int> sortArray(vector<int> &nums)
{
    quickSort(nums, 0, nums.size() - 1);
    return nums;
}

// Bucket Sort
void bucketSort(vector<double> &arr)
{
    int n = arr.size();

    // 1) Create n empty buckets
    vector<float> b[n];

    // 2) Put array elements
    // in different buckets
    for (int i = 0; i < n; i++)
    {
        int bi = n * arr[i]; // Index in bucket
        b[bi].push_back(arr[i]);
    }

    // 3) Sort individual buckets
    for (int i = 0; i < n; i++)
        sort(b[i].begin(), b[i].end());

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}

// Extra=============================================================================
// 729. My Calendar I
/*
Approach 1: O(n^2)
Keep an array of intervals.
For every new interval, check if it overlaps with any existing interval.
This takes O(n) for each interval.

Approach 2: O(nlogn)
If we keep BST, then we can check if it overlaps in O(logn) and add in O(logn)
So, just use a ordered_set, and using binary search to find the <= interval for 
the current interval and check if the current interval overlaps with the next or previous 
interval.
For eg: 
the lower bound gives the equal or just greater element
So, like we searched [20,30], then we got [25,35]
Then this [20,30] interval can overlap with the just greater if currEnd > nextStart
OR, it can overlap with previous interval like [5,15] if currStart < prevEnd
*/
// Approach 1: O(n^2)
class MyCalendar
{
public:
    vector<pair<int, int>> intervals;
    MyCalendar()
    {
    }

    bool book(int start, int end)
    {
        int i = 0;

        while (i < intervals.size())
        {
            if (intervals[i].first <= start && start < intervals[i].second ||
                intervals[i].first < end && end < intervals[i].second ||
                intervals[i].first >= start && intervals[i].second <= end)
                return false;
            else if (end <= intervals[i].first)
            {
                intervals.insert(intervals.begin() + i, {start, end});
                return true;
            }
            else
                i++;
        }

        intervals.push_back({start, end});

        return true;
    }
};
// Approach 2: O(nlogn)
class MyCalendar
{
private:
    set<pair<int, int>> intervals;

public:
    MyCalendar()
    {
    }

    bool book(int start, int end)
    {
        auto itr = intervals.lower_bound({start, end});

        // current interval does not overlap with next interval
        if (itr != intervals.end() && itr->first < end)
            return false;

        // current interval does not overlap with previous interval
        if (itr != intervals.begin())
        {
            itr--;
            if (start < itr->second)
                return false;
        }

        intervals.insert({start, end});

        return true;
    }
};

// 731. My Calendar II
/*
Wrong Approach: O(nlogn)
We can keep 2 ordered sets: intervals, all overlaps that are double booked
Now for current interval, check if it overlaps with any present overlaps
If it is present, then that overlap is triple booked, so return false.
Else find if it overlaps with any interval and add the overlap in the overlaps set
as that overlap is now double booked. 
But the current interval can overlap with more that just the previous and next interval.
So, if we only check with those two, then overlap set wont have all the overlaps.
Eg:
Intervals: 42 61, 44 55, 58 73, 70 82, 60 70

i = 1
intervals: 42 61
overlaps:

i = 2
intervals: 42 61, 44 55
overlaps: 44 55

i = 3
intervals: 42 61, 44 55, 58 73
overlaps: 44 55

So, here we got 58, 73. The overlaps will be
[58 61] with [42 61]
But we will not check that because we are only checking with prev and next intervals
So, the logn approach does not work.
As the current interval can overlap with any interval before it
Because their end time may be after the current interval 
So, [58 61] wont be added to the overlaps.
So, if that interval gets booked again then it will return true.

i = 4
intervals: 42 61, 44 55, 58 73, 70 82
overlaps: 44 55, 70 73

i = 5
intervals: 42 61, 44 55, 58 73, 60, 70, 70 82
overlaps: 44 55, 60, 70, 70 73

As the [58 61] was not added so it got triple booked now.

Correct Approach: O(n^2)
For bookings > 1, it becomes same as Minimum Number of Platforms/Stations Required
We are basically saying that you cannot have more than 2 stations at the same time.
Here instead of maintaing 2 sorted arrays: start and end times
Just maintain an ordered map in which we will do +1 for start times and -1 for end times

So, for each booking just add the current interval
Then check if there are more than 2 bookings required at a time, then return false
Else return true

*/
// Wrong Approach
class MyCalendarTwo
{
private:
    set<pair<int, int>> intervals, overlaps;

public:
    MyCalendarTwo()
    {
    }

    bool book(int start, int end)
    {
        //check if it overlaps with any doubly booked intervals
        // then return false
        auto itr = overlaps.lower_bound({start, end});

        if (itr != overlaps.end() && itr->first < end)
            return false;
        if (itr != overlaps.begin())
        {
            itr--;
            if (start < itr->second)
                return false;
        }

        // check if it overlaps with any singly booked intervals,
        // then add the intersection in the doubly booked intervals
        auto itr = intervals.lower_bound({start, end});

        if (itr != intervals.end() && itr->first < end)
            overlaps.insert({max(start, itr->first), min(end, itr->second)});
        if (itr != intervals.begin())
        {
            itr--;
            if (start < itr->second)
                overlaps.insert({max(start, itr->first), min(end, itr->second)});
        }

        intervals.insert({start, end});

        return true;
    }
};
// Correct Approach
class MyCalendarTwo
{
private:
    map<int, int> bookings;

public:
    MyCalendarTwo()
    {
    }

    bool book(int start, int end)
    {
        // add current booking
        bookings[start]++;
        bookings[end]--;

        int currBookings = 0;
        for (auto ele : bookings)
        {
            currBookings += ele.second;

            // if bookings > 2, then remove current booking and return false
            if (currBookings > 2)
            {
                bookings[start]--;
                bookings[end]++;

                return false;
            }
        }

        return true;
    }
};

// 732. My Calendar III
/*
Approach: Time: O(n^2), Space: O(n)
Same as Minimum Number of Platforms/Stations required or Meeting Rooms II
Here instead of maintaing 2 sorted arrays: start and end times
Just maintain an ordered map in which we will do +1 for start times and -1 for end times
We use O(n) for each book() so for n calls it becomes O(n^2)
*/
class MyCalendarThree
{
private:
    map<int, int> bookings;

public:
    MyCalendarThree()
    {
    }

    int book(int start, int end)
    {
        // add current booking
        bookings[start]++;
        bookings[end]--;

        // find the max simultaneous bookings
        int res = 0, currBookings = 0;
        for (auto ele : bookings)
        {
            currBookings += ele.second;
            res = max(res, currBookings);
        }

        return res;
    }
};

// Sort an array of strings without converting them to integers(912. Sort an Array)
/*
Approach : O(nlogn)
We have to sort an array, where numbers are given as strings.
And we have sort this array without converting these strings to int.

In sorting strings they are sorted lexicographically.
So, they are compared at index 0, if they are equal then their index 1 is compared as so on.
So, to sort them in increasing order, we should first check if they have equal size, 
then directly use s1 < s2.
Otherwise if they have different sizes, then sort on basis of size
This approach works for +ve numbers.

For negative numbers, if both are negative then just sort them in opposite order
And if one of them is negative, then put the negative one first.

In Code, in lambda function we return s1 < s2 to sort in increasing order
So, basically if the function returns true, then the order of elements remains the same
So, if we want to place the -ve string first, and +ve string second then we need to check
if s1[0] == '-', this means the first string is -ve, so it is already in right order
So, in this case return true,
And if s2[0] == '-', then we want to change the order as we want s2 first, so return false.

Below question is to just test this approach, as this specific question is not given anywhere
to submit.
*/
vector<int> sortArray(vector<int> &nums)
{
    vector<string> arr;
    for (int val : nums)
        arr.push_back(to_string(val));

    // sort in increasing order
    sort(arr.begin(), arr.end(), [](string &s1, string &s2)
         {
             // both negative -> sort them in decreasing order
             if (s1[0] == '-' && s2[0] == '-')
             {
                 if (s1.size() == s2.size())
                     return s1 > s2;
                 else
                     return s1.size() > s2.size();
             }
             // any one negative -> put the negative one first
             else if (s1[0] == '-' || s2[0] == '-')
             {
                 return s1[0] == '-';
             }
             // both positive -> sort in incresing order
             else
             {
                 // if size is same, then sort lexicographically
                 if (s1.size() == s2.size())
                     return s1 < s2;
                 // if size is different, then smaller number comes first
                 else
                     return s1.size() < s2.size();
             }
         });

    for (int i = 0; i < arr.size(); i++)
    {
        nums[i] = stoi(arr[i]);
    }

    return nums;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
