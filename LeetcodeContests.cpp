#include <bits/stdc++.h>
using namespace std;

// 1894. Find the Student that Will Replace the Chalk
int chalkReplacer(vector<int> &chalk, int k)
{
    long long totalChalk = 0;
    for (int ele : chalk)
        totalChalk += ele;

    k %= totalChalk;

    for (int i = 0; i < chalk.size(); i++)
    {
        k -= chalk[i];
        if (k < 0)
            return i;
    }

    return 0;
}

// 1893. Check if All the Integers in a Range Are Covered
bool isCovered(vector<vector<int>> &ranges, int left, int right)
{
    int currLeft = left, currRight = right;
    for (int i = 0; i < ranges.size(); i++)
    {
        //completely out of range
        if (currLeft > ranges[i][1] || currRight < ranges[i][0])
            continue;

        //interval over
        if (currLeft > currRight)
            return true;

        if (currLeft >= ranges[i][0])
            currLeft = max(currLeft, ranges[i][1]) + 1;

        if (currRight <= ranges[i][1])
            currRight = min(currRight, ranges[i][0]) - 1;
    }

    if (currLeft > currRight)
        return true;

    return false;
}

int main()
{
    return 0;
}