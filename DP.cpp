#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
#include <unordered_set>

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

// Cut Type(MCM)=============================================================================================

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
int countParenth(string &symb, string &oper)
{
}

// Minimum and Maximum values of an expression with * and +
int minAndMax(string &exp, string &oper)
{
}

// 241. Different Ways to Add Parentheses
vector<int> diffWaysToCompute(string expression)
{
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

// LCS / LPS====================================================================================================

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

// 10. Regular Expression Matching(Not Done Yet)
bool isMatch(string s, string p)
{
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

// Extra========================================================================================
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

int main()
{
    return 0;
}