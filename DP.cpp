#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

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
// Approach 2: O(nlogn)(Not Complete)
int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
{
    int n = startTime.size();

    vector<vector<int>> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = {startTime[i], endTime[i], profit[i]};

    sort(arr.begin(), arr.end());

    vector<int> dp;
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        int lo = 0, hi = dp.size();

        while (lo < hi)
        {
            int mid = lo + (hi - lo) / 2;

            if (dp[lo] < dp[mid])
        }

        res = max(res, dp[i]);
    }

    return res;
}

// Include/Exclude(P & C)================================================================================

// 514 · Paint Fence
/*
Approach: O(n)
Keep 2 counts: 
1. Number of ways to paint 2 fences with same color
2. Number of ways to paint 2 fences with different color

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

// =======================================================================================================
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
Approach: O(n^3)

*/
int pickup(vector<vector<int>> &grid, int row1, int col1, int row2, vector<vector<vector<int>>> &dp)
{
    int col2 = row1 + col1 - row2;

    // out of range indexes
    if (row1 >= grid.size() || col1 >= grid[0].size() || row2 >= grid.size() || col2 >= grid[0].size() || grid[row1][col1] == -1 || grid[row2][col2] == -1)
        return -1;

    // obstacle
    if (row1 == grid.size() - 1 && col1 == grid[0].size() - 1 && row2 == grid.size() - 1 && col2 == grid[0].size() - 1)
        return dp[row1][col1][row2] = grid[row1][col1];

    if (dp[row1][col1][row2] != -1)
        return dp[row1][col1][row2];

    int myAns;
    if (row1 == row2 && col1 == col2)
        myAns = grid[row1][col1];
    else
        myAns = grid[row1][col1] + grid[row2][col2];

    int temp1 = pickup(grid, row1 + 1, col1, row2 + 1, dp);
    int temp2 = pickup(grid, row1 + 1, col1, row2, dp);
    int temp3 = pickup(grid, row1, col1 + 1, row2 + 1, dp);
    int temp4 = pickup(grid, row1, col1 + 1, row2, dp);

    int res = max(max(temp1, temp2), max(temp3, temp4));

    return dp[row1][col1][row2] = (res == -1) ? res : res + myAns;
}
int cherryPickup(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(n, -1)));
    int res = pickup(grid, 0, 0, 0, dp);

    return res == -1 ? 0 : res;
}

int main()
{
    return 0;
}