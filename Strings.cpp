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
int KMP(string &str)
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

    return len;
}
string shortestPalindrome(string s)
{
    //make the str = s#s for lps
    string revStr = s;
    reverse(revStr.begin(), revStr.end());
    string str = s + '#' + revStr;

    //find the longest palindrome in given string
    int len = KMP(str);

    //Get the substring to be added, reverse it
    string res = str.substr(len, s.size() - len);
    reverse(res.begin(), res.end());

    //add it to beginning to get the shortest palindrome
    return res + s;
}

//Z - Algo (Pepcoding)
/*
Approach: O(m + n), O(m + n)
Make a Z Array: Longest length prefix which is also a substring (starting a index i)
We, dont include index 0 in substring, otherwise prefix itself will become the substring
Eg: aabaacaabaad
Here aabaa, is a prefix which is also a substring, start from index 6
*/
void zAlgo(string txt, string pat)
{
    string str = pat + "#" + txt;
    int n = str.length();

    vector<int> zarr(n);

    int i = 1;
    int l = 0, r = 0;

    while (i < n)
    {
        if (i <= r)
            zarr[i] = min(r - i + 1, zarr[i - l]);

        while (i + zarr[i] < n && str[i + zarr[i]] == str[zarr[i]])
            zarr[i]++;

        if (i + zarr[i] - 1 > r)
        {
            l = i;
            r = i + zarr[i] - 1;
        }

        //pattern found, print starting index according to string txt
        if (zarr[i] == pat.size())
            cout << i - pat.size() - 1 << endl;

        i++;
    }
}

//www.codechef.com/COOK103B/problems/SECPASS
/*
Approach: Zalgo O(n)
Every time you find a prefix as a substring you update the count of that prefix length
Eg: if length 3 prefix was found as subtring
That means count of length 3,2,1 will be increased by 1 because
that 3 length will always have the smaller lengths included in it.
So the prefix that occurs as a substring max times will always be the smallest non zero value of Z Array.

EG: 
a b c a b a b a b
0 0 0 2 0 2 0 2 0
Here ans is 2

a b c a b c a a b
0 0 0 3 0 0 1 2
Here ans is 1
As the pefix abc which occurs as a substring also contains prefix a,ab
And for prefix ab which has length 2, contains, a
So count of prefix lengths will be
3 - 1
2 - 1 + 1
1 - 1 + 1 + 1 (max)

So ans is 1 mostly, as it is included in all prefixes
Except, if the value of Z Array is same evrywhere, as in eg 1, where all non zero values are 2
*/
int chefAndSecretPassword_(string &str)
{
    int n = str.length();

    vector<int> zarr(n);

    int i = 1;
    int l = 0, r = 0;
    int minLen = n;

    while (i < n)
    {
        if (i <= r)
            zarr[i] = min(r - i + 1, zarr[i - l]);

        while (i + zarr[i] < n && str[i + zarr[i]] == str[zarr[i]])
            zarr[i]++;

        if (i + zarr[i] - 1 > r)
        {
            l = i;
            r = i + zarr[i] - 1;
        }

        if (zarr[i] > 0)
            minLen = min(minLen, zarr[i]);

        i++;
    }

    return minLen;
}
void chefAndSecretPassword()
{
    int t;
    cin >> t;
    while (t-- > 0)
    {
        int n;
        cin >> n;
        string str;
        cin >> str;

        int len = chefAndSecretPassword_(str);
        string res = str.substr(0, len);
        cout << res << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}