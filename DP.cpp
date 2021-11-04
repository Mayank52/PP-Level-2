#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <unordered_set>

using namespace std;

void display(vector<vector<int>> &dp)
{
    for (int i = 0; i < dp.size(); i++)
    {
        for (int j = 0; j < dp[0].size(); j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

// LIS======================================================================================
// 300. Longest Increasing Subsequence
/*
Approach 1: O(n^2)
For each element we check every element before it that is smaller than current element
And find the max length by adding this element to the end of their subsequence
In this method we can use retracing to find the subsequence from the DP array

Approach 2: O(nlogn)
Instead of checking for all elements before current element
In the DP array we maintain the last element of the LIS of that length
Eg:
at index 2 we will have the smallest last element(greatest in that sequence as it is increasing sequence)
of an increasing sequence of length = 2

And for the current element we find the smallest element in DP array 
that is equal to or just greater than this element
And replace it with this element

So, basically, we find a sequence till now whose last element is > this element
So replacing that with this element is better
Like if we have 2 4 10
And this is 7
Then replacing 10 with 7 is better as now we can have 8, 9 after 7 which not be possible after 10
thus 7 can possibly give a longer sequence

At the end the ans is the size of DP array
But in this method we cannot find the actual subsequence for that answer
*/
// Approach 1: O(n^2)
int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();

    vector<int> dp(n, 1);
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
            if (nums[i] > nums[j])
                dp[i] = max(dp[i], dp[j] + 1);

        res = max(res, dp[i]);
    }

    return res;
}
// Approach 2: O(nlogn)
int lengthOfLIS(vector<int> &nums)
{
    vector<int> dp;

    for (int i = 0; i < nums.size(); i++)
    {
        // stl function to find smallest element equal to or just greater than current element
        // int idx = lower_bound(dp.begin(), dp.end(), nums[i]) - dp.begin();

        // binary search to find the smallest element equal to or just greater than current element
        int lo = 0, hi = dp.size();
        while (lo < hi)
        {
            int mid = lo + (hi - lo) / 2;

            if (nums[i] > dp[mid])
                lo = mid + 1;
            else // this handles <= case
                hi = mid;
        }

        if (lo == dp.size())
            dp.push_back(nums[i]);
        else
            dp[lo] = nums[i];
    }

    return dp.size();
}

// 673. Number of Longest Increasing Subsequence
int findNumberOfLIS(vector<int> &nums)
{
    int n = nums.size();

    vector<pair<int, int>> dp(n, {1, 1}); // { length, count of subseq with that length}
    int res = 0, count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
            {
                // if the val at j == val at i, then add the count of its increasing subseq to current element's count
                if (dp[i].first == dp[j].first + 1)
                    dp[i].second += dp[j].second;
                // else the count will be same as the element in whose subseq, this element is being added
                else if (dp[i].first < dp[j].first + 1)
                {
                    dp[i].first = dp[j].first + 1;
                    dp[i].second = dp[j].second;
                }
            }
        }

        // update the res if current element has longer subseq
        if (dp[i].first > res)
        {
            res = dp[i].first;
            count = dp[i].second;
        }
        // else if the lenght is same, then this count to the previous count to get the total count of this length
        else if (dp[i].first == res)
            count += dp[i].second;
    }

    return count;
}

// Building Bridges (SPOJ)(https://www.spoj.com/problems/BRDGHRD/)
/*
Approach: LIS O(nlogn)
Store both arrays in a single nx2 array
Then sort this array with respect to one bridge points i.e 0th index or 1st index
Then for the other bridge points find the LIS
This LIS is the answer
*/
void buildingBridges()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        vector<vector<int>> arr(n, vector<int>(2));

        for (int i = 0; i < n; i++)
            cin >> arr[i][0];
        for (int i = 0; i < n; i++)
            cin >> arr[i][1];

        sort(arr.begin(), arr.end());

        vector<int> dp;
        int res = 0;

        for (int i = 0; i < n; i++)
        {
            int lo = 0, hi = dp.size();
            while (lo < hi)
            {
                int mid = lo + (hi - lo) / 2;
                if (arr[i][1] < dp[mid])
                    hi = mid;
                else
                    lo = mid + 1;
            }

            if (lo == dp.size())
                dp.push_back(arr[i][1]);
            else
                dp[lo] = arr[i][1];
        }

        cout << dp.size() << '\n';
    }
}

// 354. Russian Doll Envelopes
/*
Approach: LIS
Sort the array on basis of increasing height and decreasing width
This way LIS wont add elements with increasing width and equal height to same subseq
Because the width of consecutive equal heights will be decreasing
Eg:
(3, 5), (4, 6), (4, 5), (4, 4)
Here as the height is equal to 4 for 3 consecutive
So, if width is also increasing then in LIS we will have to check for both height and width
But if we make width decreasing, then we only need to check for width

*/
// Approach 1: O(n^2)
int maxEnvelopes(vector<vector<int>> &envelopes)
{
    // sort only in increasing order
    sort(envelopes.begin(), envelopes.end());

    int n = envelopes.size();

    vector<int> dp(n, 1);
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
            // check for both width and height
            if (envelopes[i][1] > envelopes[j][1] && envelopes[i][0] > envelopes[j][0])
                dp[i] = max(dp[i], dp[j] + 1);

        res = max(res, dp[i]);
    }

    return res;
}
// Approach 1: O(nlogn)
int maxEnvelopes(vector<vector<int>> &envelopes)
{
    // sort in increasing order of height, and decreasing width for equal heights
    sort(envelopes.begin(), envelopes.end(), [](vector<int> &v1, vector<int> &v2)
         {
             if (v1[0] != v2[0])
                 return v1[0] < v2[0];
             else
                 return v1[1] > v2[1];
         });

    vector<int> dp;

    // LIS for just widths
    for (vector<int> &env : envelopes)
    {
        int lo = 0, hi = dp.size();

        while (lo < hi)
        {
            int mid = lo + (hi - lo) / 2;

            if (env[1] > dp[mid])
                lo = mid + 1;
            else
                hi = mid;
        }

        if (lo == dp.size())
            dp.push_back(env[1]);
        else
            dp[lo] = env[1];
    }

    return dp.size();
}

// Box Stacking (https://practice.geeksforgeeks.org/problems/box-stacking/1)
/*
Approach: LIS O(n ^ 2)
We will add all 6 combinations of {l, w, h} into an array
Here, we consider arr[0] = height, arr[1] = width, arr[2] = length

Then we do LIS for the length and width same as the russian doll envelope
And find the sequence with max height

Also, out of 6 combinations, we only need 3
We will make 3 combinations with l < w, and 3 with w < l
We can take either the ones with l < w or w < l
As these 2 can never stack on top of each other, so we only need 3 combinations
either of l < w or w < l.
*/
int maxHeight(int height[], int width[], int length[], int n)
{
    vector<vector<int>> arr;

    for (int i = 0; i < n; i++)
    {
        arr.push_back({height[i], min(width[i], length[i]), max(width[i], length[i])});
        arr.push_back({width[i], min(height[i], length[i]), max(height[i], length[i])});
        arr.push_back({length[i], min(width[i], height[i]), max(width[i], height[i])});
    }

    sort(arr.begin(), arr.end(), [](vector<int> &v1, vector<int> &v2)
         {
             if (v1[1] == v2[1])
                 return v1[2] > v2[2];
             else
                 return v1[1] < v2[1];
         });

    vector<int> dp(arr.size());
    int res = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        dp[i] = arr[i][0];
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[i][2] > arr[j][2])
                dp[i] = max(dp[i], dp[j] + arr[i][0]);
        }

        res = max(res, dp[i]);
    }

    return res;
}

// Minimum number of increasing subsequences
/*
Approach: LIS
https://cp-algorithms.com/sequences/longest_increasing_subsequence.html

Minimum number of increasing subsequences = length of longest decreasing subsequence

Explanation:
Every element in the longest decreasing subsequence will belong a seperate increasing subseq
As if they put in same group they will be in decreasing order

So, Minimum number of increasing subsequences = length of longest decreasing subsequence

*/
int minNumberofIncSubseq(vector<int> &nums)
{
    vector<int> dp;

    // LIS from the n - 1 to 0 index will be LDS from 0 to n - 1
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        // binary search to find the smallest element equal to or just greater than current element
        int lo = 0, hi = dp.size();
        while (lo < hi)
        {
            int mid = lo + (hi - lo) / 2;

            if (nums[i] > dp[mid])
                lo = mid + 1;
            else
                hi = mid;
        }

        if (lo == dp.size())
            dp.push_back(nums[i]);
        else
            dp[lo] = nums[i];
    }

    return dp.size();
}

// 1235. Maximum Profit in Job Scheduling
// Approach 1: O(n^2)
int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
{
    int n = startTime.size();

    vector<vector<int>> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = {startTime[i], endTime[i], profit[i]};

    sort(arr.begin(), arr.end());

    vector<int> dp(n);
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        dp[i] = arr[i][2];
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[i][0] >= arr[j][1])
                dp[i] = max(dp[i], dp[j] + arr[i][2]);
        }

        res = max(res, dp[i]);
    }

    return res;
}
// Approach 2: O(nlogn)
int lower_bound(vector<vector<int>> &arr, int lo, int x)
{
    int hi = arr.size() - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid][0] >= x)
            hi = mid - 1;
        else
            lo = mid + 1;
    }
    return lo;
}

int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
{
    int n = startTime.size();
    vector<int> dp(n, 0);

    vector<vector<int>> arr(n); //{start, end, profit}
    for (int i = 0; i < n; i++)
        arr[i] = {startTime[i], endTime[i], profit[i]};

    sort(arr.begin(), arr.end());

    int maxprofit = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int j = lower_bound(arr, i + 1, arr[i][1]);

        int lb = j == n ? 0 : dp[j];

        dp[i] = max(arr[i][2] + lb, maxprofit);

        maxprofit = max(maxprofit, dp[i]);
    }

    return maxprofit;
}

// Longest Bitonic Subsequence
/*
Approach: O(nlogn)
1. Find LIS (Left to Right)
2. Find LDS (Right to Left)

In LIS DP for each index i we have, longest increasing subsequence ending at i
In LDS DP for each index i we have, longest decreasing subsequence starting at i

Now iterate over these 2, and for each index find the longest bitonice subsequence
longestBitonicSubsequence = lis[i] + lds[i] - 1
lis[i] will give the increasing till i, lds[i] will give the longest decreasing from i,
in this ith index is counted twice, so we take lis[i] + lds[i] - 1
*/
int LongestBitonicSequence(vector<int> nums)
{
    int n = nums.size();

    // LIS
    vector<int> lis(n, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
                lis[i] = max(lis[i], lis[j] + 1);
        }
    }

    // LDS
    vector<int> lds(n, 1);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (nums[i] > nums[j])
                lds[i] = max(lds[i], lds[j] + 1);
        }
    }

    // Longest Bitonic Subsequence
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        res = max(res, lis[i] + lds[i] - 1);
    }

    return res;
}

// 1671. Minimum Number of Removals to Make Mountain Array
/*
Approach 1: O(n^2)
We have to find the Longest Bitonic Subsequence
But the peak element must have atleast one element on both its left and right
We cannot take a subsequence that is just increasing or decreasing.

Approach 2: O(nlogn)
Use nlogn approach for LIS and LDS
And maintain a prefix, suffix array to keep
prefix: max LIS till i
suffix: max LDS from i

Logic I am not sure
*/
// Approach 2: O(nlogn)
int minimumMountainRemovals(vector<int> &nums)
{
    int n = nums.size();

    // LIS
    vector<int> prefix(n), suffix(n);
    vector<int> dp;
    for (int i = 0; i < n; i++)
    {
        int idx = lower_bound(dp.begin(), dp.end(), nums[i]) - dp.begin();

        if (idx == dp.size())
            dp.push_back(nums[i]);
        else
            dp[idx] = nums[i];

        // update prefix[i] with max LIS till i, which is dp.size()
        prefix[i] = dp.size();
    }

    dp.clear();

    // LDS
    for (int i = n - 1; i >= 0; i--)
    {
        int idx = lower_bound(dp.begin(), dp.end(), nums[i]) - dp.begin();

        if (idx == dp.size())
            dp.push_back(nums[i]);
        else
            dp[idx] = nums[i];

        // update suffix[i] with max LDS starting from i, which is dp.size()
        suffix[i] = dp.size();
    }

    // Longest Bitonic Subsequence
    int maxBitonicLen = 0;
    for (int i = 1; i < n - 1; i++)
    {
        if (prefix[i] > 1 && suffix[i] > 1)
            maxBitonicLen = max(maxBitonicLen, prefix[i] + suffix[i] - 1);
    }

    return nums.size() - maxBitonicLen;
}
// Approach: O(n^2)
int minimumMountainRemovals(vector<int> &nums)
{
    int n = nums.size();

    // LIS
    vector<int> lis(n, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
                lis[i] = max(lis[i], lis[j] + 1);
        }
    }

    // LDS
    vector<int> lds(n, 1);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (nums[i] > nums[j])
                lds[i] = max(lds[i], lds[j] + 1);
        }
    }

    // Longest Bitonic Subsequence
    int maxBitonicLen = 0;
    for (int i = 1; i < n - 1; i++)
    {
        if (lis[i] > 1 && lds[i] > 1)
            maxBitonicLen = max(maxBitonicLen, lis[i] + lds[i] - 1);
    }

    return nums.size() - maxBitonicLen;
}

// Include/Exclude(P & C)================================================================================

// 514 · Paint Fence
/*
Approach: O(n)
Keep 2 counts: 
1. Number of ways to paint 2 fences with same color
2. Number of ways to paint 2 fences with different colkor

Number of ways to paint current fence:
1. Same as last fence: ways to paint last fence different color than its previous fence
As more than 2 fences cannot have same color. So, if we paint this fence same as last, then it will the same as painting 
last fence different than its previous fence.

2. Different than last fence: total ways to paint last fence * (k - 1)
To color, this fence different we can color it with k - 1  colors, i.e. every color except the one last
fence was painted with.
So, the count for this is the total ways to paint last fence * (k - 1)

Base Case:
For the first fence you can paint it with any of the k colors, so ways = k
For 2nd fence, to paint it same as last will be k
and to paint it different, for every paint we have k - 1 choices to paint different
So for k paints we have k * k - 1 choices.
*/
int numWays(int n, int k)
{
    // for 1st fence
    if (n == 1)
        return k;

    // for 2nd fence
    int sameCount = k;
    int diffCount = k * (k - 1);

    // every fence after that
    for (int i = 2; i < n; i++)
    {
        int a = sameCount, b = diffCount;

        // paint this fence same as last fence
        sameCount = b;

        // paint this fence different than last fence
        diffCount = (a + b) * (k - 1);
    }

    return sameCount + diffCount;
}

// Consecutive 1's not allowed
/*
Approach: O(n)
We keep track of 
1. Number of sequences ending with 1 = oneCount
1. Number of sequences ending with 0 = zeroCount

Now for current index, 
Number of ways to add 1 here = Number of ways to put a zero at previous index = zeroCount
Number of ways to add 0 here = We can add 0 after any sequence, so = oneCount + zeroCount

Eg:
1 2 3 4 5 6     : Idx
1 2 3 4 8 13    : lastZero
1 1 2 3 5 8     : lastOne
Ans: 13 + 8 = 21

This forms a fibonacci sequence: 0 1 1 2 3 5 8 13 21....
Here the number of ways to make a sequecne of length 1 = 2 (Either 0 or 1)
So in this case the sequence starts from n = 3 of fibonacci sequence

So, for the given n, we have to find the (n + 2)th number of the fibonacci sequence
As the nth zeroCount would be the ans

*/
long MOD = 1e9 + 7;
long long countStrings(int n)
{
    long long oneCount = 1;
    long long zeroCount = 1;

    for (int i = 1; i < n; i++)
    {
        long long a = oneCount, b = zeroCount;

        oneCount = b;
        zeroCount = (a % MOD + b % MOD) % MOD;
    }

    return (oneCount % MOD + zeroCount % MOD) % MOD;
}

// 509. Fibonacci Number (logn)
/*
Approach: O(logn)
Fibonacci Series: 0 1 1 2 3 5
If we have to find just the nth number in the fibonacci sequence, then it is possible to do it 
in O(logn).

The fibonacci sequence can be represented using the matrix:
M = 1 1
    1 0

nth number in the series is given by M^n
M^n = f(n+1) f(n)
      f(n)   f(n-1)
Eg: 
Find 4th Fibonacci Number
M^4:
M^2: 1 1 * 1 1 = 2 1
     1 0   1 0   1 1

M^4: 2 1 * 2 1 = 5 3
     1 1   1 1   3 2

So, (n+1)th = 5th = 5,
 nth = 4th = 3,
 (n-1)th = 3rd = 2


Now we can use Fast Exponentiation and matrix multiplication to find it is logn.
For Matrix multiplication of n*m and m*k, complexity is n*m*k
In our case we a matrix of 2x2, so complexity = 2*2*2 = 8
M^n will have O(8logn) = O(logn)
*/
vector<vector<int>> matrixMultiply(vector<vector<int>> &mat1, vector<vector<int>> &mat2)
{
    int n1 = mat1.size(), m1 = mat1[0].size();
    int n2 = mat2.size(), m2 = mat2[0].size();

    vector<vector<int>> res(n1, vector<int>(m2)); // 2 x 2

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            for (int r = 0, c = 0; r < n2 && c < m1; r++, c++)
            {
                res[i][j] += mat1[i][c] * mat2[r][j];
            }
        }
    }

    return res;
}
int fib(int n)
{
    vector<vector<int>> x{{1, 1}, {1, 0}};
    int y = n;

    vector<vector<int>> res{{1, 0}, {0, 1}}; // Identity Matrix

    while (y > 0)
    {
        if (y % 2 != 0)
        {
            res = matrixMultiply(res, x);
            y--;
        }

        x = matrixMultiply(x, x);
        y /= 2;
    }

    int ans = res[0][1];

    return ans;
}

// Count possible ways to construct buildings
/*
Approach: O(n)
This is same as consecutive 1's not allowed
If we construct building on plot, then it is a 1
And if we dont, then it is 0.

We just find ways to construct building on one side = n 
On the other side the count will be the same = n
Now total ways to construct on both sides = n * n
*/
int TotalWays(int n)
{
    // Code here
    long MOD = 1e9 + 7;
    long long oneCount = 1;
    long long zeroCount = 1;

    for (int i = 1; i < n; i++)
    {
        long long a = oneCount, b = zeroCount;

        oneCount = b;
        zeroCount = (a % MOD + b % MOD) % MOD;
    }

    int res = (oneCount % MOD + zeroCount % MOD) % MOD;
    res = (res % MOD * res % MOD) % MOD;

    return res;
}

// Catalan Numbers========================================================================================
/*
Catalan Numbers: https://cp-algorithms.web.app/combinatorics/catalan-numbers.html

The first few numbers Catalan numbers, Cn (starting from zero):
1,1,2,5,14,42,132,429,1430,…

C[0] = 1
C[1] = 1
C[2] = C[0]*C[1] + C[1]*C[0] = 1 + 1 = 2
C[3] = C[0]*C[2] + C[1]*C[1] + C[2]*C[0] = 2 + 1 + 2 = 5
And So on....

Formula:
C(n) = 2nCn/(n+1)

Complexity to get nth Catalan Number: 
Approach 1: DP, O(n^2)
Approach 2:
    Using the Formula: C(n) = 2nCn/(n+1)
    Time: O(n)

Applications:
The Catalan number Cn is the solution for:
1. Number of correct bracket sequence consisting of n opening and n closing brackets.
2. The number of rooted full binary trees with n+1 leaves (vertices are not numbered). 
A rooted binary tree is full if every vertex has either two children or no children.
3. The number of ways to completely parenthesize n+1 factors.
4. The number of triangulations of a convex polygon with n+2 sides 
(i.e. the number of partitions of polygon into disjoint triangles by using the diagonals).
5. The number of ways to connect the 2n points on a circle to form n disjoint chords.
6. The number of non-isomorphic full binary trees with n internal nodes (i.e. nodes having at least one son).
7. The number of monotonic lattice paths from point (0,0) to point (n,n) in a square lattice of size n×n, 
which do not pass above the main diagonal (i.e. connecting (0,0) to (n,n)).
8. Number of permutations of length n that can be stack sorted 
(i.e. it can be shown that the rearrangement is stack sorted if and only if there is no such index i<j<k, such that ak<ai<aj ).
9. The number of non-crossing partitions of a set of n elements.
10. The number of ways to cover the ladder 1…n using n rectangles 
(The ladder consists of n columns, where ith column has a height i).
*/
// https://practice.geeksforgeeks.org/problems/nth-catalan-number0817/1#
// Approach 1: O(n^2)
int findCatalan(int n)
{
    vector<int> cat(n + 1, 0);
    cat[0] = cat[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
            cat[i] += cat[j] * cat[i - 1 - j];
    }

    return cat[n];
}

// 96. Unique Binary Search Trees
/*
Approach: Catalan Number
Number of Unique BSTs with n keys = nth Catalan Number
Also, Number of Binary Trees with n keys = no. of unique BSTs * n!
Because the structure of all Binary Trees will be the same as the BSTs
But in each of those BSTs we can have n! permutations of keys to get a different binary tree
*/
int numTrees(int n)
{
    vector<int> cat(n + 1, 0);
    cat[0] = cat[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
            cat[i] += cat[j] * cat[i - 1 - j];
    }

    return cat[n];
}

// Path====================================================================================================

// 64. Minimum Path Sum
int minPathSum(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (i == n - 1 && j == m - 1)
            {
                dp[i][j] = grid[i][j];
                continue;
            }

            int cost = INT_MAX;
            if (i + 1 < n)
                cost = min(cost, dp[i + 1][j]);
            if (j + 1 < m)
                cost = min(cost, dp[i][j + 1]);

            dp[i][j] = cost + grid[i][j];
        }
    }

    return dp[0][0];
}

// 741. Cherry Pickup
/*
Approach: O(n^3) , O(n^3)
Wrong Approach: 
To Find the max path sum -> remove all cherries in that path -> find a second max path sum
This Fails on following case:
1 0 0 0 0
0 0 0 0 0
1 0 1 0 1
0 0 1 0 0
0 0 0 0 1

The first max path will find the middle path with 4 cherries, then remove them and it will become
0 0 0 0 0
0 0 0 0 0
1 0 0 0 1
0 0 0 0 0
0 0 0 0 0

Now second time it will find 1 cherry path
So, total 5 cherries

But we could have collected all cherries we took the following 2 paths
Path 1: 0,0(cherry) -> 0,1 -> 0,2 -> 1,2 -> 2,2(cherry) -> 2,3 -> 2,4(cherry) -> 3,4 -> 4,4(cherry) = (4 cherries)
Path 2: 0,0 -> 1,0 -> 2,0(cherry) -> 3,0 -> 3,1 -> 3,2(cherry) -> 3,3 -> 3,4 -> 4,4 = (2 cherries)
So, total 6 cherries

Correct Approach:
We move 2 people through the matrix at once.
And find the max path sum for both of them together for reaching the n-1,m-1 cell
To move through 2 paths at the same time with right and down moves allowed, we get 4 combinations
Right Right
Right Down
Down Down
Down Right

So at each step we find the max from these 4 options
Also row1 + col1 = row2 + col2 for each step
So, we only need 3 variables instead of 4
r1 + c1 = r2 + c2
so c2 = r1 + c1 - r2
*/
int pickup(vector<vector<int>> &grid, int row1, int col1, int row2, vector<vector<vector<int>>> &dp)
{
    int col2 = row1 + col1 - row2;

    // out of range indexes
    if (row1 >= grid.size() || col1 >= grid[0].size() || row2 >= grid.size() || col2 >= grid[0].size() || grid[row1][col1] == -1 || grid[row2][col2] == -1)
        return INT_MIN;

    // last cell
    if (row1 == grid.size() - 1 && col1 == grid[0].size() - 1 && row2 == grid.size() - 1 && col2 == grid[0].size() - 1)
        return dp[row1][col1][row2] = grid[row1][col1];

    if (dp[row1][col1][row2] != -1)
        return dp[row1][col1][row2];

    int myAns;
    // if both people are at same cell, then pick the cherry once
    if (row1 == row2 && col1 == col2)
        myAns = grid[row1][col1];
    // else pick the cherry in both cells
    else
        myAns = grid[row1][col1] + grid[row2][col2];

    // get the max of next 4 options
    int temp1 = pickup(grid, row1 + 1, col1, row2 + 1, dp);
    int temp2 = pickup(grid, row1 + 1, col1, row2, dp);
    int temp3 = pickup(grid, row1, col1 + 1, row2 + 1, dp);
    int temp4 = pickup(grid, row1, col1 + 1, row2, dp);

    int res = max(max(temp1, temp2), max(temp3, temp4));

    return dp[row1][col1][row2] = (res == INT_MIN) ? res : res + myAns;
}
int cherryPickup(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(n, -1)));
    int res = pickup(grid, 0, 0, 0, dp);

    return res == INT_MIN ? 0 : res;
}

// 1463. Cherry Pickup II
/*
Approach: O(n^3), O(n^3)
Same approach as Cherry Pickup
Just start one robot from 0,0 and second from 0, m-1
And since there are 3 moves allowed per robot, so total combonations = 9

Also we need to keep track of 3 variables: row, col1, col2
As in each move they have to move to next row. Only option is between -1, 0, 1 columns.
*/
int pickup(vector<vector<int>> &grid, int row, int col1, int col2, vector<vector<vector<int>>> &dp)
{
    // out of range indexes
    if (row >= grid.size() || col1 >= grid[0].size() || col1 < 0 || col2 >= grid[0].size() || col2 < 0)
        return -1;

    // last row
    if (row == grid.size() - 1)
    {
        if (col1 == col2)
            return dp[row][col1][col2] = grid[row][col1];
        else
            return dp[row][col1][col2] = grid[row][col1] + grid[row][col2];
    }

    if (dp[row][col1][col2] != -1)
        return dp[row][col1][col2];

    // include cherry for current cell of both robots
    int myAns;
    if (col1 == col2)
        myAns = grid[row][col1];
    else
        myAns = grid[row][col1] + grid[row][col2];

    // get max of next 9 options
    int maxRes = -1;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            maxRes = max(maxRes, pickup(grid, row + 1, col1 + i, col2 + j, dp));
        }
    }

    return dp[row][col1][col2] = (maxRes == -1) ? maxRes : maxRes + myAns;
}
int cherryPickup(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
    int res = pickup(grid, 0, 0, m - 1, dp);

    return res == -1 ? 0 : res;
}

// 174. Dungeon Game
/*
Approach: O(n^2), O(n^2)
For each cell, we find the min HP we need to stay above 0 from this cell to the end
So, we basically find the max path sum from that cell to the end to get the path in which we would need the least HP of our own.
Then we see if this cell itself requires some HP from our side or not.
Eg: the max path till end may be 10, but this cell itself is -3, so we still need to cover that -3 to reach this cell.

Eg:
-2   -3   3 
-5  -10   1
10   30  -5

For eg: in cell 1,1 with value 10, we have 2 options
1. 2,1(30): From this cell the min HP that will be reached till 2,2 will be 25(30 - 5).
2. 1,2(1): From this cell the min HP that will be reached will be -4 (1 - 5)

So, in 1,1 cell we can either take the path with 25 min HP, or -4 min Hp
Out of these 2 we choose the max, as we want to start with min extra HP, and the path that
requires the least HP to stay above 0 till the end is the one we choose 
Now we will take min of current cell and the currentCell + maxPathToEnd
Because we need to return the min HP it gets to in that path
So, -10 returns -10

And for cell 0,2(-3), the max HP from neighbors will be -1 from right cell.
And this itself is -3.
So, to stay above 0 throughout this path we need atleast -3 + -1 = -4           

*/
// Recursive
vector<vector<int>> dp;
int calculateMinimumHP(vector<vector<int>> &dungeon, int r, int c, vector<vector<bool>> &vis)
{
    int n = dungeon.size(), m = dungeon[0].size();

    if (r == n - 1 && c == m - 1)
        return dp[r][c] = dungeon[r][c];

    if (dp[r][c] != INT_MIN)
        return dp[r][c];

    vis[r][c] = true;

    int myAns = INT_MIN;

    int dir[2][2] = {{1, 0}, {0, 1}};

    // get the max path sum for neighbors
    for (int d = 0; d < 2; d++)
    {
        int x = r + dir[d][0];
        int y = c + dir[d][1];

        if (x >= 0 && y >= 0 && x < n && y < m && !vis[x][y])
        {
            int minHP = calculateMinimumHP(dungeon, x, y, vis);
            myAns = max(myAns, minHP);
        }
    }

    vis[r][c] = false;

    // return the min HP this cell reaches
    return dp[r][c] = min(dungeon[r][c], myAns + dungeon[r][c]);
}
int calculateMinimumHP(vector<vector<int>> &dungeon)
{
    int n = dungeon.size(), m = dungeon[0].size();

    dp.resize(n, vector<int>(m, INT_MIN));
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    int res = calculateMinimumHP(dungeon, 0, 0, vis);

    return res < 0 ? abs(res) + 1 : 1;
}
// Iterative
int calculateMinimumHP(vector<vector<int>> &dungeon)
{
    int n = dungeon.size(), m = dungeon[0].size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MIN));

    int dir[2][2] = {{1, 0}, {0, 1}};

    for (int r = n - 1; r >= 0; r--)
    {
        for (int c = m - 1; c >= 0; c--)
        {
            if (r == n - 1 && c == m - 1)
            {
                dp[r][c] = dungeon[r][c];
                continue;
            }

            // get the max hp of next two cells you can go to
            int myAns = max(dp[r + 1][c], dp[r][c + 1]);

            // find the min hp required to come to this cell
            dp[r][c] = min(dungeon[r][c], myAns + dungeon[r][c]);
        }
    }

    return dp[0][0] < 0 ? abs(dp[0][0]) + 1 : 1;
}

// Buy and Sell Stock=====================================================================================
/*
Approach: 
You have 3 parameters:
Day no.: i
No. of transactions completed: k
number of stocks in hand: 0 or 1 (Buying another stock if you have a stock in hand is not allowed)

Depending on these 3 parameters, we have 2 recurrence relations:
1. You have 0 stocks in hand at end of ith day: dp[i][k][0]
    If you have 0 stocks at the end of the day, then either you rested that day, or you sold a stock that day
    2 options: rest, sell
    If you rested today then profit today = dp[i][k][0] = profit of previous day for same number of transactions = dp[i-1][k][0]
    If you sold a stock today then profit today = dp[i][k][0]
    = profit of previous day for same number of transactions and one stock in hand which you would have sold today 
    = dp[i-1][k][1] + price of that stock today

    So, dp[i][k][0]= max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])

2. You have 1 stock in hand at end of ith day: dp[i][k][1]
    If you have 1 stock at the end of the day, then either you rested that day, or you bought a stock that day
    2 options: rest, buy
    If you rested today then profit today = dp[i][k][1] = profit of previous day for same number of transactions = dp[i-1][k][1]
    If you buy a stock today then profit today = dp[i][k][1]
    = profit of previous day for k-1 number of transactions and 0 stocks in hand
    = dp[i-1][k][1] - price of that stock today

    So, dp[i][k][1]= max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

Base Cases: 
dp[-1][k][0] = 0        // No day has passed, 0 stocks in hand
dp[i][0][0] = 0         // No transaction has taken place, 0 stock in hand
dp[-1][k][1] = -inf     // No day has passed, 1 stock in hand
dp[i][0][1] = -inf      // No transaction has taken place, 1 stock in hand

And 2 relations:
dp[i][k][0]= max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1]= max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

And the answer is at dp[n][K][0] i.e. at the end of last day with all K transactions completed and 0 stocks in hand
There is no point in having 1 stock in hand at the end, 
because if you cant sell it, then buying it just reduces the profit.

We count a transaction when we buy a stock.
Also, as every value of the ith day only depends on previous day, so, we dont need to store
the values of all days.
So, we need a n*k size dp to solve it.

*/

// 121. Best Time to Buy and Sell Stock
/*
Approach: O(n), O(1)
Here k = 1, as only transaction is allowed
We dont need to keep a dp array as only previous day is needed and k = 1

So, the 2 equations:
dp[i][k][0]= max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1]= max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])

Become:
dp[i][k][0]= max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1]= max(dp[i-1][k][1], 0 - prices[i])
As, k = 1, so, k - 1 = 0 and 
We have base case: dp[i][0][0] = 0
*/
int maxProfit(vector<int> &prices)
{
    int dp0 = 0;       //dp[i-1][k][0]
    int dp1 = INT_MIN; //dp[i-1][k][1]

    for (int price : prices)
    {
        // rest or sell today: dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
        dp0 = max(dp0, dp1 + price);

        // rest or buy today: dp[i][k][1] = max(dp[i-1][k][1], 0 - prices[i])
        dp1 = max(dp1, 0 - price);
    }

    return dp0;
}

// 122. Best Time to Buy and Sell Stock II
/*
Approach: O(n), O(1)
Infinite Transactions Allowed
So, k = inf so, just ignore k in the 2 equations:
dp[i][0]= max(dp[i-1][0], dp[i-1][1] + prices[i])
dp[i][1]= max(dp[i-1][1], dp[i-1][0] - prices[i])

*/
int maxProfit(vector<int> &prices)
{
    int dp0 = 0;       //dp[i-1][k][0]
    int dp1 = INT_MIN; //dp[i-1][k][1]

    for (int price : prices)
    {
        int temp = dp0;

        // rest or sell today: dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
        dp0 = max(dp0, dp1 + price);

        // rest or buy today: dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i])
        dp1 = max(dp1, temp - price);
    }

    return dp0;
}

// 714. Best Time to Buy and Sell Stock with Transaction Fee
/*
Approach: O(n), O(1)
Exactly same as Buy and Sell Stock 2
We just subtract a transaction fee for each transaction 
We are counting the transaction at time of buying, so just change the equation to:
dp[i][k][0]= max(dp[i-1][0], dp[i-1][1] + prices[i])
dp[i][k][1]= max(dp[i-1][1], dp[i-1][0] - prices[i] - fees)

*/
int maxProfit(vector<int> &prices, int fee)
{
    int dp0 = 0;       //dp[i-1][k][0]
    int dp1 = INT_MIN; //dp[i-1][k][1]

    for (int price : prices)
    {
        int temp = dp0;

        // rest or sell today: dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
        dp0 = max(dp0, dp1 + price);

        // rest or buy today: dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i] - fee)
        dp1 = max(dp1, temp - price - fee);
    }

    return dp0;
}

// 309. Best Time to Buy and Sell Stock with Cooldown
/*
Approach: O(n), O(1)
Exactly same as Buy and Sell Stock 2
But as there is a cooldown of 1 day, so while buying we have to check for (i - 2)th day instead of (i - 1) 
So, relation becomes:
dp[i][0]= max(dp[i-1][0], dp[i-1][1] + prices[i])
dp[i][1]= max(dp[i-1][1], dp[i-2][0] - prices[i])
*/
int maxProfit(vector<int> &prices)
{
    int dp0 = 0;       //dp[i-1][k][0]
    int dp1 = INT_MIN; //dp[i-1][k][1]
    int prevdp0 = 0;   //dp[i-2][k][0]

    for (int price : prices)
    {
        int temp = dp0;

        // rest or sell today: dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
        dp0 = max(dp0, dp1 + price);

        // rest or buy today: dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])
        dp1 = max(dp1, prevdp0 - price);

        prevdp0 = temp;
    }

    return dp0;
}

// 123. Best Time to Buy and Sell Stock III
/*
Approach: O(n), O(1)
2 transactions allowed, so, instead of just 2 variables we keep 4
dp[i][1][0], dp[i][1][1]
dp[i][2][0], dp[i][2][1]

So, equations are:
dp[i][1][0]= max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
dp[i][1][1]= max(dp[i-1][1][1], dp[i-1][0][0] - prices[i])

dp[i][2][0]= max(dp[i-1][2][0], dp[i-1][2][1] + prices[i])
dp[i][2][1]= max(dp[i-1][2][1], dp[i-1][1][0] - prices[i])

Also, if we keep the dp array, then we can calculate these 4 in any order.
But as we want O(1) space, we are using 4 variables
And these 4 variables are dependent on each other's values.
So, either we save their original values in before calculating, or we calculate in a particualar order:
1. dp[i][2][0]
2. dp[i][2][1]
3. dp[i][1][0]
4. dp[i][1][1]

We are starting with dp[i][2][0] as no other variable is dependent on it.
So, changing it does not affect them.
After that dp[i][2][1] as only dp[i][2][0] was dependent on it, and now it is done, so we can 
change this
In this way we can find the order to calculate them in.

*/
int maxProfit(vector<int> &prices)
{
    int dpi10 = 0;       //dp[i-1][1][0]
    int dpi11 = INT_MIN; //dp[i-1][1][1]
    int dpi20 = 0;       //dp[i-1][2][0]
    int dpi21 = INT_MIN; //dp[i-1][2][1]

    for (int price : prices)
    {
        dpi20 = max(dpi20, dpi21 + price);
        dpi21 = max(dpi21, dpi10 - price);
        dpi10 = max(dpi10, dpi11 + price);
        dpi11 = max(dpi11, -price);
    }

    return dpi20;
}

// 188. Best Time to Buy and Sell Stock IV
/*
Approach: O(n*k), O(k)
Similar to Buy and Sell Stock 3
Here the 2 equations are used directly as k transactions are allowed
And the order to fill the dp in is also observed from K = 2 transactions
We fill dp from
For each day we transactions in order k = K -> 0
And fill for dp0 first, then dp1

And as each ith only depends on i - 1
So, maintain only a k*2 dp 
2 for 0 or 1 stock in hand, and k for number of trasactions

And equations remain same as original:
dp[i][k][0]= max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
dp[i][k][1]= max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
*/
int maxProfit(int K, vector<int> &prices)
{
    vector<int> dpi0(K + 1, 0);       // 0 stock in hand, base case = 0
    vector<int> dpi1(K + 1, INT_MIN); // 1 stock in hand, base case = -inf

    for (int price : prices)
    {
        for (int k = K; k > 0; k--)
        {
            dpi0[k] = max(dpi0[k], dpi1[k] + price);
            dpi1[k] = max(dpi1[k], dpi0[k - 1] - price);
        }
    }

    return dpi0[K];
}

// Cut Type=====================================================================================================

// Matrix Chain Multiplication (https://practice.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1)
/*
Approach: Time: O(N^3), Space: O(N^2)

*/
// Recursive
int MCM_rec(vector<int> &arr, int si, int ei, vector<vector<int>> &dp)
{
    if (si + 1 == ei)
        return dp[si][ei] = 0;

    if (dp[si][ei] != -1)
        return dp[si][ei];

    int ans = 1e8;
    for (int cut = si + 1; cut < ei; cut++)
    {
        int leftCost = MCM_rec(arr, si, cut, dp);
        int rightCost = MCM_rec(arr, cut, ei, dp);

        int myCost = leftCost + arr[si] * arr[cut] * arr[ei] + rightCost;
        if (myCost < ans)
            ans = myCost;
    }

    return dp[si][ei] = ans;
}
// Iterative
int matrixMultiplication(int N, int arr[])
{
    vector<vector<int>> dp(N, vector<int>(N, INT_MAX));

    for (int gap = 1; gap < N; gap++)
    {
        for (int si = 0, ei = gap; ei < N; si++, ei++)
        {
            if (si + 1 == ei)
            {
                dp[si][ei] = 0;
                continue;
            }

            for (int cut = si + 1; cut < ei; cut++)
            {
                int leftCost = dp[si][cut];
                int rightCost = dp[cut][ei];

                int myCost = leftCost + arr[si] * arr[cut] * arr[ei] + rightCost;

                dp[si][ei] = min(dp[si][ei], myCost);
            }
        }
    }

    return dp[0][N - 1];
}

// 312. Burst Balloons
/*
Approach: O(N^3), O(N^2)
*/
// Recursive
int burstBallon(vector<int> &arr, int si, int ei, vector<vector<int>> &dp)
{
    if (dp[si][ei] != 0)
        return dp[si][ei];

    int lVal = si == 0 ? 1 : arr[si - 1];
    int rVal = (ei == arr.size() - 1) ? 1 : arr[ei + 1];

    int ans = 0;
    for (int cut = si; cut <= ei; cut++)
    {
        int leftTreeCost = (cut == si) ? 0 : burstBallon(arr, si, cut - 1, dp);
        int rightTreeCost = (cut == ei) ? 0 : burstBallon(arr, cut + 1, ei, dp);

        int myCost = leftTreeCost + lVal * arr[cut] * rVal + rightTreeCost;
        if (myCost > ans)
            ans = myCost;
    }

    return dp[si][ei] = ans;
}
// Iterative
int maxCoins(vector<int> &nums)
{
    int n = nums.size();

    vector<vector<int>> dp(n, vector<int>(n));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            int leftVal = (i == 0) ? 1 : nums[i - 1];
            int rightVal = (j == n - 1) ? 1 : nums[j + 1];

            for (int cut = i; cut <= j; cut++)
            {
                int leftCost = (cut == i) ? 0 : dp[i][cut - 1];
                int rightCost = (cut == j) ? 0 : dp[cut + 1][j];

                int myCost = leftCost + leftVal * nums[cut] * rightVal + rightCost;

                dp[i][j] = max(dp[i][j], myCost);
            }
        }
    }

    return dp[0][n - 1];
}

// 1039. Minimum Score Triangulation of Polygon
/*
Approach: O(n^3), O(n^2)
We start from gap 2
Because for gap 0 and 1, we will have only 2 vertices in the polygon
So, it wont be a triangle
Rest, just use the MCM method
And for the cuts we make cut at start + 1 to end - 1
Because if we make cut on start, then right side is the whole polygon and left side is nothing
Similarly for the cut at end

If we have to find the number of triangulations, it is given by Catalan number
Number of triangultions for n vertices is (n - 2)th Catalan Number

*/
int minScoreTriangulation(vector<int> &nums)
{
    int n = nums.size();

    vector<vector<int>> dp(n, vector<int>(n));

    for (int gap = 2; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            int myAns = INT_MAX;
            for (int cut = i + 1; cut < j; cut++)
            {
                int leftCost = dp[i][cut];
                int rightCost = dp[cut][j];

                int myCost = leftCost + nums[i] * nums[cut] * nums[j] + rightCost;

                myAns = min(myAns, myCost);
            }

            dp[i][j] = myAns;
        }
    }

    return dp[0][n - 1];
}

// 725 · Boolean Parenthesization
/*
Approach: O(n^3)
We keep 2 2D DPs
One for true count, and one for false count

For each cut, we check
leftCount = dp[i][cut]
rightCount = dp[cut + 1][j]


For each operator, using their Truth Table, we can find their current count of True and False values 
Case:
OR : 
    trueCount = (leftTrue * rightTrue) + (leftTrue * rightFalse) + (leftFalse * rightTrue)
    falseCount = (leftFalse * rightFalse)
AND:
    trueCount = (leftTrue * rightTrue)
    falseCount = (leftFalse * rightFalse) + (leftTrue * rightFalse) + (leftFalse * rightTrue)
XOR:
    trueCount = (leftTrue * rightFalse) + (leftFalse * rightTrue)
    falseCount = (leftFalse * rightFalse) + (leftTrue * rightTrue)

*/
int countParenth(string &symb, string &oper)
{
    int n = symb.size();

    vector<vector<int>> trueCount(n, vector<int>(n)), falseCount(n, vector<int>(n));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (i == j)
            {
                trueCount[i][j] = symb[i] == 'T' ? 1 : 0;
                falseCount[i][j] = symb[i] == 'F' ? 1 : 0;
                continue;
            }

            for (int cut = i; cut <= j; cut++)
            {
                int leftTrue = trueCount[i][cut];
                int rightTrue = (cut == n - 1) ? 0 : trueCount[cut + 1][j];
                int leftFalse = falseCount[i][cut];
                int rightFalse = (cut == n - 1) ? 0 : falseCount[cut + 1][j];

                if (oper[cut] == '|')
                {
                    trueCount[i][j] += (leftTrue * rightTrue) + (leftTrue * rightFalse) + (leftFalse * rightTrue);
                    falseCount[i][j] += (leftFalse * rightFalse);
                }
                else if (oper[cut] == '&')
                {
                    trueCount[i][j] += (leftTrue * rightTrue);
                    falseCount[i][j] += (leftFalse * rightFalse) + (leftTrue * rightFalse) + (leftFalse * rightTrue);
                }
                else
                {
                    trueCount[i][j] += (leftTrue * rightFalse) + (leftFalse * rightTrue);
                    falseCount[i][j] += (leftFalse * rightFalse) + (leftTrue * rightTrue);
                }
            }
        }
    }

    return trueCount[0][n - 1];
}

// Minimum and Maximum values of an expression with * and +
/*
Approach: O(n^3)
Similar to Boolean Parenthesization

In the DP, at each cell we store {minValue, maxValue}
For each cut, we get left and right min and max
leftMin = dp[i][cut][0];
rightMin = dp[cut + 1][j][0];
leftMax = dp[i][cut][1];
rightMax = dp[cut + 1][j][1];

Then, current min = leftMin * rightMin
And, current max = leftMax * rightMax

*/
vector<int> minAndMax(string expression)
{
    vector<int> nums;
    vector<char> oper;

    int i = 0;
    while (i < expression.size())
    {
        int num = 0;
        while (expression[i] - '0' >= 0 && expression[i] - '0' <= 9)
        {
            num = num * 10 + (expression[i] - '0');
            i++;
        }

        nums.push_back(num);
        oper.push_back(expression[i]);
        i++;
    }

    int n = nums.size();

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2)));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            // Base Case
            if (i == j)
            {
                dp[i][j] = {nums[i], nums[i]};
                continue;
            }

            int minAns = INT_MAX, maxAns = INT_MIN;
            for (int cut = i; cut < j; cut++)
            {
                // nothing on right, so left value is the only option
                if (cut == n - 1)
                {
                    minAns = dp[i][cut][0]; // leftMin
                    maxAns = dp[i][cut][1]; // leftMax
                    continue;
                }

                int leftMin = dp[i][cut][0];
                int rightMin = dp[cut + 1][j][0];
                int leftMax = dp[i][cut][1];
                int rightMax = dp[cut + 1][j][1];

                if (oper[cut] == '*')
                {
                    minAns = min(minAns, leftMin * rightMin);
                    maxAns = max(maxAns, leftMax * rightMax);
                }
                else
                {
                    minAns = min(minAns, leftMin + rightMin);
                    maxAns = max(maxAns, leftMax + rightMax);
                }
            }

            dp[i][j] = {minAns, maxAns};
        }
    }

    return dp[0][n - 1];
}

// 241. Different Ways to Add Parentheses
/*
Approach: O(n^3)
Same as previous question
At each cell in DP we keep an array of all possible values of the expression for that cell
Then for current cell, we get
All left Values * All right Values
*/
vector<int> diffWaysToCompute(string expression)
{
    vector<int> nums;
    vector<char> oper;

    int i = 0;
    while (i < expression.size())
    {
        int num = 0;
        while (expression[i] - '0' >= 0 && expression[i] - '0' <= 9)
        {
            num = num * 10 + (expression[i] - '0');
            i++;
        }

        nums.push_back(num);
        oper.push_back(expression[i]);
        i++;
    }

    int n = nums.size();

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            // Base Case
            if (i == j)
            {
                dp[i][j].push_back(nums[i]);
                continue;
            }
            for (int cut = i; cut < j; cut++)
            {
                for (int leftVal : dp[i][cut])
                {
                    // Nothing on right
                    if (cut == n - 1)
                    {
                        dp[i][j].push_back(leftVal);
                        continue;
                    }

                    for (int rightVal : dp[cut + 1][j])
                    {
                        if (oper[cut] == '+')
                            dp[i][j].push_back(leftVal + rightVal);
                        else if (oper[cut] == '*')
                            dp[i][j].push_back(leftVal * rightVal);
                        else
                            dp[i][j].push_back(leftVal - rightVal);
                    }
                }
            }
        }
    }

    return dp[0][n - 1];
}

// Optimal BST (https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-levelup/dynamic-programming/optimal-bst-official/ojquestion)
/*
Approach: O(n^3)
Cut Type Approach
We make cut on each  key one by one
This means that key is the root, and we need to find the cost for its left side 
that will make the left subtree, and its right side that will make the right subtree
Then as this becomes the root so everything on left and right goes down 1 level
So, their cost of searching will also increase by 1 for all frequencies
Eg:
Input:  keys[] = {10, 12, 20}, freq[] = {34, 8, 50}
There can be following possible BSTs
    10                12                 20         10              20
      \             /    \              /             \            /
      12          10     20           12               20         10  
        \                            /                 /           \
         20                        10                12             12  
     I               II             III             IV             V
Among all possible BSTs, cost of the fifth BST is minimum.  

Cost of searching of a key is = depth * frequency
So, if we make a cut at 12, and we have the cost of left i.e. 10, and right i.e. 20
Then when 12 becomes the root, all keys in left and right go down one level
And now, 
previous cost of 10 = 1 * 34
Now cost of 10 = 2 * 34 
Similarly for all other keys 
So, total increase in cost = sum of frequencies of left keys + current node's frequency + sum of frequency of right keys
= total frequency sum in range (L, R) both inclusive
L, R are the border that we are making the cuts in
*/
int optimalbst(vector<int> &keys, vector<int> &frequency)
{
    int n = keys.size();

    vector<vector<int>> dp(n, vector<int>(n));
    vector<int> prefixSum(n);

    prefixSum[0] = frequency[0];
    for (int i = 1; i < n; i++)
    {
        prefixSum[i] = prefixSum[i - 1] + frequency[i];
    }

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            int minCost = INT_MAX;
            for (int cut = i; cut <= j; cut++)
            {
                int leftCost = (cut == 0) ? 0 : dp[i][cut - 1];
                int rightCost = (cut == n - 1) ? 0 : dp[cut + 1][j];
                int myCost = prefixSum[j] - prefixSum[i] + frequency[i]; // sum of frequencies in range (i, j) both inclusive

                minCost = min(minCost, leftCost + myCost + rightCost);
            }

            dp[i][j] = minCost;
        }
    }

    return dp[0][n - 1];
}

// 1547. Minimum Cost to Cut a Stick
/*
Approach 1: O(n^3), O(n^2)
Using cut approach
We make a cut at each index from left + 1 to right - 1
leftCost = dp[i][cut]
rightCost = dp[cut][j]
myCost = right - left

When making the cut just check if we can make a cut at that index

Approach 2: O(k^3), O(k^2)
k = cuts.size()

Instead of checking for the whole length of rod, 
We check for the cuts array
Add 0, n into the cuts array so that it has the correct left and right
Then sort the cuts array
Now use the same method using the cuts array
So, here 
leftCost = 
*/
// Approach 1: O(n^3), O(n^2) (TLE)
int minCost(int n, vector<int> &cuts)
{
    // Given n is 0 based, n + 1 gives the actual length
    n++;

    vector<vector<int>> dp(n, vector<int>(n));
    unordered_set<int> cutSet;

    // add all cuts in a set, to make search O(1)
    for (int val : cuts)
        cutSet.insert(val);

    for (int gap = 2; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            int cost = INT_MAX;
            for (int cut = i + 1; cut < j; cut++)
            {
                // if we cannot make a cut at this index then skip it
                if (cutSet.find(cut) == cutSet.end())
                    continue;

                int leftCost = dp[i][cut];
                int rightCost = dp[cut][j];

                cost = min(cost, leftCost + j - i + rightCost);
            }

            dp[i][j] = cost == INT_MAX ? 0 : cost;
        }
    }

    return dp[0][n - 1];
}
// Approach 2: O(k^3), O(k^2) , k = cuts.size()
int minCost(int n, vector<int> &cuts)
{
    cuts.push_back(0);
    cuts.push_back(n);

    sort(cuts.begin(), cuts.end());

    int k = cuts.size();

    vector<vector<int>> dp(k, vector<int>(k));

    for (int gap = 2; gap < k; gap++)
    {
        for (int i = 0, j = gap; j < k; i++, j++)
        {
            int cost = INT_MAX;
            for (int cut = i + 1; cut < j; cut++)
            {
                int leftCost = dp[i][cut];
                int rightCost = dp[cut][j];

                cost = min(cost, leftCost + cuts[j] - cuts[i] + rightCost);
            }

            dp[i][j] = cost == INT_MAX ? 0 : cost;
        }
    }

    return dp[0][k - 1];
}

// 1130. Minimum Cost Tree From Leaf Values
/*
https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/discuss/478708/RZ-Summary-of-all-the-solutions-I-have-learned-from-Discuss-in-Python
Approach 1: DP, O(n^3)
This is the brute force.
For the current array, we make each index the pivot and divide the array into left and right parts.
Now the current node would be = max element if left part * max element in right part
And then make the call for the left and right parts.
This way at each step we divide the array into two halves and choose the pivot that gives the minimum cost.
The complexity of this would be O(n^4) as O(n^3) for the cut based DP and we find the max
in left and right of cut for every cut.
We can find the max for any range (i, j) in O(1) if we preprocess and keep a maxArray[i][j] for 
every range in O(n^2) time. And then overall complexity is O(n^3).

Approach 2: Greedy, O(n^2)
Above approach is kind of like brute force since we calculate and compare the results all possible pivots.
To achieve a better time complexity, one important observation is that when we build each level of the binary tree, 
it is the max left leaf node and max right lead node that are being used, 
so we would like to put big leaf nodes close to the root. As if you put them farther away, then they will 
add up on each level. So, we need to keep the greater values closer to the root.
Otherwise, taking the leaf node with max value in the array as an example, 
if its level is deep, for each level above it, its value will be used to calculate the non-leaf node value, 
which will result in a big total sum.

With above observation, the greedy approach is to find the smallest value in the array, 
use it and its smaller neighbor to build a non-leaf node, 
then we can safely delete it from the array since it has a smaller value than its neightbor so it will never be used again. 
Repeat this process until there is only one node left in the array (which means we cannot build a new level any more)

Approach 3: Monotonic Stack, O(n)
This approach is similar to greater element on right and maximum area under histogram.
We keep a strictly decreasing stack.
So, for the current element we resolve the top of stack until it is <= current element.
So, for that top its neighbor on right is current element and its neighbor on left is the element
just below it in the stack. So, the top element is min element that we found in greedy. Then 
we find its cost with smaller of its two neighbors i.e. current element and element below it in stack.
In this way keeping a decreasing stack we can find the answer in O(n).

*/
// Approach 1: DP, O(n^3)
// Memoization
int getMinCost(vector<int> &arr, int left, int right, vector<vector<int>> &dp, vector<vector<int>> &maxInRange)
{
    if (left >= right)
        return 0;

    if (dp[left][right] != -1)
        return dp[left][right];

    int minCost = INT_MAX;

    // make a cut at each index in current range and find the min cost
    for (int i = left; i < right; i++)
    {
        int myCost = maxInRange[left][i] * maxInRange[i + 1][right];
        int leftCost = getMinCost(arr, left, i, dp, maxInRange);
        int rightCost = getMinCost(arr, i + 1, right, dp, maxInRange);

        minCost = min(minCost, leftCost + myCost + rightCost);
    }

    return dp[left][right] = minCost;
}
int mctFromLeafValues(vector<int> &arr)
{
    int n = arr.size();

    vector<vector<int>> dp(n, vector<int>(n, -1));
    vector<vector<int>> maxInRange(n, vector<int>(n));

    // calculate the max in range for every (i,j)
    for (int i = 0; i < n; i++)
    {
        maxInRange[i][i] = arr[i];
        for (int j = i + 1; j < n; j++)
        {
            maxInRange[i][j] = max(maxInRange[i][j - 1], arr[j]);
        }
    }

    return getMinCost(arr, 0, n - 1, dp, maxInRange);
}
// Iterative
int mctFromLeafValues(vector<int> &arr)
{
    int n = arr.size();

    vector<vector<int>> dp(n, vector<int>(n));
    vector<vector<int>> maxInRange(n, vector<int>(n));

    // calculate the max in range for every (i,j)
    for (int i = 0; i < n; i++)
    {
        maxInRange[i][i] = arr[i];
        for (int j = i + 1; j < n; j++)
        {
            maxInRange[i][j] = max(maxInRange[i][j - 1], arr[j]);
        }
    }

    for (int gap = 1; gap < n; gap++)
    {
        for (int left = 0, right = gap; right < n; left++, right++)
        {
            int minCost = INT_MAX;

            // make a cut at each index in current range and find the min cost
            for (int i = left; i < right; i++)
            {
                int myCost = maxInRange[left][i] * maxInRange[i + 1][right];
                int leftCost = dp[left][i];
                int rightCost = dp[i + 1][right];

                minCost = min(minCost, leftCost + myCost + rightCost);
            }

            dp[left][right] = minCost;
        }
    }

    return dp[0][n - 1];
}
// Approach 2: Greedy, O(n^2)
int mctFromLeafValues(vector<int> &arr)
{
    int res = 0;

    while (arr.size() > 1)
    {
        // find the min value index
        int minIdx = min_element(arr.begin(), arr.end()) - arr.begin();

        // from its two neighbors, use the smaller one
        if (minIdx > 0 && minIdx < arr.size() - 1)
            res += arr[minIdx] * min(arr[minIdx - 1], arr[minIdx + 1]);
        else
            res += arr[minIdx] * (minIdx == 0 ? arr[minIdx + 1] : arr[minIdx - 1]);

        // remove the minIdx element from array
        arr.erase(arr.begin() + minIdx);
    }

    return res;
}
// Approach 3: Monotonic Stack,O(n)
int mctFromLeafValues(vector<int> &arr)
{
    stack<int> st;
    st.push(-1);

    int res = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        while (st.top() != -1 && arr[st.top()] < arr[i])
        {
            int mid = st.top();
            st.pop();

            res += st.top() == -1 ? arr[mid] * arr[i] : arr[mid] * min(arr[st.top()], arr[i]);
        }

        st.push(i);
    }

    while (st.top() != -1)
    {
        int mid = st.top();
        st.pop();

        if (st.top() != -1)
            res += arr[mid] * arr[st.top()];
    }

    return res;
}

// Strings====================================================================================================

// 1143. Longest Common Subsequence
int longestCommonSubsequence(string text1, string text2)
{
    int n = text1.size(), m = text2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (text1[i] == text2[j])
                dp[i][j] = dp[i + 1][j + 1] + 1;
            else
                dp[i][j] = max(dp[i][j + 1], dp[i + 1][j]);
        }
    }

    return dp[0][0];
}

// LCS of three strings (https://practice.geeksforgeeks.org/problems/lcs-of-three-strings0028/1)
/*
Approach: O(n^3), O(n^3)
Same as LCS
As there are 3 strings so take 3D DP and compare 3 strings instead of 2.
*/
int LCSof3(string A, string B, string C, int n1, int n2, int n3)
{
    vector<vector<vector<int>>> dp(n1 + 1, vector<vector<int>>(n2 + 1, vector<int>(n3 + 1)));

    for (int i = n1 - 1; i >= 0; i--)
    {
        for (int j = n2 - 1; j >= 0; j--)
        {
            for (int k = n3 - 1; k >= 0; k--)
            {
                if (A[i] == B[j] && B[j] == C[k])
                    dp[i][j][k] = dp[i + 1][j + 1][k + 1] + 1;
                else
                    dp[i][j][k] = max(dp[i + 1][j][k], max(dp[i][j + 1][k], dp[i][j][k + 1]));
            }
        }
    }

    return dp[0][0][0];
}

// 516. Longest Palindromic Subsequence
int longestPalindromeSubseq(string s)
{
    int n = s.size();

    vector<vector<int>> dp(n, vector<int>(n));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (i > j)
                continue;

            if (i == j)
            {
                dp[i][j] = 1;
                continue;
            }

            if (s[i] == s[j])
                dp[i][j] = dp[i + 1][j - 1] + 2;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }

    return dp[0][n - 1];
}

// 647. Palindromic Substrings
/*
Approach 1: O(n^2), O(n^2)
We do like in LPS
For every i, j, the number of palindromes = 
palindromes in (i, j - 1) + palindromes in (i + 1, j) - palindromes in (i + 1, j - 1)
Basically for i, j we take a union of strings
1. Excluding i: (i + 1, j)
2. Excluding j: (i, j - 1)

And on they both include (i + 1, j - 1)
So, it gets counted twice so, subtract count of (i + 1, j - 1)

Also, when we add the characters at i, j we, may get a new palindrome if (i + 1, j - 1) is
also a palindrome. So, we preprocess and another 2D boolean DP, which stores if each i,j 
is a palindrome.

Base Case:
1. For single characters count is always 1
2. For 2 characters:
    Eg: aa, count is 3, as we have a, a, aa as palindromes
    Eg: ab, count is 2, as we have a, b as palindromes
    So, for 2 characters if they are equal than count is 3 else 2

Eg: baaab
i = 0, j = 4
So, i and j are at leftmost and rightmost index
Here if s[i] == s[j] , then count = count(baaa) + count(aaab) - count(aaa)
Also, as aaa itself is a palindrome, so adding the b,b on i,j we get a new palindrome so
count = count(baaa) + count(aaab) - count(aaa) + 1

Approach 2: O(n^2), O(1) Space
From Leetcode Discuss Section:
Idea is go to each index and extend until it is a palindrome

A very easy explanation with an example
Lets take a string "aabaa"

Step 1: Start a for loop to point at every single character from where we will trace the palindrome string.
checkPalindrome(s,i,i); //To check the palindrome of odd length palindromic sub-string
checkPalindrome(s,i,i+1); //To check the palindrome of even length palindromic sub-string

Step 2: From each character of the string, we will keep checking if the sub-string is a palindrome and increment the palindrome count. 
To check the palindrome, keep checking the left and right of the character if it is same or not.

Eg: aabaa
First Loop:
i = 0
Palindrome: a (Count=1)
Palindrome: aa (Count=2)

Second Loop:
i = 1
Palindrome: a (Count=3)
Palindrome: No Palindrome

Third Loop:
i = 2
Palindrome: b,aba,aabaa (Count=6)
Palindrome: No Palindrome

Fourth Loop:
i = 3
Palindrome: a (Count=7)
Palindrome: aa (Count=8)

Count = 9 (For the last character)

*/
int countSubstrings(string s)
{
    int n = s.size();

    vector<vector<int>> dp(n, vector<int>(n));
    vector<vector<bool>> isPalindrome(n, vector<bool>(n, true));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            // Single Characters
            if (i == j)
            {
                isPalindrome[i][j] = true;
                continue;
            }
            // Only 2 characters
            if (i + 1 == j)
            {
                if (s[i] == s[j])
                    isPalindrome[i][j] = true;
                else
                    isPalindrome[i][j] = false;

                continue;
            }

            if (s[i] == s[j])
                isPalindrome[i][j] = isPalindrome[i + 1][j - 1];
            else
                isPalindrome[i][j] = false;
        }
    }

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            // Single Characters
            if (i == j)
            {
                dp[i][j] = 1;
                continue;
            }
            // Only 2 characters
            if (i + 1 == j)
            {
                if (s[i] == s[j])
                    dp[i][j] = 3;
                else
                    dp[i][j] = 2;

                continue;
            }

            // if equal and middle is a palindrome
            if (s[i] == s[j] && isPalindrome[i][j])
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + 1;
            else
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
        }
    }

    display(dp);

    return dp[0][n - 1];
}
// Approach 2: O(n^2), O(1)
int countSubstrings(string s)
{
    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        count += extractPalindrome(s, i, i);     //odd length
        count += extractPalindrome(s, i, i + 1); //even length
    }
    return count;
}
int extractPalindrome(string s, int left, int right)
{
    int count = 0;
    while (left >= 0 && right < s.size() && s[left] == s[right])
    {
        left--;
        right++;
        count++;
    }
    return count;
}

// 132. Palindrome Partitioning II
/*
Approach 1: Cut Type O(n^3)
First make a 2D isPalindrome DP
Then using Cut type approach, for each substring, make cuts and for each cut
leftCost = dp[i][cut] 
rightCost = dp[cut + 1][j]
totalCost = leftCost + 1 + rightCost
We added 1 as we are making a cut ourselves as well at the cut index


Approach 2: O(n^2)
We can preprocess
Then we can just keep a 1D DP
For each cut if the right side is not a palindrome then we dont need to calculate the cost for that cut
As that would already have been calculated in some other part
Eg:
a | baccdbd     No
ab | accdbd     No
aba | ccdbd     No
abac | cdbd     No
abacc | dbd     Yes
abaccd | bd     No
abaccdb | d     Yes

Like in abac | cdbd, on right side we have cdbd, which is not a palindrome
So, we would make cuts in it such that its left and right sides are palindromes
Now, after making those cuts, the right side would have become a palindrome and we
would get the case we have already calculated
Like in this case
cdbd -> cdb | b is the only cut with right a palindrome
So, the total string would become
abac | cdbd  -> abaccdb | d
which is already done

So, for any cut where right side is not a palindrome we dont need to check
So, just keep a 1D DP, here for each i, make a cut everywhere b/w 0 and i, and cost is
leftCost = dp[cut] 
rightCost = 0 as it is palindrome
totalCost = leftCost + 1 + rightCost

Approach 3: O(n^2), O(n)
Similar to 647. Palindrome Substrings
For each index i, we extend left and right indexes until string left...right is a palindrome
And while extending, for each left...right,
Cuts for (right + 1) = cuts for (left - 1) + 1, because left...right is already a palindrome so 0 cuts for that.

We do this for both odd and even length palindromes.
Initial values of cuts for all indexes is i - 1
dp[i] is storing the cuts required till i - 1.

*/
// Approach 2: Time: O(n^2), Space: O(n^2)
int minCut(string s)
{
    int n = s.size();

    // make the isPalindrome DP, for the string
    vector<vector<bool>> isPalindrome(n, vector<bool>(n, true));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            // Single Characters
            if (i == j)
            {
                isPalindrome[i][j] = true;
                continue;
            }
            // Only 2 characters
            if (i + 1 == j)
            {
                if (s[i] == s[j])
                    isPalindrome[i][j] = true;
                else
                    isPalindrome[i][j] = false;

                continue;
            }

            if (s[i] == s[j])
                isPalindrome[i][j] = isPalindrome[i + 1][j - 1];
            else
                isPalindrome[i][j] = false;
        }
    }

    vector<int> dp(n);
    for (int i = 0; i < n; i++)
    {
        dp[i] = i;

        // if 0 to i is a palindrome, then cuts = 0
        if (isPalindrome[0][i])
        {
            dp[i] = 0;
            continue;
        }

        // else make cuts between 0 to i
        for (int cut = 0; cut < i; cut++)
        {
            // if right side is not a palindrome, then skip
            if (!isPalindrome[cut + 1][i])
                continue;

            dp[i] = min(dp[i], dp[cut] + 1);
        }
    }

    return dp[n - 1];
}
// Approach 3: Time: O(n^2), Space: O(n)
int minCut(string s)
{
    int n = s.size();

    vector<int> dp(n + 1);

    // Max cuts for index i, can be i - 1
    for (int i = 0; i <= n; i++)
        dp[i] = i - 1;

    for (int i = 0; i < n; i++)
    {
        // Odd Length Palindrome
        int left = i, right = i;
        while (left >= 0 && right < n && s[left] == s[right])
        {
            dp[right + 1] = min(dp[right + 1], dp[left] + 1);
            left--;
            right++;
        }

        // Even Length Palindrome
        left = i, right = i + 1;
        while (left >= 0 && right < n && s[left] == s[right])
        {
            dp[right + 1] = min(dp[right + 1], dp[left] + 1);
            left--;
            right++;
        }
    }

    return dp[n];
}

// Count All Palindromic Subsequence in a given String (https://practice.geeksforgeeks.org/problems/count-palindromic-subsequences/1)
/*
Approach: O(n^2)

If we consider:
A = count of (i + 1, j)
B = count of (i, j -1)
C = count of (i + 1, j - 1)
Cases:
a[i] == a[j]
    We take A + B, and remove their intersection C.
    Now as a[i] == a[j], so adding these two to all palindromic subsequences in (i + 1, j - 1) gives a new palindrome
    So, we get count(i + 1, j - 1) = C new ones. Also a[i] and a[j] together also make a new palindrome as they are equal.
    So, dp[i][j] = (A + B - C) + (C + 1) = A + B + 1

a[i] != a[j]:
    Just take A + B and remove the intersection C. We dont get any new palindromes
    dp[i][j] = A + B - C

We dont count a[i], a[j] as new as they would have been counted already in start of A, and end of B.

*/
long long int countPS(string s)
{
    int n = s.size();
    long MOD = 1e9 + 7;

    vector<vector<long long>> dp(n, vector<long long>(n));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (i == j)
            {
                dp[i][j] = 1;
                continue;
            }
            if (i + 1 == j)
            {
                if (s[i] == s[j])
                    dp[i][j] = 3;
                else
                    dp[i][j] = 2;

                continue;
            }

            if (s[i] == s[j])
                dp[i][j] = ((dp[i + 1][j] % MOD + dp[i][j - 1] % MOD) % MOD + 1) % MOD;
            else
                dp[i][j] = ((dp[i + 1][j] % MOD + dp[i][j - 1] % MOD) % MOD - dp[i + 1][j - 1] % MOD + MOD) % MOD;
        }
    }

    return dp[0][n - 1];
}

// 730. Count Different Palindromic Subsequences
/*
Approach: O(n^3)
It is similar to count different palindromic subsequences
But here we dont want duplicates

A = count of (i + 1, j)
B = count of (i, j -1)
C = count of (i + 1, j - 1)

So, condition of

s[i] == s[j] changes:
1. There are no occurences of s[i] in the middle string C
    In this case, as ith index is the first time this character has occured, so adding s[i] to 
    (i+1, j-1) string wont give any new palindromes, same with adding s[j] to the middle.
    So, the number of palindromes in A, B are equal to C because of this reason.
    So, the relation = (A + B - C) + C + 1 = A + B + 1
    changes to = C + C + 2
    because A = C, B = C
    And the character at s[i], s[j] can now give 2 palindromes: s[i], s[i]+s[j]
    Eg: acddca
    i, j are at leftmost and rightmost. Since there are no a's in the middle string.
    So, a,a themselves will give 2 palindromes: a, aa
    and rest are the palindromes in A, B of the string which are equal to C
    So, dp[i][j] = 2*dp[i+1][j-1] + 2
2. Count of s[i] in middle string = 1
    In this case everything is same as 1st case. Except instead of +2 we have +1
    as s[i] is present in middle string so it was already counted there. Now we only count s[i]+s[j]
    Eg: acdadca
    So here we only count aa as new because a would have been counted in middle already
    So, dp[i][j] = 2*dp[i+1][j-1] + 1
3. Count of s[i] in middle string >= 2
    In this case, we will get duplicates for every subsequence that already has s[i]s[j] at each leftmost and rightmost position
    Eg: abadaccadaba
    So, now if i = 4, j = 7 which is acca. Here we counted acca
    And now when we come to i = 0, j = 11, i.e. whole string abadaccadaba
    Then since we are taking subsequences we will count the acca again with the new a's
    This will lead to duplicates: one in the middle 'acca' and other is the middle 'cc' with the a0 and a11
    So, we find the position of the leftmost and rightmost s[i] in the middle string and subtract its palindrome count from the answer
    Eg, in abadaccadaba we will subtract d[2][9] to remove the duplicates
    And the a, aa would have been counted in the middle string already
    So, dp[i][j] = 2*dp[i+1][j-1] - dp[left+1][right-1]

s[i] != s[j] remains the same

*/
int countPalindromicSubsequences(string s)
{
    int n = s.size();
    long MOD = 1e9 + 7;

    vector<vector<long>> dp(n, vector<long>(n));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (i == j)
            {
                dp[i][j] = 1;
                continue;
            }

            if (s[i] == s[j])
            {
                int left = i + 1, right = j - 1;

                while (left <= right && s[left] != s[j])
                    left++;
                while (left <= right && s[right] != s[j])
                    right--;

                if (left > right) // count of s[i] in i+1, j-1 = 0
                    dp[i][j] = dp[i + 1][j - 1] * 2 + 2;
                else if (left == right) // count of s[i] in i+1, j-1 = 1
                    dp[i][j] = dp[i + 1][j - 1] * 2 + 1;
                else // count of s[i] in i+1, j-1 >= 2
                    dp[i][j] = dp[i + 1][j - 1] * 2 - dp[left + 1][right - 1];
            }
            else
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];

            // instead of taking mod in every line, just do this
            dp[i][j] = dp[i][j] < 0 ? dp[i][j] + MOD : dp[i][j] % MOD;
        }
    }

    return dp[0][n - 1];
}

// 115. Distinct Subsequences
// Memoization
vector<vector<int>> dp;
int numDistinct(string &s, string &t, int i, int j)
{
    if (j == t.size())
        return dp[i][j] = 1;

    if (i == s.size())
        return dp[i][j] = 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int count = 0;
    if (s[i] == t[j])
        count += numDistinct(s, t, i + 1, j + 1);

    count += numDistinct(s, t, i + 1, j);

    return dp[i][j] = count;
}
int numDistinct(string s, string t)
{
    int n = s.size(), m = t.size();

    dp.resize(n + 1, vector<int>(m + 1, -1));

    return numDistinct(s, t, 0, 0);
}
// Iterative (Not Complete)
int numDistinct(string s, string t)
{
    int n = s.size(), m = t.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (j == 0)
            {
                dp[i][j] = 1;
                continue;
            }

            if (j > i)
            {
                dp[i][j] = 0;
                continue;
            }

            if (s[i - 1] == t[j - 1])
                dp[i][j] += dp[i - 1][j - 1];

            dp[i][j] += dp[i - 1][j];
        }
    }

    return dp[n][m];
}

// 940. Distinct Subsequences II
/*
Approach: O(n)
Eg:
abca
So, suppose we have all the subsequences of ca = a,c,ca
Now for b, we will have all the previous subsequences + we put b infront of all of them
So total = 2 * subsequences of ca

Now for abca, a repeats so it will get double counts for every subsequence infront of which a was already added
So, for eg: abacde
So, the a at index 2 would have added itself infront of all subseq of cde
Now for a at index 0, we have 2 * count(bacde) - count(cde) because those would already have been counted with previous a.
Also, when the character occurs the first time, then count +1 for that single character
Eg: for a at index 2, add 1 for 'a' subseq, and for every other a, we wont do +1 as then it will generate duplicates
So, For an index i, the number of distinct subsequences =
dp[i] = 2 * dp[i + 1] - dp[last position of ith char + 1]

Also dp[i] only depends on i + 1, so just keep a variable with previous answer,
and for dp[last position of ith char + 1], store it in the last position array itself
*/
// Approach 1: Time: O(n), Space: O(n)
int distinctSubseqII(string s)
{
    int n = s.size();
    long MOD = 1e9 + 7;

    vector<int> dp(n + 1);
    vector<int> prevPos(26, -1);

    for (int i = n - 1; i >= 0; i--)
    {
        dp[i] = 2 * dp[i + 1];

        if (prevPos[s[i] - 'a'] == -1) // first occurence
            dp[i]++;
        else // repeated occurences
            dp[i] -= dp[prevPos[s[i] - 'a'] + 1];

        // taking MOD
        if (dp[i] < 0)
            dp[i] += MOD;
        else
            dp[i] %= MOD;

        // update last position of ith character
        prevPos[s[i] - 'a'] = i;
    }

    return dp[0];
}
// Approach 1 with O(1) space
int distinctSubseqII(string s)
{
    int n = s.size();
    long MOD = 1e9 + 7;

    int count = 0;
    vector<int> prevPos(26, -1);

    for (int i = n - 1; i >= 0; i--)
    {
        // save the ans for i + 1
        int prevAns = count;

        count = 2 * count;

        if (prevPos[s[i] - 'a'] == -1) // first occurence
            count++;
        else // repeated occurences
            count -= prevPos[s[i] - 'a'];

        // taking MOD
        if (count < 0)
            count += MOD;
        else
            count %= MOD;

        // the answer of i + 1 becomes the duplicate count for i which we need to remove in its next occurence
        prevPos[s[i] - 'a'] = prevAns;
    }

    return count;
}

// 734 · Number of Subsequences of Form a^i b^j c^k (Lintcode)
/*
Approach: O(n)
We make 3 1D DPs 
aCount: ith index shows number of subsequences till now that end with 'a'
bCount: ith index shows number of subsequences till now that end with 'b'
cCount: ith index shows number of subsequences till now that end with 'c'

Since the question says we need k>=1 for a,b,c
So the answer will be cCount[i] for the last index

The relations will be:
Ending with 'a':
    It can only be attached in front of a subsequence ending with 'a'
    So, we count all subsequences that end with 'a' and adding this to their end gives a new subsequence.
    Also, this alone could start a new subsequence
    So, the count = count(a) + count(a) + 1
    count(a) = 2*count(a) + 1
Ending with 'b':
    'b' can only be attached in front of a subsequence ending with 'a' or 'b'
    So, total subsequeces ending with 'b' till now = previous count of subsequences ending with 'b' and
    same count and we add this b to their end giving new subsequences.
    Also, this can be added to end of 'a' to give new subseq ending with 'b'
    So, the count = prevCount(b) + prevCount(b) + count(a)
    count(b) = 2*count(b) + count(a)
Ending with 'c':
    Same thing as 'b'
    Here we count all ending with 'c' + add this 'c' to their end giving new sequeces + add this 'c' to end of all
    sequences ending with 'b'
    count(c) = 2*count(c) + count(b)

Also, as each state i only depends on i-1, so we dont need to keep an array.
*/
int countSubsequences(string &source)
{
    int n = source.size();

    int aCount = 0, bCount = 0, cCount = 0;

    for (int i = 0; i < n; i++)
    {
        if (source[i] == 'a')
            aCount = 2 * aCount + 1;
        else if (source[i] == 'b')
            bCount = 2 * bCount + aCount;
        else
            cCount = 2 * cCount + bCount;
    }

    return cCount;
}

// Knapsack============================================================================================

// 0 - 1 Knapsack Problem (https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem0945/1)
/*
Approach: O(n^2), O(n)
Include / Exclude Approach
If the current item weight <= remaining weight
    Then make 2 calls: inlcude(idx + 1, remainingWeight - currItemWeight), exclude(idx + 1, remainingWeight)
    And take max of these
Else
    Just exclude: exclude(idx + 1, remainingWeight)

Each state of DP only depends on previous state.
So, we need only 1D DP.

*/
// Memoization
int knapSack01(int wt[], int val[], int W, int n, int idx, vector<vector<int>> &dp)
{
    if (W == 0 || idx == n)
        return 0;

    if (dp[idx][W] != -1)
        return dp[idx][W];

    int ans = -1;

    // include
    if (W - wt[idx] >= 0)
        ans = max(ans, knapSack01(wt, val, W - wt[idx], n, idx + 1, dp) + val[idx]);

    // exclude
    ans = max(ans, knapSack01(wt, val, W, n, idx + 1, dp));

    return dp[idx][W] = ans;
}
int knapSack(int W, int wt[], int val[], int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));

    return knapSack01(wt, val, W, n, 0, dp);
}
// Iterative
// 2D DP
int knapSack(int W, int wt[], int val[], int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(W + 1));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            // if this can be included
            if (w - wt[i - 1] >= 0)
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - wt[i - 1]] + val[i - 1]);
            // if it cannot be included
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
}
// 1D DP
int knapSack(int W, int wt[], int val[], int n)
{
    vector<int> prev(W + 1), curr(W + 1);

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            // if this can be included
            if (w - wt[i - 1] >= 0)
                curr[w] = max(prev[w], prev[w - wt[i - 1]] + val[i - 1]);
            // if it cannot be included
            else
                curr[w] = prev[w];
        }

        prev = curr;
        curr.assign(W + 1, 0);
    }

    return prev[W];
}

// Unbounded Knapsack (https://practice.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1)
/*
Approach: O(n^2)
Same as 0/1 Knapsack,
Just while including dont increase the index by 1, as current item can be included again
*/
int knapSack01(int wt[], int val[], int W, int n, int idx, vector<vector<int>> &dp)
{
    if (W == 0 || idx == n)
        return 0;

    if (dp[idx][W] != -1)
        return dp[idx][W];

    int ans = -1;

    // include
    if (W - wt[idx] >= 0)
        ans = max(ans, knapSack01(wt, val, W - wt[idx], n, idx, dp) + val[idx]);

    // exclude
    ans = max(ans, knapSack01(wt, val, W, n, idx + 1, dp));

    return dp[idx][W] = ans;
}
int knapSack(int n, int W, int val[], int wt[])
{
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));

    return knapSack01(wt, val, W, n, 0, dp);
}
// Iterative
int knapSack(int n, int W, int val[], int wt[])
{
    vector<vector<int>> dp(n + 1, vector<int>(W + 1));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            // if this can be included
            if (w - wt[i - 1] >= 0)
                dp[i][w] = max(dp[i - 1][w], dp[i][w - wt[i - 1]] + val[i - 1]);
            // if it cannot be included
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
}

// Fractional Knapsack Problem
/*
Approach: Greedy O(nlogn + n)
Sort the items in decreasing order of ratio: value / weight

The start with the highest ratio, and keep including the item completely until
its weight <= remaining weight
And then include the ratio of the next item to complete the capacity

Eg:
Items as (value, weight) pairs 
arr[] = {{60, 10}, {100, 20}, {120, 30}} 
Knapsack Capacity, W = 50; 

Ratio: 60/10 = 6
100/20 = 5
120/30 = 4

Decreasing order: (60,10), (100,20), (120,30)
Maximum possible value = 240 
by taking items of weight 10 and 20 kg and 2/3 fraction 
of 30 kg. Hence total price will be 60+100+(2/3)(120) = 240

*/
struct Item
{
    int value;
    int weight;
};
double fractionalKnapsack(int W, Item arr[], int n)
{
    // Your code here
    sort(arr, arr + n, [](Item &i1, Item &i2)
         { return (double)i1.value / i1.weight > (double)i2.value / i2.weight; });

    double ans = 0;

    for (int i = 0; i < n; i++)
    {
        if (W - arr[i].weight >= 0)
        {
            ans += arr[i].value;
            W -= arr[i].weight;
        }
        else
        {
            ans += ((double)W / arr[i].weight) * arr[i].value;
            break;
        }
    }

    return ans;
}

// 518. Coin Change 2 (Coin Change Combination)
/*
Approach: O(n^2), O(n^2)
*/
// Approach 1: Time: O(n^2), Space: O(n^2)
int combinations(vector<int> &coins, int tar, int idx, vector<vector<int>> &dp)
{
    if (tar == 0)
        return dp[idx][tar] = 1;
    if (idx == coins.size())
        return dp[idx][tar] = 0;

    if (dp[idx][tar] != -1)
        return dp[idx][tar];

    int count = 0;
    if (tar - coins[idx] >= 0)
        count += combinations(coins, tar - coins[idx], idx, dp);

    count += combinations(coins, tar, idx + 1, dp);

    return dp[idx][tar] = count;
}
int change(int amount, vector<int> &coins)
{
    vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1, -1));

    return combinations(coins, amount, 0, dp);
}
// Approach 2: Time: O(n^2), Space: O(n)
int change(int amount, vector<int> &coins)
{
    vector<int> dp(amount + 1);
    dp[0] = 1;

    // checking all targets for the available coins gives combinations
    for (int coin : coins)
    {
        for (int tar = coin; tar <= amount; tar++)
        {
            if (tar - coin >= 0)
                dp[tar] += dp[tar - coin];
        }
    }

    return dp[amount];
}

// Coin Change Permutation (Pepcoding)
int change(int amount, vector<int> coins)
{
    int n = coins.size();
    vector<int> dp(amount + 1);
    dp[0] = 1;

    // checking all coins for every target gives the permutations
    for (int tar = 0; tar <= amount; tar++)
    {
        for (int i = 0; i < n; i++)
        {
            if (tar - coins[i] >= 0)
                dp[tar] += dp[tar - coins[i]];
        }
    }

    return dp[amount];
}

// 322. Coin Change
/*
Approach: 
Same as Coin Change 2 (Combinations)
Instead of the count we just store the minimum subset size
Rest is same
*/
// Approach 1: Recursive, O(n^2), O(n^2)
int combinations(vector<int> &coins, int tar, int idx, vector<vector<int>> &dp)
{
    if (tar == 0)
        return dp[idx][tar] = 1;
    if (idx == coins.size())
        return dp[idx][tar] = 0;

    if (dp[idx][tar] != -1)
        return dp[idx][tar];

    int res = INT_MAX;

    if (tar - coins[idx] >= 0)
    {
        int includeAns = combinations(coins, tar - coins[idx], idx, dp);
        // if including gives an answer, then update the min subset size
        if (includeAns)
            res = min(res, includeAns + 1);
    }

    int excludeAns = combinations(coins, tar, idx + 1, dp);
    // if excluding gives an answer, then update the min subset size
    if (excludeAns)
        res = min(res, excludeAns);

    return dp[idx][tar] = res == INT_MAX ? 0 : res;
}
int coinChange(vector<int> &coins, int amount)
{
    vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1, -1));

    int res = combinations(coins, amount, 0, dp);

    return res == INT_MAX ? -1 : res - 1;
}
// Approach 2: Iterative, O(n^2), O(n)
int coinChange(vector<int> &coins, int amount)
{
    // Initialize with amount + 1 value, instead of INT_MAX to avoid overflow with INT_MAX + 1
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for (int coin : coins)
    {
        for (int tar = coin; tar <= amount; tar++)
        {
            if (tar - coin >= 0)
                dp[tar] = min(dp[tar], dp[tar - coin] + 1);
        }
    }

    return dp[amount] == amount + 1 ? -1 : dp[amount];
}

// 416. Partition Equal Subset Sum
/*
Approach: O(n^2)
Exactly same as knapsack
To divide the array into two subsets of equal sum, we just need to find a subset whose sum = total sum / 2
If there is a subarray with totalSum/2 sum, then the remaining elements will form the second subset
Also, the totalSum has to be even to divide the array into 2 subsets of equal sum
*/
bool knapsack01(vector<int> &nums, int tar, int idx, vector<vector<int>> &dp)
{
    if (tar == 0)
        return dp[idx][tar] = true;
    if (idx == nums.size())
        return dp[idx][tar] = false;

    if (dp[idx][tar] != -1)
        return dp[idx][tar];

    bool res = false;

    if (tar - nums[idx] >= 0)
        res = res || knapsack01(nums, tar - nums[idx], idx + 1, dp);

    res = res || knapsack01(nums, tar, idx + 1, dp);

    return dp[idx][tar] = res;
}
bool canPartition(vector<int> &nums)
{
    int n = nums.size();

    int totalSum = 0;
    for (int val : nums)
        totalSum += val;

    // if total sum is odd, return false
    if (totalSum % 2 != 0)
        return false;

    // use knapsack for target = total sum / 2
    vector<vector<int>> dp(n + 1, vector<int>(totalSum / 2 + 1, -1));

    return knapsack01(nums, totalSum / 2, 0, dp);
}

// 494. Target Sum
/*
Approach: O(n^2)
The current sum can be in the range: -target to +target
So, make DP for 2*target + 1
And to keep the currSum in range for indexing use currSum + totalSum
*/
int totalSum = 0;
int targetSum(vector<int> &nums, int currSum, int tar, int idx, vector<vector<int>> &dp)
{
    if (idx == nums.size())
    {
        if (currSum == tar)
            return dp[idx][currSum + totalSum] = 1;

        return dp[idx][currSum + totalSum] = 0;
    }

    if (dp[idx][currSum + totalSum] != -1)
        return dp[idx][currSum + totalSum];

    int count = 0;

    count += targetSum(nums, currSum - nums[idx], tar, idx + 1, dp);
    count += targetSum(nums, currSum + nums[idx], tar, idx + 1, dp);

    return dp[idx][currSum + totalSum] = count;
}
int findTargetSumWays(vector<int> &nums, int target)
{
    int n = nums.size();

    for (int val : nums)
        totalSum += val;

    vector<vector<int>> dp(n + 1, vector<int>(2 * totalSum + 1, -1));

    return targetSum(nums, 0, target, 0, dp);
}

// Digit DP=====================================================================================

// 233. Number of Digit One
/*
Approach: 
We go to each position in the number one by one

Eg: 2101832
3 Cases:
1. digit > 1:
Like in given eg we are at digit 8
If we put 1 at this position, then the remaining positions are:
(2101)8(32)
Replace 8 by 1, now the final number <= given number
As we lowered the current digit, so increasing any digit on its right will keep the overall number < given number
So, number of ways to fill positions to right is 0 - 99 i.e. 100 ways as there are only 2 digits to its right
For 3 digits it would be 1000(0-999) and so on
In general number of ways for right = position of current number, like 8 is at 100s position

Now for the left side, we cannot increase left side as it will increase the overall number
So, number of ways to fill left side = 0 - 2101(2102 ways) i.e. the number on left side + 1
So, total ways = (leftNumber + 1) * (position of current Number)

2. digit == 1:
Eg: 2101132
(2101)1(32)
If the digit is already 1, then we have 2 cases:
    a. We lower the left side number, in (0 - 2100) i.e. 2101 ways then on right side we can have 0-99 ways. Because if left side is lowered, 
        then overall wont increase.
        So, total ways = leftNumber * position of current digit
    b. When left remains equal to the original number then right side can be in (0 - 32) i.e. 33 ways.
        So, right can be anything between 0 and original right side 
        So, in this case left side is only filled in 1 way, and right side in rightNumber + 1 ways
        So, total = rightNumber + 1
So, total ways = (leftNumber * position of current digit) + (rightNumber + 1)

3. digit < 1:
Eg: 2101032
(2101)0(32)
If digit is < 1, then by putting 1, we are increasing this digit, so putting anything on right will increase it.
So, left side can be filled by any number lower can original left side i.e. 0 - 2100 ways
And since left side is smaller than original number, right side can be filled in current digit position number of ways
So, total ways = leftNumber * current digit's position



*/
int countDigitOne(int n)
{
    long mul = 1;
    int res = 0;

    while (n / mul > 0)
    {
        int leftNum = n / (mul * 10);
        int rightNum = n % mul;
        int currDigit = (n / mul) % 10;

        if (currDigit > 1)
            res += (leftNum + 1) * mul;
        else if (currDigit == 1)
            res += (leftNum * mul) + (rightNum + 1);
        else
            res += leftNum * mul;

        mul *= 10;
    }

    return res;
}

// Misc================================================================================================

// 264. Ugly Number II
/*
Approach: O(n)
Ugly number only have 2, 3, 5 as factors
So, we can only get an ugly number by multiplying 2 ugly numbers
To get the nth ugly number:
We keep track of the greatest ugly number for 2, 3, 5 as factors
And then to get the next ugly number we multiply the smallest of these with its next ugly number
(1) 1×2, 2×2, 3×2, 4×2, 
(2) 1×3, 2×3, 3×3,
(3) 1×5, 2×5

At this point 4x2 is smallest so we move 2 to its next factor that is also a ugly number which is 5
*/
int nthUglyNumber(int n)
{
    vector<int> nums(n);
    int twoIdx = 0, threeIdx = 0, fiveIdx = 0;

    nums[0] = 1; // first ugly number is 1

    for (int i = 1; i < n; i++)
    {
        // get the min of all three 2, 3, 5's current ugly numbers
        nums[i] = min(2 * nums[twoIdx], min(3 * nums[threeIdx], 5 * nums[fiveIdx]));

        // whichever is the minimum move that to its next factor
        // in case of duplicates like 2x3 and 3x2, move both 2 and 3 to next factor
        if (nums[i] == 2 * nums[twoIdx])
            twoIdx++;
        if (nums[i] == 3 * nums[threeIdx])
            threeIdx++;
        if (nums[i] == 5 * nums[fiveIdx])
            fiveIdx++;
    }

    return nums[n - 1];
}

// 313. Super Ugly Number
/*
Approach: O(nk)
Same as nth Ugly number
To maintain the indexes of primes we will need an array
*/
int nthSuperUglyNumber(int n, vector<int> &primes)
{
    vector<int> nums(n, INT_MAX);
    vector<int> primesIdx(primes.size());

    nums[0] = 1; // first ugly number is 1

    for (int i = 1; i < n; i++)
    {
        // get the min of all primes's current factors
        for (int j = 0; j < primes.size(); j++)
        {
            nums[i] = min(nums[i], primes[j] * nums[primesIdx[j]]);
        }

        // whichever is the minimum move that to its next factor
        for (int j = 0; j < primes.size(); j++)
        {
            if (nums[i] == primes[j] * nums[primesIdx[j]])
                primesIdx[j]++;
        }
    }

    return nums[n - 1];
}

// 10. Regular Expression Matching
/*
Approach: O(n^2)
If current p[i] is a letter, then   
    if p[i] = s[j], then dp[i][j] = true
    else dp[i][j] = false
If current p[i] is '.', then
    if p,s are equal till i-1, j-1, then they are equal till i,j as well
        then dp[i][j] = true
    else dp[i][j] = false
If current p[i] is '*', then

*/
bool isMatch(string s, string p)
{
    int n = s.size(), m = p.size();

    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
    dp[0][0] = true;

    for (int i = 0; i < m; i++)
    {
        if (p[i] == '*')
            dp[i + 1][0] = dp[i - 1][0];
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // if letter
            if (p[i - 1] >= 'a' && p[i - 1] <= 'z')
            {
                if (s[j - 1] == p[i - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = false;
            }

            // if .
            else if (p[i - 1] == '.')
            {
                dp[i][j] = dp[i - 1][j - 1];
            }

            // if *
            else
            {
                if (dp[i - 2][j] == true)
                    dp[i][j] = true;
                else
                {
                    if (p[i - 2] != s[j - 1] && p[i - 2] != '.')
                        dp[i][j] = false;
                    else
                        dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
            }
        }
    }

    return dp[m][n];
}

// 44. Wildcard Matching
/*
Approach: 
if s[i] == p[j] => n-1, m-1
if s[i] != p[j]{
    if '?' => n-1, m-1
    if '* => n-1,m and n-1,m-1 and n,m-1(for "" string)
    also in '* wildcard, can be subtituted for empty "" string in begin and end
}
*/
int isMatch_Mem(string &s, string &p, int n, int m, vector<vector<int>> &dp)
{
    //both strings are over
    if (n < 0 && m < 0)
        return 1;
    if (m < 0)
        return 0;
    if (n < 0)
    {
        //for case: s="", p="***", i.e pattern just has wildcards left
        //then all wildcards are substituted for empty string
        while (m >= 0 && p[m] == '*')
            m--;

        if (n < 0 && m < 0)
            return 1;
        else
            return 0;
    }

    if (dp[n][m] != -1)
        return dp[n][m];

    bool res = false;
    if (s[n] == p[m])
    {
        res = res || isMatch_Mem(s, p, n - 1, m - 1, dp);
    }
    else
    {
        if (p[m] == '?')
        {
            res = res || isMatch_Mem(s, p, n - 1, m - 1, dp);
        }
        else if (p[m] == '*')
        {
            res = res || isMatch_Mem(s, p, n - 1, m, dp) || isMatch_Mem(s, p, n - 1, m - 1, dp) || isMatch_Mem(s, p, n, m - 1, dp);
        }
    }

    return dp[n][m] = (res ? 1 : 0);
}
bool isMatch(string s, string p)
{
    int n = s.size() - 1;
    int m = p.size() - 1;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return isMatch_Mem(s, p, n, m, dp);
}

// 688. Knight Probability in Chessboard
/*
Approach: O(k*n*n)
For a particular row r, and column c
We have 8 options
So, the probability of going to those 8 positions is 1/8 each of the probabilty of current cell

For each k, the probabilities only depend on probabilities k - 1 moves
So, we keep two 2D DPs: previous probabilities, current probabilities

Now We iterate over the previous probabilties, and for each cell with p > 0
We find the 8 cells that can be reached from that cell
And the probability of that cell is:
current probability = current probability + (previous probability / 8)

We do this k times to get the probability for each cell on the board after k moves
And for total probability just find the sum of all values in the previous probability DP at the end
*/
double knightProbability(int n, int k, int row, int column)
{
    int dir[8][2] = {{2, 1}, {2, -1}, {1, 2}, {1, -2}, {-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}};

    vector<vector<double>> prevProb(n, vector<double>(n)), currProb(n, vector<double>(n));

    // initially, knight starts at the given row, column, so that cell's probability = 1
    prevProb[row][column] = 1;

    for (int count = 0; count < k; count++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // if probability of reaching current cell = 0, then skip it
                if (prevProb[i][j] == 0)
                    continue;

                // else update probability for the 8 cells on the board that can be reached from current cell
                for (int d = 0; d < 8; d++)
                {
                    int x = i + dir[d][0];
                    int y = j + dir[d][1];

                    if (x >= 0 && y >= 0 && x < n && y < n)
                    {
                        currProb[x][y] += prevProb[i][j] / 8;
                    }
                }
            }
        }

        // current becomes previous
        prevProb = currProb;

        // and reset the current board
        currProb.assign(n, vector<double>(n, 0));
    }

    // get the total probability after k moves
    double totalProb = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            totalProb += prevProb[i][j];
    }

    return totalProb;
}

// 87. Scramble String
/*
Approach: O(n^3)
We make cuts at indexes 1 to n
And we check if 
1. 0 to i of string1 can be scrambled into 0 to i of string2 
   and i to n of string1 can be scrambled into i to n of string 2
2. we can also swap the left and right part of ith index. So, check if
   0 to i of string1 can be scrambled into last i characters
   and i to n can of string 1 can be scrambled into 0 to n - i of string2

Also before making the cuts check if both strings have the same characters
Otherwise they can never be equal

Eg:
great, rgeat
Suppose we make a cut at 2
So we check for (gr, rg) and (eat, eat)
And (gr, at) and (eat, rge)

            great, rgeat (Only the true calls are shown)
             /      \
        gr, rg     eat, eat (returns true)
        /    \
   (g,r)    (r,g)     
(1st,1st) (2nd,2nd) 
  (g, g)     (r,r)
(1st,2nd), (2nd,1st)

So, we make cut at i = 2, and the right parts are already equal
And for left parts we again make cuts, and their left and right parts are equal
So, it returns true           

*/
unordered_map<string, bool> dp;
bool isScramble(string s1, string s2)
{
    string key = s1 + s2;

    if (dp.find(key) != dp.end())
        return dp[key];

    // if both strigns are equal
    if (s1 == s2)
        return dp[key] = true;

    // compare the frequency map of strings
    vector<int> freq1(26), freq2(26);
    for (int i = 0; i < s1.size(); i++)
    {
        freq1[s1[i] - 'a']++;
        freq2[s2[i] - 'a']++;
    }
    // if frequency map is different then they cannot be equal
    for (int i = 0; i < 26; i++)
    {
        if (freq1[i] != freq2[i])
            return dp[key] = false;
    }

    for (int i = 1; i < s1.size(); i++)
    {
        // make a cut at ith index in both strings
        // compare 1st and 2nd parts of both strings
        bool isEqual1 = isScramble(s1.substr(0, i), s2.substr(0, i));
        bool isEqual2 = isScramble(s1.substr(i), s2.substr(i));

        if (isEqual1 && isEqual2)
            return dp[key] = true;

        // compare first i characters of string1 with last i characters of strign 2
        // and same for 2nd part with first part of string2
        bool isEqual3 = isScramble(s1.substr(0, i), s2.substr(s2.size() - i));
        bool isEqual4 = isScramble(s1.substr(i), s2.substr(0, s2.size() - i));

        if (isEqual3 && isEqual4)
            return dp[key] = true;
    }

    return dp[key] = false;
}

// 139. Word Break
/*
Approach 1:
For the string s, make a cut at each index and check if the substring 0 to cut is present in the dictionary
If it is then make the call to check for the remaining string

*/
// Approach 1: O(n^3)
unordered_set<string> dict;
unordered_map<string, bool> dp;
bool wordBreak_(string &s)
{
    if (dp.find(s) != dp.end())
        return dp[s];

    // check if current string itself is in the dictionary
    if (dict.find(s) != dict.end())
        return dp[s] = true;

    for (int i = 1; i < s.size(); i++)
    {
        // check substring from 1 to i of current string is in the dictionary
        if (dict.find(s.substr(0, i)) != dict.end())
        {
            string remStr = s.substr(i);
            // if the substring is present in dictionary, check for the remaining string
            if (wordBreak_(remStr))
                return dp[s] = true;
        }
    }

    return dp[s] = false;
}
bool wordBreak(string &s, vector<string> &wordDict)
{
    // put all words into a hashset, to make find operation O(1)
    for (string &str : wordDict)
        dict.insert(str);

    return wordBreak_(s);
}
// Approach 2: O(n^2), Same as Approach 1, But Using indexes instead of substring
unordered_set<string> dict;
vector<int> dp;
bool wordBreak_(string &s, int si)
{
    if (si >= s.size())
        return false;

    if (dp[si] != -1)
        return dp[si];

    // check for all possible substrings from startIndex(si) to s.size()
    string currSubStr = "";
    for (int i = si; i < s.size(); i++)
    {
        currSubStr += s[i];

        if (dict.find(currSubStr) != dict.end())
        {
            if (wordBreak_(s, i + 1))
            {
                return dp[si] = true;
            }
        }
    }

    // check for whole string formed from si to s.size()
    if (dict.find(currSubStr) != dict.end())
    {
        return dp[si] = true;
    }

    return dp[si] = false;
}
bool wordBreak(string &s, vector<string> &wordDict)
{
    dp.resize(s.size(), -1);
    for (string &str : wordDict)
        dict.insert(str);

    return wordBreak_(s, 0);
}
// Approach 3: Iterative
bool wordBreak(string &s, vector<string> &wordDict)
{
    unordered_set<string> dict;
    for (string &str : wordDict)
        dict.insert(str);

    vector<bool> dp(s.size() + 1, false);

    for (int si = s.size() - 1; si >= 0; si--)
    {
        string currSubStr = "";
        for (int i = si; i < s.size(); i++)
        {
            currSubStr += s[i];

            if (dict.find(currSubStr) != dict.end())
            {
                if (dp[i + 1])
                {
                    dp[si] = true;
                    break;
                }
            }
        }

        if (dict.find(currSubStr) != dict.end())
        {
            dp[si] = true;
            continue;
        }
    }

    return dp[0];
}

// 140. Word Break II
/*
Approach:
Same as Word Break I
Instead of true, false return all possible sentences for the substring
*/
unordered_set<string> dict;
unordered_map<int, vector<string>> dp;
vector<string> wordBreak_(string &s, int si)
{
    if (si >= s.size())
        return {};

    if (dp.find(si) != dp.end())
        return dp[si];

    // check for all possible substrings from startIndex(si) to s.size()
    string currSubStr = "";
    vector<string> myAns;
    for (int i = si; i < s.size(); i++)
    {
        currSubStr += s[i];

        // if current substring is present in dictionary
        if (dict.find(currSubStr) != dict.end())
        {
            // get all sentences possible for the remaining string, and add yourself to all of their start
            vector<string> sentences = wordBreak_(s, i + 1);
            for (string &sent : sentences)
            {
                myAns.push_back(currSubStr + " " + sent);
            }
        }
    }

    // check for whole string formed from si to s.size()
    if (dict.find(currSubStr) != dict.end())
    {
        // there is no remaining substring, so this string itself forms 1 sentence
        myAns.push_back(currSubStr);
    }

    return dp[si] = myAns;
}
vector<string> wordBreak(string &s, vector<string> &wordDict)
{
    for (string &str : wordDict)
        dict.insert(str);

    return wordBreak_(s, 0);
}

// 1092. Shortest Common Supersequence
/*
Approach: O(n*m)
Find the LCS
Every Character in LCS will be present in the answer once
Rest of them should be present in same manner as the 2 strings given
So, build the LCS string from the dp
Then keep 3 pointers, one each on str1, str2, lcs
Until the current character in str1, str2 != current of lcs, keep adding them to the ans
Then add the lcs current and move all ahead.

Eg: AGGTAB, GXTXAYB
LCS: GTAB

So, the ans will of size = str1.size() + str2.size() - lcs.size() = 6 + 7 - 4 = 9
Ans = AGGXTXAYB

*/
string lcs(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    // find the length of LCS
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i == 0 || j == 0)
                continue;

            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    int lcsLen = dp[n][m];

    string lcsStr = "";

    // build the LCS string from the DP
    int i = n, j = m, count = 0;
    while (count < lcsLen)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            lcsStr += s1[i - 1];
            i--;
            j--;
            count++;
        }
        else
        {
            if (dp[i - 1][j] > dp[i][j - 1])
                i--;
            else
                j--;
        }
    }

    reverse(lcsStr.begin(), lcsStr.end());

    return lcsStr;
}
string shortestCommonSupersequence(string str1, string str2)
{
    string lcsStr = lcs(str1, str2);

    int i = 0, j = 0, k = 0;
    string res = "";

    // get the result string using the lcs
    while (k < lcsStr.size())
    {
        // until str1[i] != lcs[k], keep adding it to result
        while (i < str1.size() && str1[i] != lcsStr[k])
            res += str1[i++];

        // until str2[j] != lcs[k], keep adding it to result
        while (j < str2.size() && str2[j] != lcsStr[k])
            res += str2[j++];

        // now all 3 pointers are at same character, so add it to result and increase all 3
        res += lcsStr[k];
        i++;
        j++;
        k++;
    }

    // add the remaining str1 into result
    while (i < str1.size())
        res += str1[i++];

    // add the remaining str2 into result
    while (j < str2.size())
        res += str2[j++];

    return res;
}

// 403. Frog Jump
/*
Approach: O(n^2)
Keep a hashmap of {stone position : set of k values that it can be reached with}
Keep mp[0] = 1
As k for postion 0 is 1 always

Now we iterate over the stones
And for each stone, for each of each k value we find the next Position
that can be reached from their as nextPos = curr + k
And at that next positions's set, we insert k-1, k, k+1

This way the at the end the last stone has all the k that it can be reached with.
*/
bool canCross(vector<int> &stones)
{
    unordered_map<int, unordered_set<int>> mp;
    // initialise the set for each stones so that we have
    // the available stone values in the map when we search later
    for (int val : stones)
        mp[val] = unordered_set<int>();

    mp[0].insert(1);

    for (int val : stones)
    {
        // iterate over all k values of current stone
        for (auto itr = mp[val].begin(); itr != mp[val].end(); itr++)
        {
            int nextPos = val + *itr; // get the next position for that k
            // if there is a stone at that next positon, then insert k-1, k, k+1 in that stone's set
            if (mp.find(nextPos) != mp.end())
            {
                mp[nextPos].insert(*itr - 1);
                mp[nextPos].insert(*itr);
                mp[nextPos].insert(*itr + 1);
            }
        }
    }

    // if size of the set of last stone is > 0, then it can be reached else not
    return mp[stones[stones.size() - 1]].size() > 0;
}

// 72. Edit Distance
/*
Approach: O(n*m)
The relations for each operation is given by
insert: dp[i][j] = dp[i][j-1] + 1
remove: dp[i][j] = dp[i-1][j] + 1
replace: dp[i][j] = dp[i-1][j-1] + 1

*/
int minDistance(string word1, string word2)
{
    int n = word1.size(), m = word2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for (int j = 0; j <= m; j++)
        dp[0][j] = j;
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i == 0 || j == 0)
                continue;

            if (word1[i - 1] == word2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
            {
                dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
            }
        }
    }

    return dp[n][m];
}

// 546. Remove Boxes
int removeBoxes(vector<int> &boxes, int left, int right, int count, vector<vector<vector<int>>> &dp)
{
    if (left > right)
        return 0;

    if (dp[left][right][count] != -1)
    {
        return dp[left][right][count];
    }

    int currLeft = left;
    int currCount = count;

    while (currLeft < right && boxes[currLeft] == boxes[currLeft + 1])
    {
        currLeft++;
        currCount++;
    }

    int ans = 0;

    ans = removeBoxes(boxes, currLeft + 1, right, 0, dp) + (currCount + 1) * (currCount + 1);

    for (int i = currLeft + 1; i <= right; i++)
    {
        if (boxes[i] == boxes[currLeft])
        {
            int temp = removeBoxes(boxes, currLeft + 1, i - 1, 0, dp) + removeBoxes(boxes, i, right, currCount + 1, dp);
            ans = max(ans, temp);
        }
    }

    return dp[left][right][count] = ans;
}
int removeBoxes(vector<int> &boxes)
{
    int n = boxes.size();

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, -1)));

    return removeBoxes(boxes, 0, boxes.size() - 1, 0, dp);
}

// 887. Super Egg Drop
/*
Brute Force: 


Approach: O(n*k)
We start with m moves, e eggs
For each floor, we drop an egg:
1. Survive: 
    moves left = m - 1
    eggs left = e
    Number of floors checked = x

2. Break: 
    moves left = m - 1
    eggs left = e - 1
    Number of floors checked = y

So, number of floors for m, e = x + y + 1
Here, x, y = number of floors that we can check we the remaining moves, eggs

*/
int superEggDrop(int k, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));

    for (int m = 1; m <= n; m++)
    {
        for (int e = 1; e <= k; e++)
            dp[m][e] = dp[m - 1][e] + dp[m - 1][e - 1] + 1;

        if (dp[m][k] >= n)
            return m;
    }

    return n;
}

// Friends Pairing Problem
/*
Approach: O(n)
For n people, we have 2 choices for each person:
1. Remain Single: If this person remains single, then we just need to find the number of ways to pair up the remaining (n - 1) people.
                  So, in this case number of ways = count(n - 1)
2. Pair Up: If this person wants to pair up, then he can be paired up with one of the remaining (n - 1) people in (n - 1) ways
            And the then we find the number of ways for remaining (n - 2) people.
            So, in this case number of ways = count(n - 2) * (n - 1)
    
So, total count = count(n - 1) + count(n - 2) * (n - 1)

Base Case: If n == 1, then number of ways = 1
*/
// O(n) space
int countFriendsPairings(int n)
{
    long MOD = 1e9 + 7;

    vector<long> dp(n + 1);
    dp[0] = dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2] * (i - 1);
        dp[i] %= MOD;
    }

    return dp[n];
}
// O(1) space
int countFriendsPairings(int n)
{
    long MOD = 1e9 + 7;

    long a = 1, b = 1; // a = dp[n-2], b = dp[n-1]

    for (int i = 2; i <= n; i++)
    {
        long c = b + a * (i - 1);
        c %= MOD;

        a = b;
        b = c;
    }

    return b;
}

// Largest Sum Subarray of Size at least K
/*
Approach: O(n)
We preprocess and make a prefixSum array
Each index i of prefixMax contains the max subarray sum till i

Then using a sliding window we find the sum of every k size window
And for each window, we update the max sum as
maxSum = max(windowSum, windowSum + prefixMax[i-k])
So, for each window, the max can be that window, or that window + the max sum on its left
*/
long long int maxSumWithK(long long int a[], long long int n, long long int k)
{
    vector<long long> prefixMax(n);

    // find prefixMax for each index
    prefixMax[0] = a[0];
    for (int i = 1; i < n; i++)
    {
        // max for this index is either this element or this element + max till now
        prefixMax[i] = max(a[i], a[i] + prefixMax[i - 1]);
    }

    long long res = 0, currSum = 0;

    // first window
    for (int i = 0; i < k; i++)
        currSum += a[i];

    res = currSum;

    for (int i = k; i < n; i++)
    {
        // find current window sum
        currSum += a[i] - a[i - k];

        // update the max sum
        res = max(res, max(currSum, currSum + prefixMax[i - k]));
    }

    return res;
}

// 45. Jump Game II
/*
Approach 1: DP, Time: O(n^2), Space: O(n)
For each index go to every index in range [curridx, currIdx + arr[i]]
Worst Case will be like [6,5,4,3,2,1,0,5] here it will be n^2

Approach 2: Greedy, O(n), O(1)
Suppose we are at index i, from here farthest we can go will be (i + arr[i])
So, let currBegin = i, currEnd = i + arr[i]
In this range [currBegin, currEnd] we can reach anywhere with 1 jump from i.
Now, we find the farthest we can go from this range
To do this we keep a 
int canReach;
And for every index in the current range we find the max index we can reach from here by 
canReach = max(canReach, i + arr[i]) for every i in [currBegin, currEnd]
And wherever we get the max canReach, is the start of next interval.
And then the next interval will be [index that gives max canReach, canReach]

And when the canReach >= last index, then we have our answer
So, we are basically jumping from one interval to other, and it takes 1 jump to go from one interval to next
So, in this manner when canReach becomes >= destination, then we have our minimum jumps


*/
// Approach 1: O(n^2), O(n)
int jumps(vector<int> &nums, int idx, vector<int> &dp)
{
    if (idx >= nums.size())
        return -1;

    if (idx == nums.size() - 1)
        return 0;

    if (dp[idx] != -1)
        return dp[idx];

    int minCount = nums.size();

    // for current index, go to every index this index can jump to
    for (int i = 1; i <= nums[idx]; i++)
    {
        int currCount = jumps(nums, idx + i, dp);

        // if you were able to reach the end
        if (currCount != -1)
            minCount = min(minCount, currCount + 1);
    }

    return dp[idx] = minCount;
}
int jump(vector<int> &nums)
{
    int n = nums.size();

    vector<int> dp(n, -1);

    return jumps(nums, 0, dp);
}
// Approach 2: O(n)
int jump(vector<int> &nums)
{
    int n = nums.size();

    if (n <= 1)
        return 0;

    int canReach = nums[0], currBegin = 0, jumps = 0;
    // until canReach is less than last index
    while (canReach < n - 1)
    {
        jumps++;

        int currEnd = currBegin + nums[currBegin], nextBegin;

        // find the canReach for current interval
        for (int i = currBegin; i <= currEnd; i++)
        {
            if (i + nums[i] > canReach)
            {
                canReach = i + nums[i];
                nextBegin = i;
            }
        }

        // update the begin for next interval
        currBegin = nextBegin;
    }

    return jumps + 1;
}
// Approach 2: Shorter Code
int jump(vector<int> &nums)
{
    int canReach = 0, currEnd = 0, jumps = 0;

    for (int i = 0; i < nums.size() - 1; i++)
    {
        // update canReach for current interval
        canReach = max(canReach, i + nums[i]);

        // if this index is the end of current interval, then update with the end of next interval
        if (i == currEnd)
        {
            jumps++;
            currEnd = canReach;
        }
    }

    return jumps;
}

// 55. Jump Game
/*
Approach: Greedy, O(n)
Same as Jump Game 2
*/
// Approach : Greedy
bool canJump(vector<int> &nums)
{
    int n = nums.size();

    if (n <= 1)
        return true;

    int canReach = nums[0], currBegin = 0;

    // until canReach is less than last index
    while (true)
    {
        // currEnd will be the min(last index, max index that can be reached from this index)
        int currEnd = min(currBegin + nums[currBegin], n - 1), nextBegin;

        // find the canReach for current interval
        for (int i = currBegin; i <= currEnd; i++)
        {
            if (i + nums[i] > canReach)
            {
                canReach = i + nums[i];
                nextBegin = i;
            }
        }

        // can reach end from current interval
        if (canReach >= n - 1)
            return true;

        // cannot never go outside current interval, so cannot reach the end
        if (canReach <= currEnd)
            return false;

        // update the begin for next interval
        currBegin = nextBegin;
    }

    return false;
}
// Same Approach, Shorter Code
bool canJump(vector<int> &nums)
{
    int canReach = 0, currEnd = 0;

    for (int i = 0; i < nums.size() - 1; i++)
    {
        // update canReach for current interval
        canReach = max(canReach, i + nums[i]);

        // if this index is the end of current interval, then update with the end of next interval
        if (i == currEnd)
            currEnd = canReach;
    }

    return currEnd >= nums.size() - 1;
}

// 1306. Jump Game III
/*
Approach: DFS, O(n)
From each index, if it is in range and not visited yet
Mark current index as visited
go to idx + arr[idx], idx - arr[idx]
If current arr[idx] == 0, then return true

We dont unmark visited, as if that index cannot reach any index with 0, then it
doesn't matter what path we take to that index, it will still never be able to reach the destination

So, Every index is visited atmost once
So, Time: O(n)
*/
bool canReach(vector<int> &arr, int start)
{
    // if not in range, or visited, then return false
    if (start < 0 || start >= arr.size() || arr[start] == -1)
        return false;

    // if current element is 0, then return true
    if (arr[start] == 0)
        return true;

    int val = arr[start];
    arr[start] = -1; // mark visited

    // if any call returns true then return true
    if (canReach(arr, start + val) || canReach(arr, start - val))
        return true;

    return false;
}

// 1871. Jump Game VII
/*
Approach 1: BFS, O(n)
For each index, mark it as visited
then go to all index in range [i + minJump, i + maxJump] if s[i] == 0
Also, like if you have checked the range (4, 10) for a certain index, then if another index after it
is checking (6, 15), then you can directly start from 11 instead.
So, for each index the range would be: max(i + minJump, alreadyReached) to min(i + maxJump, n - 1)
i.e. you start from the i + minJump and if some part of that range is already checked, then start from the end of
the checked range, and the upper limit is the i + maxJump, if that is in the array bounds.
If you reach the end return true.

Approach 2: DP + Sliding Window, O(n)
Explanation is not accurate
For do it in reverse.
For each index i, we find all indexes it can be reached from 
The indexes it can be reached from will lie in range [i - maxJump, i - minJump]

To do this we use Sliding window approach.
We maintain the count of ways the current index i can be reached.
Then for the current index, the number of ways = number of i - minJump can be reached - number of ways i - maxJump can be reached
= count(i - minJump) - count(i - maxJump)

This way for each index i, we will find the count of ways it can be reached.
And then if the current index has s[i] == 0 and count > 1, then dp[i] = true


*/
// Approach 1: BFS O(n)
bool canReach(string s, int minJump, int maxJump)
{
    int n = s.size();

    queue<int> que;
    que.push(0);

    int alreadyReached = 0;

    while (que.size() > 0)
    {
        int rIdx = que.front();
        que.pop();

        for (int i = max(rIdx + minJump, alreadyReached); i <= min(rIdx + maxJump, n - 1); i++)
        {
            if (s[i] == '0')
            {
                // if last reached return true
                if (i == n - 1)
                    return true;

                s[i] = '#'; // mark visited
                que.push(i);
            }
        }

        // upper limit of currrent range is now the max index we already checked
        alreadyReached = rIdx + maxJump;
    }

    return false;
}
// Approach 2: Sliding Window + DP, O(n)
bool canReach(string s, int minJump, int maxJump)
{
    int count = 0;
    vector<bool> dp(s.size());

    dp[0] = true;
    for (int i = minJump; i < s.size(); i++)
    {
        count += dp[i - minJump];
        if (i - maxJump > 0)
            count -= dp[i - maxJump - 1];

        if (s[i] == '0' && count > 0)
            dp[i] = true;
    }

    return dp[s.size() - 1];
}

// 1345. Jump Game IV
/*
Approach: BFS O(n)
(Always try BFS for questions where minimum steps to destination is asked. BFS ensures minimum steps)

Make a map of {element : list of indexes that element is present at}
Then, use BFS. For each level jumps increase by 1
Every indexes that get removed from queue adds idx - 1, idx + 1, all indexes where that same element is present into queue
Mark every index visited when it is added to queue.
Also, after adding all same element into queue, clear that list from map
Because when it goes to those indexes it will again check for all of them
And even though they wont be added into queue because their visited would be true, but still that
for loop will run completely increasing complexity to O(n^2)

For Eg: [7,7,7,7,7,7,7,6]
Now, the first 7 will check all remaining 7s, add them to queue and mark them as visited
Now when it goes to those 7s, they will again check all 7s. Even though they wont be added to queue but that
for loop still runs for all of them. To avoid that clear the list when the first 7 is reached
Because after that every time a 7 is reached, it will be with more steps.
*/
int minJumps(vector<int> &arr)
{
    int n = arr.size();

    unordered_map<int, vector<int>> mp;
    vector<bool> vis(n);
    queue<int> que;

    for (int i = 0; i < n; i++)
    {
        mp[arr[i]].push_back(i);
    }

    int jumps = 0;
    que.push(0);
    vis[0] = true;

    while (que.size() > 0)
    {
        int size = que.size();

        while (size--)
        {
            int rIdx = que.front();
            que.pop();

            if (rIdx == n - 1)
                return jumps;

            if (rIdx - 1 >= 0 && !vis[rIdx - 1])
            {
                vis[rIdx - 1] = true;
                que.push(rIdx - 1);
            }
            if (rIdx + 1 < n && !vis[rIdx + 1])
            {
                vis[rIdx + 1] = true;
                que.push(rIdx + 1);
            }

            for (int idx : mp[arr[rIdx]])
            {
                if (!vis[idx])
                {
                    vis[idx] = true;
                    que.push(idx);
                }
            }

            // after going to all indexes where same element is present, erase it from the
            // map so that you dont check again for it at those indexes, because even though they would
            // be marked visited and not added in queue, but still the for loop will run for all of
            // them to check if they can be visited
            mp.erase(arr[rIdx]);
        }

        jumps++;
    }

    return -1;
}

// 1340. Jump Game V
/*
Approach 1: O(nd), DP
Start from every index and apply dfs to find the max jumps from that start
In the DFS, for the current index, go right until you have a currHeight > that height 
And same for left side
Make calls from every index, and return the max answer.

Approach 2: O(n)
If you have like [7,3,2,1]
Then you only need to check 7 -> 3 -> 2 -> 1
Checking 7 -> 2 -> 1 or 7 -> 1 cannot give maximum answer
So, we need to check for decreasing sequences
Not done here

*/
// Approach 1: O(nd)
int maxJumps(vector<int> &arr, int d, int idx, vector<int> &dp)
{
    int n = arr.size();

    if (dp[idx] != -1)
        return dp[idx];

    int count = 0;

    // go right until you dont get a >= element
    for (int i = idx + 1; i <= min(n - 1, idx + d); i++)
    {
        if (arr[i] < arr[idx])
            count = max(count, maxJumps(arr, d, i, dp));
        else
            break;
    }

    // go left until you dont get a >= element
    for (int i = idx - 1; i >= max(0, idx - d); i--)
    {
        if (arr[i] < arr[idx])
            count = max(count, maxJumps(arr, d, i, dp));
        else
            break;
    }

    return dp[idx] = count + 1;
}
int maxJumps(vector<int> &arr, int d)
{
    int n = arr.size();

    int res = 0;
    vector<int> dp(n, -1);

    for (int i = 0; i < n; i++)
        res = max(res, maxJumps(arr, d, i, dp));

    return res;
}

// 1696. Jump Game VI
/*
Approach 1: DP, Time: O(nk), Space: O(n)
Start from end, and for each index find the max ans from next k indexes
This way you can form the dp and get the ans

Approach 2: Time: O(n), Space: O(k)
Using Sliding Window Maximum technique using a queue
We can find greatest in k size window in O(1)
Rest is the same method, at each index get max of next k elements
This makes complexity O(n)
*/
// Approach 1: DP, O(nk)
int maxResult(vector<int> &nums, int k)
{
    int n = nums.size();

    vector<int> dp(n);

    dp[n - 1] = nums[n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        int maxVal = dp[i + 1];

        // find max in next k elements
        for (int j = i + 1; j <= min(n - 1, i + k); j++)
            maxVal = max(maxVal, dp[j]);

        dp[i] = maxVal + nums[i];
    }

    return dp[0];
}
// Approach 2: DP + Queue, O(n)
int maxResult(vector<int> &nums, int k)
{
    int n = nums.size();

    vector<int> dp(n);
    deque<int> que;

    dp[n - 1] = nums[n - 1];
    que.push_back(n - 1);

    for (int i = n - 2; i >= 0; i--)
    {
        // pop front until front element is out of current window
        while (que.size() > 0 && que.front() > i + k)
            que.pop_front();

        // now front gives the max of current window
        dp[i] = dp[que.front()] + nums[i];

        // now remove last element until it is less than current element
        while (que.size() > 0 && dp[que.back()] < dp[i])
            que.pop_back();

        // add current element
        que.push_back(i);
    }

    return dp[0];
}

// Extra========================================================================================

// 1755. Closest Subsequence Sum
/*
Approach: Time: O(n*2^(n/2)), Space: O(2^(n/2))
If we just brute force and generate all sums of subsequences of the original array,
the time complexity would be O(2^n) which is too slow for n=40.
Instead we can break the array in half and generate all possible sums of each half. 
For each possible sum of the 1st half, we binary seach for the sum in the 2nd half 
that gives the closest value to goal.

While searching (goal - value of first half), in second half:
1. If you find the exact value then difference is 0, so just return 0
2. Else find the difference with both the just greater value and just smaller value.
*/
void subsetSum(vector<int> &nums, int si, int ei, int currSum, vector<int> &subsets)
{
    if (si == ei)
    {
        subsets.push_back(currSum);
        return;
    }

    subsetSum(nums, si + 1, ei, currSum + nums[si], subsets);
    subsetSum(nums, si + 1, ei, currSum, subsets);
}
int minAbsDifference(vector<int> &nums, int goal)
{
    int n = nums.size();

    vector<int> left, right;

    subsetSum(nums, 0, n / 2, 0, left);  // all possible sums of first half
    subsetSum(nums, n / 2, n, 0, right); // all possible sums of second half

    // sort the second half
    sort(right.begin(), right.end());

    int res = INT_MAX;

    // for every sum in first half
    for (int val1 : left)
    {
        // binary search it in second half
        int idx = lower_bound(right.begin(), right.end(), goal - val1) - right.begin();

        // update the answer with just difference b/w just greater value
        if (idx < right.size())
        {
            // if exact value, then return 0
            if (right[idx] == goal - val1)
                return 0;

            res = min(res, abs(goal - (val1 + right[idx])));
        }

        // update the answer with just difference b/w just smaller value
        if (idx - 1 >= 0)
            res = min(res, abs(goal - (val1 + right[idx - 1])));
    }

    return res;
}

// 221. Maximal Square
/*
Approach: O(mn)
Each i,j stores the side of largest square with that index at its bottom right corner
So, the side of largest square for i, j = min((i-1,j-1), (i-1,j), (i,j-1))
From these 3 cells we can find the max length of square with i,j as bottom right corner
*/
int maximalSquare(vector<vector<char>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    vector<vector<int>> dp(n, vector<int>(m));
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = matrix[i][j] - '0';
            else if (matrix[i][j] == '1')
                dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;

            // update the max area
            res = max(res, dp[i][j] * dp[i][j]);
        }
    }

    return res;
}

// 1277. Count Square Submatrices with All Ones
/*
Approach: O(mn)
Same approach as maximal square.
We can use the matrix itself as DP.
And every cell stores the max length of square with that cell as bottom right corner
Then the number of squares with that corner is also equal to that length
Eg: 
1 1 1
1 1 1
1 1 1

So, for {2,2}, we have 3 squares with that index as bottom right corner
As from {2,2} you have max length 3, so you have 3 squares of length 1,2,3

In this way each index stores count of squares with that corner
And their sum gives total count
*/
int countSquares(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();

    int res = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // update length of max square
            if (matrix[i][j] == 1 && i > 0 && j > 0)
                matrix[i][j] = min({matrix[i - 1][j - 1], matrix[i - 1][j], matrix[i][j - 1]}) + 1;

            // add the count
            res += matrix[i][j];
        }
    }

    return res;
}

// 1395. Count Number of Teams
/*
Approach 1: O(n^2)
For each element find count of 
1. smaller elements on left
2. smaller elements on right
3. greater elements on left
4. greater elements on right

Then the count for current element of [a,b,c] where a > b > c OR a < b < c
= leftSmaller*rightGreater(for increasing)  + rightSmaller*leftGreater(for decreasing)

Approach 2: O(nlogn), Using BST or Fenwick Tree or similar approaches

*/
// Approach 1: O(n^2)
int numTeams(vector<int> &rating)
{
    int n = rating.size();

    int res = 0;

    for (int i = 0; i < n; i++)
    {
        int leftGreater = 0, rightGreater = 0;
        int leftSmaller = 0, rightSmaller = 0;

        for (int j = 0; j < n; j++)
        {
            if (rating[j] > rating[i])
                (i < j) ? leftGreater++ : rightGreater++;
            if (rating[j] < rating[i])
                (i < j) ? leftSmaller++ : rightSmaller++;
        }

        res += leftGreater * rightSmaller + leftSmaller * rightGreater;
    }

    return res;
}

// Not a subset sum (https://practice.geeksforgeeks.org/problems/smallest-number-subset1220/1)
/*
Approach: O(n)
Just keep a sum variable
sum = 1 initially as that is the smallest +ve number
Then iterate over the array and if the arr[i] <= sum
Then every number till sum can be represented using subset of array
So, iterate until this condition is true
When the sum < arr[i], then sum is the answer
*/
long long findSmallest(long long arr[], int n)
{
    long long sum = 1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] <= sum)
            sum += arr[i];
        else
            break;
    }

    return sum;
}

// Count ways to divide N into K groups (https://www.geeksforgeeks.org/count-the-number-of-ways-to-divide-n-in-k-groups-incrementally/#)
int countWays(int n, int k, int idx, vector<vector<vector<int>>> &dp)
{
    if (n == 0 && k == 0)
        return dp[n][k][idx] = 1;
    if (k == 0 || n <= 0 || k > n)
        return dp[n][k][idx] = 0;

    if (dp[n][k][idx] != -1)
        return dp[n][k][idx];

    int count = 0;
    for (int i = idx; i <= n; i++)
        count += countWays(n - i, k - 1, i, dp);

    return dp[n][k][idx] = count;
}
void partitionNintoKgroups()
{
    int n = 8, k = 4;

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(n + 1, -1)));
    cout << countWays(n, k, 1, dp);
}

// 1641. Count Sorted Vowel Strings
/*
For every string add all vowels greater than the last character to it.
So, for each recursive call we pass it the n-1, last character used
Then, at each call we start adding vowels from that last character

For Eg: n=3
Dp:
1 1 1 1 1 
5 4 3 2 1 
15 10 6 3 1 
35 -1 -1 -1 -1 

So, at each row we are storing the sum of previous row from that column to end
Like dp[2][1] = dp[1][1] + dp[1][2] + dp[1][3] + dp[1][4] = 4 + 3 + 2 + 1

So, since we only need one row at a time, we can use a 1d dp.
*/
char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
int countVowelStrings_(int n, int lastChar, vector<vector<int>> &dp)
{
    if (n == 0)
        return dp[n][lastChar] = 1;

    if (dp[n][lastChar] != -1)
        return dp[n][lastChar];

    int res = 0;
    for (int i = lastChar; i < 5; i++)
    {
        res += countVowelStrings_(n - 1, i, dp);
    }

    return dp[n][lastChar] = res;
}
int countVowelStrings_dp(int N)
{
    vector<vector<int>> dp(N + 1, vector<int>(5, -1));
    for (int n = 0; n <= N; n++)
    {
        //start adding from end at each row, so at each n,i we will get the required sum
        for (int i = 4; i >= 0; i--)
        {
            if (n == 0)
                dp[n][i] = 1;
            else
                dp[n][i] = dp[n][i + 1] + dp[n - 1][i];
        }
    }

    return dp[N][0];
}
int countVowelStrings(int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(5, -1));
    // return countVowelStrings_(n, 0, dp);
    return countVowelStrings_dp(n);
}

// 118. Pascal's Triangle
/*
Approach: O(n^2)
Just find the values for current row using previous row
and do this for every row
*/
vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> triangle(numRows);
    triangle[0].push_back(1);

    for (int i = 1; i < numRows; i++)
    {
        triangle[i].push_back(1);

        for (int j = 1; j < triangle[i - 1].size(); j++)
            triangle[i].push_back(triangle[i - 1][j - 1] + triangle[i - 1][j]);

        triangle[i].push_back(1);
    }

    return triangle;
}

// 119. Pascal's Triangle II
/*
Approach: Time: O(n^2), Space: O(n)
For the current we can make changes in the previous row array itself
Just start adding from the end.
This way you wont lose any values of previous row until you have used them.
*/
vector<int> getRow(int rowIndex)
{
    vector<int> currRow(rowIndex + 1);
    currRow[0] = 1;

    for (int i = 1; i <= rowIndex; i++)
    {
        for (int j = i; j > 0; j--)
            currRow[j] = currRow[j] + currRow[j - 1];
    }

    return currRow;
}

// 53. Maximum Subarray
/*
Approach 1: Kadanne's Algo, O(n)
This is the standard Kadanne' Algo to get the maximum subarray sum

Approach 2: DP, O(n)
This is the exact same as Kadanne's Algo
You just dont reset the currMax value with 0 if it goes -ve.
like this, if (currMax < 0) currMax = 0;

Instead we do
currMax = max(currMax + arr[i], arr[i]);
So, we are basically just ignoring the previous value if current is more, which 
is same as setting to 0 in previous step

*/
int maxSubArray(vector<int> &arr)
{
    int n = arr.size();
    long maxSoFar = arr[0];
    long currMax = 0;

    for (int i = 0; i < n; i++)
    {
        currMax += arr[i];
        if (maxSoFar < currMax)
            maxSoFar = currMax;
        if (currMax < 0)
            currMax = 0;
    }

    return maxSoFar;
}
int maxSubArray(vector<int> &arr)
{
    int currMax = arr[0], res = arr[0];

    for (int i = 1; i < arr.size(); i++)
    {
        currMax = max(currMax + arr[i], arr[i]);
        res = max(res, currMax);
    }

    return res;
}

// 1186. Maximum Subarray Sum with One Deletion
/*
Approach: Time: O(n), Space: O(n)
We keep track of 2 things
Max sum till now with no deletions which is basically the Kadanne's array
And a max till now with 1 deletion

So, for no deletion
noDelete[i] = max(max till now + current value, current value) = max(noDelete[i-1] + arr[i], arr[i])

And for one deletion, 
If we remove the current element, then we have to take the noDelete[i-1] as that will have max till now
with no deletions and we removed this one.
And if we dont remove the current element, then we take oneDelete[i-1] + arr[i], so we took
the max till now with one removed already, so we cannot remove this one as only one deletion is allowed.
So, oneDelete[i] = max(noDelete[i - 1], oneDelete[i - 1] + arr[i])

We can just use variables for oneDelete, noDelete, and make the space O(1)
For this we will have to calculate oneDelete before noDelete, as oneDelete depends on
previous value of noDelete
*/
int maximumSum(vector<int> &arr)
{
    int n = arr.size();

    vector<int> noDelete(n), oneDelete(n);
    noDelete[0] = arr[0];
    oneDelete[0] = max(arr[0], 0);

    int res = arr[0];

    for (int i = 1; i < n; i++)
    {
        noDelete[i] = max(noDelete[i - 1] + arr[i], arr[i]);
        oneDelete[i] = max(noDelete[i - 1], oneDelete[i - 1] + arr[i]);

        res = max({res, noDelete[i], oneDelete[i]});
    }

    return res;
}
// Approach 1: Time: O(n), Space: O(1)
int maximumSum(vector<int> &arr)
{
    int noDelete = arr[0], oneDelete = max(arr[0], 0), res = arr[0];

    for (int i = 1; i < arr.size(); i++)
    {
        oneDelete = max(noDelete, oneDelete + arr[i]);
        noDelete = max(noDelete + arr[i], arr[i]);

        res = max({res, noDelete, oneDelete});
    }

    return res;
}

// 857 · Minimum Window Subsequence (Lintcode)
/*
Approach: O(nm)
From every index in string s, if it is equal to t[0], then find the if there is a subsequence starting 
from that index that is equal to t, if there is than update the min length using the start and end point
of that subsequence.
*/
int findSubseq(string &s, string &t, int i, int j, vector<vector<int>> &dp)
{
    if (i == s.size() || j == t.size())
        return INT_MAX;
    if (j == t.size() - 1 && s[i] == t[j])
        return i;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (s[i] == t[j])
        return dp[i][j] = findSubseq(s, t, i + 1, j + 1, dp);
    else
        return dp[i][j] = findSubseq(s, t, i + 1, j, dp);
}
string minWindow(string &S, string &T)
{
    int ansStart = 0, ansEnd = INT_MAX;
    vector<vector<int>> dp(S.size(), vector<int>(T.size(), -1));

    for (int si = 0; si < S.size(); si++)
    {
        // if this character is equal to t[0], find the end of subsequence
        if (S[si] == T[0])
        {
            int ei = findSubseq(S, T, si + 1, 1, dp);

            // if subsequence is present, then update the shortest length
            if (ei != INT_MAX && ei - si + 1 < ansEnd - ansStart + 1)
            {
                ansStart = si;
                ansEnd = ei;
            }
        }
    }

    return (ansEnd == INT_MAX) ? "" : S.substr(ansStart, ansEnd - ansStart + 1);
}

// 877. Stone Game
/*
Approach 1: Game Theory, O(1)
There are always even number of piles.
So, whoever goes first wins.

Eg: [5,3,4,5]
Here the sum of 0th + 2nd element is greater than 1st + 3rd
So, Alice will pick 0th, and then Bob has to pick 2nd or 4th, and Alice picks 3rd and total will be more
So, basically for every n, Alice will choose either all even positions, or all odd positions
whichever has more total sum.
So, eg [1,2,3,4,5,6]
Here 1 + 3 + 5 < 2 + 4 + 6
So, Alice picks all odd positions(2,4,6)
Once she picks a odd position, both ends will only have the even positions so
bob is forced to pick an even position and this continues.
Similarly if even had more sum, she will only pick even positions
So, in this way for any even n, alice always wins

This only works because n here is even
In case of odd number of piles we need to use DP

Approach 2: DP, O(n^2)
Let dp(i, j) be the largest score Alex can achieve where the piles remaining are 
piles[i], piles[i+1], ..., piles[j]. 
So, instead of storing seperate scores, we just the current difference of their scores
And in case of Alice she will add the sum to that, and Bob will remove it so 
at the end we will have the difference between both their scores

When the piles remaining are piles[i], piles[i+1], ..., piles[j], 
the player who's turn it is can pick the first or last stone

If the player is Alice, then she either takes piles[i] or piles[j], 
increasing her score by that amount. 
Afterwards, the total score is either piles[i] + dp(i+1, j), or piles[j] + dp(i, j-1)
and we want the maximum possible score because Alice plays optimally

If the player is Bob, then he either takes piles[i] or piles[j], 
decreasing Alice's score by that amount. 
Afterwards, the total score is either -piles[i] + dp(i+1, j), or -piles[j] + dp(i, j-1); 
and we want the minimum possible score, as Bob plays optimally
*/
// Approach 1: Game Theory, O(1)
bool stoneGame(vector<int> &piles)
{
    return true;
}
// Approach 2: DP, O(n^2)
int getMaxScore(vector<int> &piles, int start, int end, int turn, vector<vector<int>> &dp)
{
    if (start == end)
        return piles[start];

    if (dp[start][end] != -1)
        return dp[start][end];

    // turn -> 1 is Alice, 0 is Bob
    if (turn)
        return dp[start][end] = max(getMaxScore(piles, start + 1, end, 0, dp) + piles[start], getMaxScore(piles, start, end - 1, 1, dp) + piles[end]);
    else
        return dp[start][end] = min(getMaxScore(piles, start + 1, end, 0, dp) - piles[start], getMaxScore(piles, start, end - 1, 1, dp) - piles[end]);
}
bool stoneGame(vector<int> &piles)
{
    int n = piles.size();

    vector<vector<int>> dp(n, vector<int>(n, -1));
    return getMaxScore(piles, 0, n - 1, 1, dp);
}

// 1140. Stone Game II
/*
Approach 1: DP, Time: O(n^2), Space: O(2 * n * n)
The function returns Alice's score
So, At each step,
Run a loop from idx + 1 to idx + 2*m
And if its Alice's turn then find the max score she can get from the remaining piles
And if its Bob's turn then find the min score Alice can get from the remaining piles

And if the all remaining piles can be picked then the current player takes them all.

The DP will be n x n x 2

Approach 2: DP, Time: O(n^2), Space: O(n^2)
First make a suffix sum array
Now at each step,
suffixSum[i] gives the total score from the remaining array
Now run a loop from i + 1 to i + 2*m
The current player picks the piles from i to i + x - 1, and then we find the
min score the next player can get from the piles i+x to end
So, we dont check whose turn it is, instead as both are playing optimally so just
find the min score other player can get from remaining piles
And then current player score is suffixSum[i] - minScore which will automatically be 
max since we got the min score for the other one.

So, basically at each step you choose a path in which the opponent gets the least score.
This approach is common to most stone game questions
*/
int getAliceScore(vector<int> &piles, int m, int idx, int turn, vector<vector<vector<int>>> &dp)
{
    if (dp[idx + 1][m][turn] != -1)
        return dp[idx + 1][m][turn];

    // if all remaining piles can be taken, then take them all
    if (idx + 2 * m >= piles.size())
    {
        // if it is Bob's turn then just return 0, as we only need Alice's score
        if (turn == 0)
            return 0;

        idx++;

        int currScore = 0;

        while (idx < piles.size())
            currScore += piles[idx++];

        return dp[idx + 1][m][turn] = currScore;
    }

    if (turn) // Alice Turn
    {
        int res = 0, currScore = 0;
        for (int x = 1; x <= 2 * m && idx + x < piles.size(); x++)
        {
            currScore += piles[idx + x];
            // Alice's takes max score that she can get
            res = max(res, getAliceScore(piles, max(x, m), idx + x, 0, dp) + currScore);
        }

        return dp[idx + 1][m][turn] = res;
    }
    else // Bob Turn
    {
        int res = INT_MAX;
        for (int x = 1; x <= 2 * m && idx + x < piles.size(); x++)
        {
            // Bob will take min score that Alice can get
            res = min(res, getAliceScore(piles, max(x, m), idx + x, 1, dp));
        }

        return dp[idx + 1][m][turn] = res;
    }
}
int stoneGameII(vector<int> &piles)
{
    int n = piles.size();

    vector<vector<vector<int>>> dp(n + 2, vector<vector<int>>(n + 1, vector<int>(2, -1)));

    return getAliceScore(piles, 1, -1, 1, dp);
}
// Approach 2:
int getScore(vector<int> &suffixSum, int m, int idx, vector<vector<int>> &dp)
{
    // if all remaining piles can be taken, then take them all
    if (idx + 2 * m >= suffixSum.size())
        return suffixSum[idx];

    if (dp[idx][m] != -1)
        return dp[idx][m];

    // find min score the other player can get from remaining piles
    int res = INT_MAX;
    for (int x = 1; x <= 2 * m; x++)
    {
        res = min(res, getScore(suffixSum, max(x, m), idx + x, dp));
    }

    // current player's score = totalScore in remaining array - other player's score
    return dp[idx][m] = suffixSum[idx] - res;
}
int stoneGameII(vector<int> &piles)
{
    int n = piles.size();

    vector<vector<int>> dp(n, vector<int>(n, -1));

    vector<int> suffixSum(n);
    suffixSum[n - 1] = piles[n - 1];
    for (int i = n - 2; i >= 0; i--)
        suffixSum[i] = suffixSum[i + 1] + piles[i];

    return getScore(suffixSum, 1, 0, dp);
}

// 1406. Stone Game III
/*
Approach: DP, Time: O(n), Space: O(1)
Same as Stone Game II 2nd approach
Make the suffix array
At each step find the minimum score other player can get

We can remove the dp and get O(1) space, as we only need last 3 results, so we can just 
keep those 3.
*/
int getScore(vector<int> &suffixSum, int idx, vector<int> &dp)
{
    if (idx >= suffixSum.size())
        return 0;

    if (dp[idx] != -1)
        return dp[idx];

    int res = INT_MAX;
    for (int x = 1; x <= 3; x++)
    {
        res = min(res, getScore(suffixSum, idx + x, dp));
    }

    return dp[idx] = suffixSum[idx] - res;
}
string stoneGameIII(vector<int> &stoneValue)
{
    int n = stoneValue.size();

    vector<int> dp(n, -1);

    vector<int> suffixSum(n);
    suffixSum[n - 1] = stoneValue[n - 1];
    for (int i = n - 2; i >= 0; i--)
        suffixSum[i] = suffixSum[i + 1] + stoneValue[i];

    int aliceScore = getScore(suffixSum, 0, dp);
    int bobScore = suffixSum[0] - aliceScore;

    if (aliceScore == bobScore)
        return "Tie";
    else
        return aliceScore > bobScore ? "Alice" : "Bob";
}

// 1510. Stone Game IV
/*
Approach: O(n*sqrt(n)) = O(n^1.5)
At each step start removing squares from n and check if the opponent can
win with the remaining n. 
So, start removing from i = 1 till i*i <= n
If the opponent does not win with that n, that you choose to remove that number

*/
bool canWin(int n, vector<int> &dp)
{
    if (dp[n] != -1)
        return dp[n];

    // if n is a perfect square then current player wins
    int root = sqrt(n);
    if (root * root == n)
        return dp[n] = true;

    // remove squares from n and check if opponent can win
    for (int i = 1; i * i <= n; i++)
    {
        bool canOpponentWin = canWin(n - i * i, dp);

        // if opponent does not win, then you won, so return true
        if (!canOpponentWin)
            return dp[n] = true;
    }

    // you cannot win
    return dp[n] == false;
}
bool winnerSquareGame(int n)
{
    vector<int> dp(n + 1, -1);
    return canWin(n, dp);
}

// 1563. Stone Game V
/*
  6 2 3 4  5  5
  0 6 8 11 15 20 25

*/
// Approach 1: O(n^3)
int stoneGameV(vector<int> &stoneValue)
{
    int n = stoneValue.size();

    vector<int> prefixSum(n);
    prefixSum[0] = stoneValue[0];
    for (int i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + stoneValue[i];

    vector<vector<int>> dp(n, vector<int>(n));

    for (int gap = 1; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; si++, ei++)
        {
            for (int cut = si; cut < ei; cut++)
            {
                int leftSum = si == 0 ? prefixSum[cut] : prefixSum[cut] - prefixSum[si - 1];
                int rightSum = prefixSum[ei] - prefixSum[cut];

                int leftAns = dp[si][cut];
                int rightAns = dp[cut + 1][ei];

                if (leftSum == rightSum)
                    dp[si][ei] = max(dp[si][ei], max(leftSum + leftAns, rightSum + rightAns));
                else if (leftSum < rightSum)
                    dp[si][ei] = max(dp[si][ei], leftSum + leftAns);
                else
                    dp[si][ei] = max(dp[si][ei], rightSum + rightAns);
            }
        }
    }

    return dp[0][n - 1];
}
// Approach 2: O(n^2 * logn)
int stoneGameV(vector<int> &stoneValue)
{
    int n = stoneValue.size();

    vector<int> prefixSum(n);
    prefixSum[0] = stoneValue[0];
    for (int i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + stoneValue[i];

    vector<vector<int>> dp(n, vector<int>(n));

    for (int gap = 1; gap < n; gap++)
    {
        for (int si = 0, ei = gap; ei < n; si++, ei++)
        {
            int totalSum = si == 0 ? prefixSum[ei] : prefixSum[ei] - prefixSum[si - 1];

            int cut = lower_bound(prefixSum.begin(), prefixSum.end(), totalSum / 2) - prefixSum.begin() - 1;

            int leftSum = si == 0 ? prefixSum[cut] : prefixSum[cut] - prefixSum[si - 1];
            int rightSum = prefixSum[ei] - prefixSum[cut];

            int leftAns = dp[si][cut];
            int rightAns = dp[cut + 1][ei];

            if (leftSum == rightSum)
                dp[si][ei] = max(dp[si][ei], max(leftSum + leftAns, rightSum + rightAns));
            else if (leftSum < rightSum)
                dp[si][ei] = max(dp[si][ei], leftSum + leftAns);
            else
                dp[si][ei] = max(dp[si][ei], rightSum + rightAns);
        }
    }

    return dp[0][n - 1];
}

// 97. Interleaving String
/*
Approach 1: O(n^3)
We keep 3 pointers:
i1 = current index of string 1
i2 = current index of string 2
j =  current index of string 3

Now, we just match 
if str1[i1] == str3[j], then call for {i1+1, i2, j+1 }
and, if str2[i2] == str3[j], then call for {i1, i2+1, j+1 }

And when both i1, i2 reach the end of str1 and str2, then return true

Approach 2: O(n^2)
j will always be equal to i1 + i2, because the length of str3
that has been matched is equal to the length of str1 that has been matched + 
length of str2 that has been matched.

*/
// Approach 1: O(n^3)
bool isSubsequence(string &s1, string &s2, string &s3, int i1, int i2, int j, vector<vector<vector<int>>> &dp)
{
    if (i1 == s1.size() && i2 == s2.size())
        return true;

    if (dp[i1][i2][j] != -1)
        return dp[i1][i2][j];

    bool res = false;

    if (i1 < s1.size() && s1[i1] == s3[j])
        res = res || isSubsequence(s1, s2, s3, i1 + 1, i2, j + 1, dp);

    if (i2 < s2.size() && s2[i2] == s3[j])
        res = res || isSubsequence(s1, s2, s3, i1, i2 + 1, j + 1, dp);

    return dp[i1][i2][j] = res;
}
bool isInterleave(string s1, string s2, string s3)
{
    int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();

    if (n3 != n1 + n2)
        return false;

    vector<vector<vector<int>>> dp(n1 + 1, vector<vector<int>>(n2 + 1, vector<int>(n3 + 1, -1)));

    return isSubsequence(s1, s2, s3, 0, 0, 0, dp);
}
// Approach 2: O(n^2)
bool isSubsequence(string &s1, string &s2, string &s3, int i1, int i2, vector<vector<int>> &dp)
{
    if (i1 == s1.size() && i2 == s2.size())
        return true;

    if (dp[i1][i2] != -1)
        return dp[i1][i2];

    bool res = false;
    int j = i1 + i2;

    if (i1 < s1.size() && s1[i1] == s3[j])
        res = res || isSubsequence(s1, s2, s3, i1 + 1, i2, dp);

    if (i2 < s2.size() && s2[i2] == s3[j])
        res = res || isSubsequence(s1, s2, s3, i1, i2 + 1, dp);

    return dp[i1][i2] = res;
}
bool isInterleave(string s1, string s2, string s3)
{
    int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();

    if (n3 != n1 + n2)
        return false;

    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, -1));

    return isSubsequence(s1, s2, s3, 0, 0, dp);
}

int main()
{
    return 0;
}