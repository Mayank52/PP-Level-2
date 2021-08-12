#include <iostream>
#include <vector>
#include <algorithm>

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
int maxHeight(int height[], int width[], int length[], int n)
{
    
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

int main()
{
    return 0;
}