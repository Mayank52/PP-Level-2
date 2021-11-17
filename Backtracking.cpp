#include <bits/stdc++.h>
using namespace std;

// 290. Word Pattern
/*
Make 2 hashmaps
Map the char in pattern to word, and the word to char
Then for each char check if it is mapped to the same word,
and the word is mapped to same char
Eg:
pattern = "abba", s = "dog cat cat dog"

1. a->dog, dog->a
2. b->cat, cat->b
3. b is already present, and mapped to cat
4. a is already present and mapped to dog

pattern = "abc", s = "dog cat dog"

1. a->dog, dog->a
2. b->cat, cat->b
3. c is not present but dog is present and mapped to a, so false
*/
bool wordPattern(string pattern, string s)
{
    unordered_map<char, string> mp1;
    unordered_map<string, char> mp2;
    vector<string> words;

    //make the words array
    string word = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            words.push_back(word);
            word = "";
        }
        else
            word += s[i];
    }
    words.push_back(word);

    //if the number of characters in pattern != number of words, return false
    if (words.size() != pattern.size())
        return false;

    for (int i = 0; i < pattern.size(); i++)
    {
        //if char is present, but different word
        if (mp1.find(pattern[i]) != mp1.end())
        {
            if (mp1[pattern[i]] != words[i])
                return false;
        }
        //if word is present but different char
        else if (mp2.find(words[i]) != mp2.end())
        {
            if (mp2[words[i]] != pattern[i])
                return false;
        }
        //map word:char and char:word
        else
        {
            mp1[pattern[i]] = words[i];
            mp2[words[i]] = pattern[i];
        }
    }

    return true;
}

// 829 · Word Pattern II (Lintcode)
bool wordPatternMatch(string &pattern, string &str, int pidx, int sidx, unordered_map<char, string> &mp1, unordered_map<string, char> &mp2)
{
    // write your code here
    if (pidx == pattern.size() && sidx == str.size())
        return true;
    if (pidx == pattern.size() || sidx == str.size())
        return false;

    char ch = pattern[pidx];
    bool res = false;

    //if char is already mapped to a word
    if (mp1.find(ch) != mp1.end())
    {
        string mapWord = mp1[ch];

        //if remaining string size is less than the required word
        if (str.size() - sidx < mapWord.size())
            return false;

        //get the word and compare it to the mapped word
        string word = str.substr(sidx, mapWord.size());
        if (mapWord != word)
            return false;

        //make next call
        res = res || wordPatternMatch(pattern, str, pidx + 1, sidx + word.size(), mp1, mp2);
    }
    else
    {
        //make a word with each remaining char in string
        string word = "";
        for (int i = sidx; i < str.size(); i++)
        {
            word += str[i];
            //if the word is already mapped to another char, skip it
            if (mp2.find(word) != mp2.end())
                continue;

            //else map it to pattern char, and make next call
            mp1[ch] = word;
            mp2[word] = ch;
            res = res || wordPatternMatch(pattern, str, pidx + 1, i + 1, mp1, mp2);
            mp1.erase(ch);
            mp2.erase(word);
        }
    }

    return res;
}
bool wordPatternMatch(string &pattern, string &str)
{
    // write your code here
    unordered_map<char, string> mp1;
    unordered_map<string, char> mp2;
    return wordPatternMatch(pattern, str, 0, 0, mp1, mp2);
}

// Pattern Matching (Pepcoding)
void wordPatternMatch(string &pattern, string &str, int pidx, int sidx, unordered_map<char, string> &mp1, unordered_map<string, char> &mp2)
{
    // write your code here
    if (pidx == pattern.size() && sidx == str.size())
    {
        bool seen[26] = {false};
        for (int i = 0; i < pattern.size(); i++)
        {
            char ch = pattern[i];
            if (!seen[ch - 'a'])
            {
                seen[ch - 'a'] = true;
                cout << ch << " -> " << mp1[ch] << ", ";
            }
        }
        cout << "." << endl;
        return;
    }
    if (pidx == pattern.size() || sidx == str.size())
        return;

    char ch = pattern[pidx];

    //if char is already mapped to a word
    if (mp1.find(ch) != mp1.end())
    {
        string mapWord = mp1[ch];

        //if remaining string size is less than the required word
        if (str.size() - sidx < mapWord.size())
            return;

        //get the word and compare it to the mapped word
        string word = str.substr(sidx, mapWord.size());
        if (mapWord != word)
            return;

        //make next call
        wordPatternMatch(pattern, str, pidx + 1, sidx + word.size(), mp1, mp2);
    }
    else
    {
        //make a word with each remaining char in string
        string word = "";
        for (int i = sidx; i < str.size(); i++)
        {
            word += str[i];
            //if the word is already mapped to another char, skip it
            if (mp2.find(word) != mp2.end())
                continue;

            //else map it to pattern char, and make next call
            mp1[ch] = word;
            mp2[word] = ch;
            wordPatternMatch(pattern, str, pidx + 1, i + 1, mp1, mp2);
            mp1.erase(ch);
            mp2.erase(word);
        }
    }
}
void wordPatternMatch(string &pattern, string &str)
{
    // write your code here
    unordered_map<char, string> mp1;
    unordered_map<string, char> mp2;
    wordPatternMatch(pattern, str, 0, 0, mp1, mp2);
}

//Leetcode Practice====================================================================
// 1863. Sum of All Subset XOR Totals
int totalSum = 0;
void subsets(vector<int> &nums, int idx, int xorSum)
{
    if (idx == nums.size())
    {
        totalSum += xorSum;
        return;
    }

    subsets(nums, idx + 1, xorSum ^ nums[idx]);
    subsets(nums, idx + 1, xorSum);
}
int subsetXORSum(vector<int> &nums)
{
    subsets(nums, 0, 0);
    return totalSum;
}

// 1688. Count of Matches in Tournament
int numberOfMatches(int n)
{
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;

    int currMatches = n / 2;

    if (n % 2 == 0)
        currMatches += numberOfMatches(n / 2);
    else
        currMatches += numberOfMatches(n / 2 + 1);

    return currMatches;
}

// 78. Subsets
// Approach 1: Backtracking (Method 1)
vector<vector<int>> res;
void subsets(vector<int> &nums, int idx, vector<int> &subset)
{
    if (idx == nums.size())
    {
        res.push_back(subset);
        return;
    }

    subset.push_back(nums[idx]);
    subsets(nums, idx + 1, subset);
    subset.pop_back();

    subsets(nums, idx + 1, subset);
}
vector<vector<int>> subsets(vector<int> &nums)
{
    vector<int> subset;
    subsets(nums, 0, subset);
    return res;
}
// Approach 2: Backtracking (Method 2)
void subsets(vector<int> &nums, int idx, vector<int> &subset)
{
    res.push_back(subset);
    for (int j = i; j < nums.size(); j++)
    {
        subset.push_back(nums[j]);
        subsets(nums, j + 1, subset);
        subset.pop_back();
    }
}
vector<vector<int>> subsets(vector<int> &nums)
{
    vector<int> subset;
    subsets(nums, 0, subset);
    return res;
}
// Approach 3: Iterative
/*
Approach: 
Eg: [1,2,3]
So, we iterate over all elements
And for each element we add it to all available subsets to get a new subset

Initially: []
1: [], [1]
2: adds [2], [1,2]
3: adds [3], [1,3], [2,3], [1,2,3]

So, total, [],[1],[2],[1,2],[3],[1,3], [2,3], [1,2,3]
*/
vector<vector<int>> subsets(vector<int> &nums)
{
    vector<vector<int>> res;
    res.push_back({});

    for (int i = 0; i < nums.size(); i++)
    {
        int n = res.size();
        for (int j = 0; j < n; j++)
        {
            res.push_back(res[j]);
            res[res.size() - 1].push_back(nums[i]);
        }
    }

    return res;
}
// Approach 4: Bit Manipulation
/*
Approach: O(2^n)
If size of array = n
Then no. of subsets = 2^n
So, we iterate from 0 to 2^n
And for each number we check its bit representation
Every bit that is 1, we add that index number into the current subset

Eg: [1,2,3]
n = 3,
Iterate from 0 to 2^3 = 8

For 0, bits = 0 0 0, so empty set
1 = 0 0 1 = So, only 3 gets added
2 = 0 1 0 = So, only 2 gets added
3 = 0 1 1 = So, 2, 3 get added

And So on...
*/
vector<vector<int>> subsets(vector<int> &nums)
{
    vector<vector<int>> res;

    for (int i = 0; i < (1 << nums.size()); i++)
    {
        int n = i, k = nums.size() - 1;
        vector<int> subset;

        while (n > 0)
        {
            // if current bit is set then add this index element into subset
            if (n & 1)
                subset.push_back(nums[k]);

            k--;
            n >>= 1;
        }

        res.push_back(subset);
    }

    return res;
}

// 90. Subsets II
/*
Approach 1: Backtracking, O(nlogn + 2^n) = O(nlogn)
Sort the array to get all duplicates together
Then each step, we put every element at the current position and make the next call
To prevent duplicates, we only add an element if it is not equal to its previous element

Approach 2: Iterative
Sort the array
Then for each element first count its frequency
Then for each subset till now, add the current element to it 1 time, 2 time.....count times
And add all those new subsets to result

Eg: [1,2,2]
When you get 2 and have already, [], [1]
We will get [2],[2,2], [1,2], [1,2,2] new subsets
*/
// Approach 1: Backtracking
void subsets(vector<int> &nums, int idx, vector<vector<int>> &res, vector<int> &subset)
{
    res.push_back(subset);

    for (int i = idx; i < nums.size(); i++)
    {
        if (i == idx || nums[i] != nums[i - 1])
        {
            subset.push_back(nums[i]);
            subsets(nums, i + 1, res, subset);
            subset.pop_back();
        }
    }
}
vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    vector<vector<int>> res;
    vector<int> subset;

    sort(nums.begin(), nums.end());

    subsets(nums, 0, res, subset);

    return res;
}
// Approach 2: Iterative
vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    vector<vector<int>> res;
    res.push_back({});

    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++)
    {
        int count = 1;
        while (i < nums.size() - 1 && nums[i] == nums[i + 1])
        {
            count++;
            i++;
        }

        int n = res.size();
        for (int j = 0; j < n; j++)
        {
            vector<int> subset = res[j];

            for (int k = 0; k < count; k++)
            {
                subset.push_back(nums[i]);
                res.push_back(subset);
            }
        }
    }

    return res;
}

// 22. Generate Parentheses
vector<string> res;
void generateParenthesis(int n, int openCount, int closeCount, string ans)
{
    if (openCount + closeCount == 2 * n)
    {
        res.push_back(ans);
        return;
    }

    //If open brackets count > close bracket count -> add a close bracket
    if (openCount > closeCount)
        generateParenthesis(n, openCount, closeCount + 1, ans + ')');

    //if open bracket count < total bracket count -> add a open bracket
    if (openCount < n)
        generateParenthesis(n, openCount + 1, closeCount, ans + '(');
}
vector<string> generateParenthesis(int n)
{
    generateParenthesis(n, 0, 0, "");
    return res;
}

// 797. All Paths From Source to Target
vector<vector<int>> res;
void dfs(vector<vector<int>> &graph, int u, vector<int> &path)
{
    if (u == graph.size() - 1)
    {
        path.push_back(u);
        res.push_back(path);
        path.pop_back();
        return;
    }

    path.push_back(u);

    for (int v : graph[u])
    {
        dfs(graph, v, path);
    }

    path.pop_back();
}
vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
{
    int n = graph.size();

    //graph is acyclic, so no need to mark visited nodes, as there are no cycles
    vector<int> path;
    dfs(graph, 0, path);

    return res;
}

// 1723. Find Minimum Time to Finish All Jobs
int res = INT_MAX;
void minimumTimeRequired(vector<int> &jobs, int k, int idx, vector<int> &workers, int maxTime)
{
    //Optimization - 2
    //if the current maxTime is already more than min res, then no need to check further
    if (maxTime > res)
        return;

    if (idx == jobs.size())
    {
        if (k == 0)
        {
            res = min(res, maxTime);
        }

        return;
    }

    for (int i = 0; i < workers.size(); i++)
    {
        if (workers[i] == 0)
        {
            workers[i] += jobs[idx];
            minimumTimeRequired(jobs, k - 1, idx + 1, workers, max(maxTime, workers[i]));
            workers[i] -= jobs[idx];

            //to prevent permutations
            break;
        }
        else
        {
            workers[i] += jobs[idx];
            minimumTimeRequired(jobs, k, idx + 1, workers, max(maxTime, workers[i]));
            workers[i] -= jobs[idx];
        }
    }
}
int minimumTimeRequired(vector<int> &jobs, int k)
{
    res = INT_MAX;

    //Optimization - 1
    //sort jobs in descending order, so that greatest time jobs get assigned first
    //so you will get the max possible time earlier
    sort(jobs.begin(), jobs.end(), greater<int>());

    vector<int> workers(k, 0);
    minimumTimeRequired(jobs, k, 0, workers, 0);

    return res;
}

// CrossWord Puzzle (https://www.hackerrank.com/challenges/crossword-puzzle/problem)
bool canPlaceV(vector<string> &arr, string &word, int sr, int sc)
{
    // enough cells available
    if (sr + word.size() - 1 >= arr.size())
        return false;

    // either each index empty OR the right character already present
    for (int i = 0; i < word.length(); i++)
    {
        if (arr[sr + i][sc] != '-' && arr[sr + i][sc] != word[i])
            return false;
    }

    return true;
}
bool canPlaceH(vector<string> &arr, string &word, int sr, int sc)
{
    // enough cells available
    if (sc + word.size() - 1 >= arr[0].size())
        return false;

    // either each index empty OR the right character already present
    for (int j = 0; j < word.length(); j++)
    {
        if (arr[sr][sc + j] != '-' && arr[sr][sc + j] != word[j])
            return false;
    }

    return true;
}
void placeV(vector<string> &arr, string &word, int r, int c)
{
    for (int i = 0; i < word.size(); i++)
    {
        arr[i + r][c] = word[i];
    }
}
void unplaceV(vector<string> &arr, string &word, int r, int c)
{
    for (int i = 0; i < word.size(); i++)
    {
        arr[i + r][c] = '-';
    }
}
void placeH(vector<string> &arr, string &word, int r, int c)
{
    for (int j = 0; j < word.size(); j++)
    {
        arr[r][j + c] = word[j];
    }
}
void unplaceH(vector<string> &arr, string &word, int r, int c)
{
    for (int j = 0; j < word.size(); j++)
    {
        arr[r][j + c] = '-';
    }
}
bool solveCrossword(vector<string> &arr, vector<string> &words, int idx, vector<string> &solved)
{
    if (idx == words.size())
    {
        solved = arr;
        return true;
    }

    string word = words[idx];

    bool res = false;

    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[0].size(); j++)
        {
            if (canPlaceH(arr, word, i, j))
            {
                placeH(arr, word, i, j);
                res = res || solveCrossword(arr, words, idx + 1, solved);
                unplaceH(arr, word, i, j);
            }
            if (canPlaceV(arr, word, i, j))
            {
                placeV(arr, word, i, j);
                res = res || solveCrossword(arr, words, idx + 1, solved);
                unplaceV(arr, word, i, j);
            }
        }
    }

    return res;
}
vector<string> crosswordPuzzle(vector<string> crossword, string words)
{
    vector<string> solved;
    vector<string> wordList;

    string currWord = "";
    for (char ch : words)
    {
        if (ch == ';')
        {
            wordList.push_back(currWord);
            currWord = "";
        }
        else
            currWord += ch;
    }
    wordList.push_back(currWord);

    solveCrossword(crossword, wordList, 0, solved);

    return solved;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}