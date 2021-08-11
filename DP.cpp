#include <iostream>
#include <vector>

using namespace std;

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

// 673. Number of Longest Increasing Subsequence

int findNumberOfLIS(vector<int> &nums)
{
    int n = nums.size();

    vector<pair<int, int>> dp(n, {1, 1});   // { length, count of subseq with that length}
    int res = 0, count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[i] > nums[j])
            {
                if (dp[i].first == dp[j].first + 1)
                    dp[i].second += dp[j].second;
                else if (dp[i].first < dp[j].first + 1)
                {
                    dp[i].first = dp[j].first + 1;
                    dp[i].second = dp[j].second;
                }
            }
        }

        if (dp[i].first > res)
        {
            res = dp[i].first;
            count = dp[i].second;
        }
        else if (dp[i].first == res)
            count += dp[i].second;
    }

    return count;
}

int main()
{
    return 0;
}