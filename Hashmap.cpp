#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

// 914. X of a Kind in a Deck of Cards
/*
Approach: 
Make a frequency map of all elements in array
Then find the gcd of all frequencies
Gcd is the smallest group size you can divide the cards into
If the gcd >= 2, then return true
*/
int gcd(int a, int b)
{
    if (b == 0)
        return a;

    return gcd(b, a % b);
}
bool hasGroupsSizeX(vector<int> &deck)
{
    unordered_map<int, int> freq;
    for (int num : deck)
    {
        freq[num]++;
    }

    int ogcd = freq[deck[0]];
    for (auto ele : freq)
    {
        ogcd = gcd(ogcd, ele.second);
    }

    return ogcd >= 2;
}

// 560. Subarray Sum Equals K
int subarraySum(vector<int> &nums, int k)
{
    unordered_map<int, int> mp; //{prefix sum, count}

    int currSum = 0, count = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        currSum += nums[i];

        if (currSum == k)
            count++;

        if (mp.find(currSum - k) != mp.end())
            count += mp[currSum - k];

        mp[currSum]++;
    }

    return count;
}

// https://codeforces.com/contest/1520/problem/D#
/*
Approach: O(N)
We are given aj - ai = j - i
So, aj - j = ai - i

Now, just use a hashmap, and count the occurence of arr[i] - i 
for all indexes.
And for all indexes, to find count of elements satisfying the given condition, we do
count += mp[arr[i] - i]

*/
void sameDifferences()
{
    int t;
    cin >> t;
    while (t-- > 0)
    {
        int n;
        cin >> n;

        unordered_map<int, int> mp;
        long long count = 0;
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;

            count += mp[x - i];

            mp[x - i]++;
        }

        cout << count << endl;
    }
}

// 974. Subarray Sums Divisible by K
/*
Approach: O(n)
Let there be a subarray (i, j) whose sum is divisible by k
  sum(i, j) = sum(0, j) - sum(0, i-1)
Sum for any subarray can be written as q*k + rem where q 
is a quotient and rem is remainder
Thus,     
    sum(i, j) = (q1 * k + rem1) - (q2 * k + rem2)
    sum(i, j) = (q1 - q2)k + rem1-rem2
     
We see, for sum(i, j) i.e. for sum of any subarray to be
divisible by k, the RHS should also be divisible by k.
(q1 - q2)k is obviously divisible by k, for (rem1-rem2) to 
follow the same, rem1 = rem2 where
    rem1 = Sum of subarray (0, j) % k
    rem2 = Sum of subarray (0, i-1) % k 

for (rem1 - rem2) % k == 0
Case 1:
rem1 - rem2 = 0
So, rem1 = rem2

Case 2:
rem1 - rem2 = k
So, rem1 = rem2 + k

So, for -ve remainders we do (rem+k) and update that in map

So, we update the count of remainder of each prefix sum in map
To handle -ve remainders, we do
rem = ((sum % k) + k) % k
If the rem is +ve then +k)%k will give back the same number
If it is -ve then, this will make it +ve

Then for each index, we do
count += mp[rem]

Also, as we are counting remainders, so it num % k will never we greater than k
So, instead of a map, we can just use an array of size k
*/
int subarraysDivByK(vector<int> &nums, int k)
{
    vector<int> mp(k); //{prefix sum, count}

    int currSum = 0, count = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        currSum += nums[i];

        if (currSum % k == 0)
            count++;

        count += mp[(currSum % k + k) % k];

        mp[(currSum % k + k) % k]++;
    }

    return count;
}

// Subarrays with equal 1s and 0s
/*
Approach 1: O(n)
Do, sum += 1, when arr[i] == 1
And sum -= 1, when arr[i] == 0

Then just count subarrays with sum = 0

Approach 2: O(n)
For index i and j
We want count0(i, j) = count1(i, j)
=> count0(j) - count0(i) = count1(j) - count1(i)
=> count0(j) - count1(j) = count0(i) - count1(i)

So, we maintain a count of 0 and 1
And for each index 
ans += mp[count0 - count1]

And update count0 - count1 in map
*/
// Approach 1:
long long int countSubarrWithEqualZeroAndOne(int arr[], int n)
{
    //Your code here
    unordered_map<int, int> mp;

    long long sum = 0, count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
            sum -= 1;
        else
            sum += 1;

        if (sum == 0)
            count++;

        count += mp[sum];

        mp[sum]++;
    }

    return count;
}
// Approach 2:
long long int countSubarrWithEqualZeroAndOne(int arr[], int n)
{
    //Your code here
    unordered_map<int, int> mp;

    long long count0 = 0, count1 = 0, res = 0;
    for (int i = 0; i < n; i++)
    {

        if (arr[i] == 0)
            count0++;
        else
            count1++;

        if (count0 == count1)
            res++;

        res += mp[count0 - count1];

        mp[count0 - count1]++;
    }

    return res;
}

// Equal 0, 1 and 2
/*
Approach: O(n)
For index i and j
We want count0(i, j) = count1(i, j) and count0(i, j) = count2(i, j)
=> count0(j) - count0(i) = count1(j) - count1(i) and count0(j) - count0(i) = count2(j) - count2(i)
=> count0(j) - count1(j) = count0(i) - count1(i) and count0(j) - count2(j) = count0(i) - count2(i)


So, we maintain a count of 0, 1 and 2
And for each index 
ans += mp[{count0 - count1, count0 - count2}]
In the map we maintain a pair of {count0 - count1, count0 - count2}

And update {count0 - count1, count0 - count2} in map
*/
long long getSubstringWithEqual012(string str)
{
    map<pair<int, int>, int> mp; // {count0 - count1, count0 - count2 : count}

    long long count0 = 0, count1 = 0, count2 = 0, res = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '0')
            count0++;
        else if (str[i] == '1')
            count1++;
        else
            count2++;

        if (count0 == count1 && count0 == count2)
            res++;

        res += mp[{count0 - count1, count0 - count2}];

        mp[{count0 - count1, count0 - count2}]++;
    }

    return res;
}

// 485. Max Consecutive Ones
int findMaxConsecutiveOnes(vector<int> &nums)
{
    int res = 0, currCount = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == 0)
            currCount = 0;
        else
            currCount++;

        res = max(res, currCount);
    }

    return res;
}

// 218. The Skyline Problem
vector<vector<int>> getSkyline(vector<vector<int>> &buildings)
{
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
