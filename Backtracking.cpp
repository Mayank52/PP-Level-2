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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}