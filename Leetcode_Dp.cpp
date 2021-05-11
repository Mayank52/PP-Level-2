#include <iostream>
#include <vector>

using namespace std;

void display2d(vector<vector<int>> &dp)
{
    for (int i = 0; i < dp.size(); i++)
    {
        for (int j = 0; j < dp[0].size(); j++)
            cout << dp[i][j];
        cout << endl;
    }
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