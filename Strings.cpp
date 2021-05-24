#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 1392. Longest Happy Prefix (LPS)
/*
Approach: O(n), O(n), (Standard Algo)
A string is a proper prefix, if it is also a suffix
Eg: aabaacaabaad
Here, lps is aabaa, as it a prefix as well as a suffix
We see the suffix from left. Like in 'leetcodeleet', lps is 'leet'
*/
string longestPrefix(string str)
{
    int n = str.size();
    vector<int> lps(n);
    int len = 0, i = 1;

    while (i < n)
    {
        if (str[i] == str[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len > 0)
                len = lps[len - 1];
            else
                i++;
        }
    }

    string res = str.substr(0, len);

    return res;
}

//KMP Algo (In Strings.java)

// 214. Shortest Palindrome
/*
Approach: O(n), O(n)
Using KMP, which is an application of LPS

A String is palindrome if after reversing it, it remains the same
So, use lps to find the longest substring in the given string which is a palindrome

Make a string str = s + # + reverse(s)
Use LPS, it returns the longest palindrome length of the string s from index 0,
now we will take the remaining substring, reverse it and append it to start of string s

Eg: aabaacde
Str = aabaacde#edcaabaa

Lps finds string aabaa of length 5
Now, the smallest string to be added is of length size(s) - len = 8 - 5 = 3
which is cde
So ans is reverse of cde + given string s
This is the shortest palindrome
*/
string shortestPalindrome(string s)
{
    //Make string = s + # + reverse(s)
    string revStr = s;
    reverse(revStr.begin(), revStr.end());
    string str = s + '#' + revStr;

    //LPS
    int n = str.size();
    vector<int> lps(n);
    int len = 0, i = 1;

    while (i < n)
    {
        if (str[i] == str[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len > 0)
                len = lps[len - 1];
            else
                i++;
        }
    }

    //Get the substring to be added, reverse it
    string res = str.substr(len, s.size() - len);
    reverse(res.begin(), res.end());

    //add it to beginning and return
    return res + s;
}

//Z - Algo
/*
Approach: O(n), O(n)
Make a Z Array: Longest length prefix which is also a substring (starting a index i)
We, dont include index 0 in substring, otherwise prefix itself will become the substring
Eg: aabaacaabaad
Here aabaa, is a prefix which is also a substring, start from index 6
*/
void zAlgo(string str){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}