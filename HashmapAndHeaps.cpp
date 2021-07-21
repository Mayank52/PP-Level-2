#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

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
/*
Approach: Using Max Priority Queue

Algorithm:
1. For every [start, end, height] divide it into [start, -height], [end, height].
    In this way make another array of [x coord, height].
2. Sort this array in increasing order of x coord, if x coord is equal, then in increasing order of height
3. Then use a Max PQ. Push a 0 into PQ initially, and keep a previous height = 0
4. Iterate over the sorted array. For every element
    a. If the height < 0, then it is the starting point
        Push this height into PQ. But the height is < 0, so we push -height
    b. If height is > 0 then it is end point. 
        In this case one building is over, so we remove this height from PQ
        It will not necessarily, be on top. So, we cant use pop(). Instead we use
        Java: pq.remove(h) -> O(n)
        C++: Does not have a way to delelte a specific element, so use a set as a PQ.
    
    Also at each iteration, we check if the current top() i.e. the maximum height in PQ
    is equal to the previous height. If not that means the coord has changed.
    So, we push the currrent x coord, top() height of PQ, into result and update the
    previous height = pq.top();

Complexity is O(n ^ 2) because the remove operation in Java is O(n)
But in C++, multiset, has O(logn) for insertion, removal, find operations
So, complexity will be O(nlogn)


We can use a multiset or set as a PQ
top() -> min element : *pq.begin(), max element: *pq.rbegin()
pop() -> min: pq.erase(pq.begin()), max: pq.erase(pq.rbegin())

Also, we can remove a specific element from set using
pq.erase(pq.find(ele))

But removing a specific element from priority_queue in c++ STL is not possible

According to C++ Reference, the complexity of
multiset::erase(iterator) -> constant
multiset::erase(val) -> logarithmic in container size, plus linear in the number of elements removed.

Also erase(val) removes all ocurrences of the element present in the multiset
*/
vector<vector<int>> getSkyline(vector<vector<int>> &buildings)
{
    vector<pair<int, int>> arr; //{left coord, height}
    //make the array of [x coord, height]
    for (vector<int> &building : buildings)
    {
        int sp = building[0];
        int ep = building[1];
        int h = building[2];

        arr.push_back({sp, -h});
        arr.push_back({ep, h});
    }

    // sort in increasing order of x coord
    sort(arr.begin(), arr.end());

    vector<vector<int>> res;
    multiset<int> pq;
    pq.insert(0);

    int prevHeight = 0;
    for (pair<int, int> &building : arr)
    {
        int x = building.first;
        int h = building.second;

        // starting point of building
        if (h < 0)
            pq.insert(-h);
        // end point of building
        else
            pq.erase(pq.find(h));

        if (prevHeight != *pq.rbegin())
        {
            res.push_back({x, *pq.rbegin()});
            prevHeight = *pq.rbegin();
        }
    }

    return res;
}

// Pairs of Non Coinciding Points
/*
Approach: O(n)
Given condition:
Manhattan Distance = Euclidean Distance
|x2 - x1| + |y2 - y1| = sqrt((x2 - x1)^2 + (y2 - y1)^2)
=> (|x2 - x1| + |y2 - y1|)^2 = (x2 - x1)^2 + (y2 - y1)^2
=> (|x2 - x1|)^2  + (|y2 - y1|)^2 + 2*|x2 - x1|*|y2 - y1| = (x2 - x1)^2 + (y2 - y1)^2
=> 2*|x2 - x1|*|y2 - y1| = 0

On Solving this equation we get,
(x2 - x1)(y2 - y1) = 0
So, we have 3 conditions 
x2 = x1 or 
y2 = y1 or 
x2 = x1 and y2 = y1, this condition is not valid as coinciding points are not allowed

We keep 3 maps: x coords, y coords, {x, y} coords
For each point we do
res += xmap[x] + ymap[y] - 2 * xymap[{x, y}];

So we add count of elements satisfying first 2 conditions, and
remove 2 * 3rd condition points as we would have included the count of same twice
Once from the x coord map, and one from y coord map
*/
int numOfPairs(int X[], int Y[], int N)
{
    // code here
    int res = 0;
    unordered_map<int, int> xmap, ymap;
    map<pair<int, int>, int> xymap;

    for (int i = 0; i < N; i++)
    {
        int x = X[i];
        int y = Y[i];

        res += xmap[x] + ymap[y] - 2 * xymap[{x, y}];

        xmap[x]++;
        ymap[y]++;
        xymap[{x, y}]++;
    }

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
