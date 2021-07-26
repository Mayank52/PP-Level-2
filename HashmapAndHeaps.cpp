#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
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

// Check Arithmetic Progression (https://practice.geeksforgeeks.org/problems/check-arithmetic-progression1842/1)
/*
Approach: O(n)
Find the min and second min
Then common diff = second min - min
Put all elements in array into set.
Now using the AP formula 
ai = a + i * d

We will check if all these values are in the set
*/
bool checkIsAP(int arr[], int n)
{
    unordered_set<int> ap;
    int a = INT_MAX, b = INT_MAX, d;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < a)
        {
            b = a;
            a = arr[i];
        }
        else if (arr[i] < b)
            b = arr[i];

        ap.insert(arr[i]);
    }

    d = b - a;

    for (int i = 0; i < n; i++)
    {
        int ai = a + i * d;
        if (ap.find(ai) == ap.end())
            return false;
    }

    return true;
}

// 954. Array of Doubled Pairs
/*
Approach: O(nlogn)
Sort the array
Then for each -ve number we will have to check for its num / 2
And for +ve its num * 2

Eg:
[4,-2,2,-4]
Sort: [-4, -2, 2, 4]
-4 pairs with -2
and 2 with 4
*/
bool canReorderDoubled(vector<int> &arr)
{
    if (arr.size() == 0)
        return true;

    int n = arr.size();

    sort(arr.begin(), arr.end());

    unordered_map<double, int> mp;

    for (int i = 0; i < n; i++)
    {
        mp[arr[i]]++;
    }

    for (int i = 0; i < n; i++)
    {
        if (mp[arr[i]] == 0)
            continue;

        // if +ve check for num * 2
        if (arr[i] >= 0)
        {
            if (mp[arr[i] * 2] == 0)
                return false;
            else
                mp[arr[i] * 2]--;
        }
        // if -ve check for num/2
        else
        {
            if (mp[arr[i] / 2.0] == 0)
                return false;
            else
                mp[arr[i] / 2.0]--;
        }

        mp[arr[i]]--;
    }

    return true;
}

// Tricky Sorting Cost (https://practice.geeksforgeeks.org/problems/morning-assembly3038/1)
/*
Approach: O(n)
We have to find the longest increasing subsequence
Then the answer would be arr.size() - len of subseq
Because the elements of that subsequence are already in relatively correct order
So, these are the elements that dont need to be moved.
As, if we just put the other elements at start or end one at time
then the elements of subsequence will automatically be at the correct position

Eg:
[4, 3, 1, 2, 5, 6, 8 ,7]
Here longest seq = 4 5 6 7
So, if we all elements except these

*/
int sortingCost(int N, int arr[])
{
    unordered_map<int, int> mp;
    int maxLen = 0;

    for (int i = 0; i < N; i++)
    {
        mp[arr[i]] = mp[arr[i] - 1] + 1;
        maxLen = max(maxLen, mp[arr[i]]);
    }

    return N - maxLen;
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

// 1001. Grid Illumination
/*
Approach: Time: O(length of lamps array + length of queries array), Space: O(n^2)
Preprocessing: O(length of lamps array)
Query: O(8) = O(1)

In the given question, the cell whose lamp is turned ON is different and
the cell that is illuminated is different. Cells are illuminated if its own lamp is on
or one of the lamps in its 8 directions is on.
If a cell is illuminated, it does not mean that its lamp is on.
For each qeury we have to tell if the cell is illuminated, and then if its lamp is on we turn it off
And we also turn off lamps in its 8 adjacent cells.

Keep 5 hashmaps for: 
row: r
column: c
diagonal 1 (left to right diagonal):  r + c
diagonal 2 (right to left diagonal) : r - c 
cells: r * n + c

In the row, col, diag1, diag2, we keep the count of lamps turned ON in that row, col, diag1, diag2
In the cells map, we keep true or false, if the lamp in that cell is ON(true) or OFF(false)

Then for each query just check if the count in the row, col, diag1, diag2, is > 0
Then there is a lamp ON in one of those directions. So, it is illuminated.
Then turn off its own and adjacent lamps.
*/
unordered_map<long long, long long> rows, cols, diag1, diag2;
unordered_map<long long, bool> cells;
void turnOn(long long r, long long c, int n)
{
    // increase count for ON lamps
    rows[r]++;
    cols[c]++;
    diag1[r + c]++;
    diag2[r - c]++;
    cells[r * n + c] = true;
}
void turnOff(long long r, long long c, int n)
{
    // decrease count for ON lamps
    if (rows[r] > 0)
        rows[r]--;
    if (cols[c] > 0)
        cols[c]--;
    if (diag1[r + c] > 0)
        diag1[r + c]--;
    if (diag2[r - c] > 0)
        diag2[r - c]--;
    if (cells[r * n + c])
        cells[r * n + c] = false;
}
vector<int> gridIllumination(int n, vector<vector<int>> &lamps, vector<vector<int>> &queries)
{
    // turn on given lamps
    for (int i = 0; i < lamps.size(); i++)
    {
        long long r = lamps[i][0];
        long long c = lamps[i][1];

        // there may be duplicate values in lamps, so dont count the same lamp twice
        if (!cells[r * n + c])
            turnOn(r, c, n);
    }

    vector<int> res;
    int dir[8][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

    for (vector<int> &q : queries)
    {
        long long r = q[0];
        long long c = q[1];

        // this cell is illuminated
        if (rows[r] || cols[c] || diag1[r + c] || diag2[r - c])
        {
            res.push_back(1);

            // turn off this lamp
            if (cells[r * n + c])
                turnOff(r, c, n);

            // turn OFF neighboring lamps, if they are ON
            for (int d = 0; d < 8; d++)
            {
                long long x = r + dir[d][0];
                long long y = c + dir[d][1];

                if (x >= 0 && y >= 0 && x < n && y < n && cells[x * n + y])
                {
                    turnOff(x, y, n);
                }
            }
        }
        // not illuminated
        else
            res.push_back(0);
    }

    return res;
}

// 554. Brick Wall
/*
Approach: O(n * m), O(m)
Count the number of gaps for each column
Then the minimum number of bricks crossed = number of rows of bricks - max gap count
*/
int leastBricks(vector<vector<int>> &wall)
{
    unordered_map<int, int> gapCount;
    int maxCount = 0;

    for (int i = 0; i < wall.size(); i++)
    {
        int col = 0; // column number for the current gap
        for (int j = 0; j < wall[i].size() - 1; j++)
        {
            col += wall[i][j];
            gapCount[col]++;

            maxCount = max(maxCount, gapCount[col]);
        }
    }

    return wall.size() - maxCount;
}

// 871. Minimum Number of Refueling Stops
/*
Approach: O(nlogn)
Use Max Priority Queue
We keep going and when we dont have enough fuel for the next station, 
then we see which of the stations till now have the max fuel
and we refuel using that fuel

So, For each station we push its fuel into the PQ.
At each station find out the fuel left after reaching that station
If fuel < 0, then refuel with top of PQ until you have > 0 fuel
Then go to the next station.

At the end if we dont have  enough fuel, and the PQ is also empty
then answer is -1.
*/
int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations)
{
    priority_queue<int, vector<int>> pq;

    int count = 0, prevPos = 0;
    for (int i = 0; i < stations.size(); i++)
    {
        // find the fuel left after reaching this station
        startFuel -= (stations[i][0] - prevPos);
        prevPos = stations[i][0];

        // if you have < 0 fuel left, then refuel
        while (startFuel < 0 && pq.size() > 0)
        {
            startFuel += pq.top();
            pq.pop();

            count++;
        }

        // if still no fuel, then return -1
        if (startFuel < 0)
            return -1;

        // add this station's fuel into the PQ
        pq.push(stations[i][1]);
    }

    // refuel if you dont have enough fuel to react destination
    while (pq.size() > 0 && prevPos + startFuel < target)
    {
        startFuel += pq.top();
        pq.pop();

        count++;
    }

    return prevPos + startFuel >= target ? count : -1;
}

// https://codeforces.com/contest/1526/problem/C2
/*
Approach: O(nlogn)
Use Min PQ
We want to maximise the number of potions
So, we keep drinking the potion until the health becomes < 0
Now, as we want maximum, so we check if there is a potion till now 
that we can remove, to include the current potion

To do this, we keep a PQ in which we have only the negative potions as they are the only
ones we should replace as we want the max potions.
Top of PQ will have the most -ve potion

If after including the current potion, health became -ve, then we have 2 choices:
1. If the top of PQ is more -ve like this potion is -9 and top is -18, then we should replace it with this one
2. If this is more -ve like this potions is -9 and top is -4, then we should not include this and keep the previous one

Because, we want max count, so removing more than 1 to include 1 with not give the right answer
*/
void potionsHardVersion()
{
    int n;
    cin >> n;

    vector<int> potions(n);
    for (int i = 0; i < n; i++)
        cin >> potions[i];

    priority_queue<int, vector<int>, greater<int>> pq;

    long long health = 0, count = 0;
    for (int i = 0; i < n; i++)
    {
        // if inlcuding this potion makes health -ve
        if (health + potions[i] < 0)
        {
            // if the top is more -ve then replace it with this, since we just replace so count remains same
            if (pq.size() > 0 && pq.top() < potions[i])
            {
                health -= pq.top();
                pq.pop();

                health += potions[i];
                pq.push(potions[i]);
            }
        }
        // else just include this one
        else
        {
            health += potions[i];
            count++;

            if (potions[i] < 0)
                pq.push(potions[i]);
        }
    }

    cout << count << endl;
}

// 781. Rabbits in Forest
/*
Approach: O(n)
If a rabbit says there are x rabbit with same color, 
then total rabbits with that color = x + 1 
(1 for the rabbit that gave the answer)

Now for each answer we maintain the count of how many rabbits gave that answer
Eg:
Given: [1,1,2,3,3,3,3,3,4,5]

So, if rabbit 4 says, there are 3 rabbit with same color
Then total rabbits with that color = 4

So, we can say that 4 rabbits giving answer 3 will have the same color
If a 5th rabbit says 3, then it will have different color, as previous 4 is already complete
So, if 5 rabbits say answer 3, there are 2 groups with 4 rabbits
So, total rabbits for those 2 groups combined will be 4 * 2 = 8
So, the answer 3 -> means group size 4
Count of that answer = 5
So, number of groups =  ceil(5 / 4) = 2
So, total number of rabbits = ceil(5 / 4) * 4 = 8
So, we count the number of times the same answer is given

Then for each answer, the number of rabbits = ceil( count of answer / (answer + 1) ) * (answer + 1)

Eg:
Given: [1,1,2,3,3,3,3,3,4,5]
Total Rabbits with that color (answer + 1): [2,2,3,4,4,4,4,4,5,6]
Here the map of {answer + 1: count} will be
2 : 2 -> ans += 2
3 : 1 -> ans += 3
4 : 5 -> ans += 4 + 4
5 : 1 -> ans+= 5
6 : 1 -> ans += 6
*/
int numRabbits(vector<int> &answers)
{
    unordered_map<double, int> mp;

    for (int ans : answers)
    {
        mp[ans + 1]++;
    }

    int res = 0;
    for (auto ele : mp)
    {
        res += ceil(ele.second / ele.first) * ele.first;
    }

    return res;
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
        C++: Does not have a way to delete a specific element, so use a set as a PQ.
    
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

// Length of the largest subarray with contiguous elements
// https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-levelup/hashmap-and-heaps/largest-subarray-with-contiguous-elements-official/ojquestion
/*
Approach: O(n^2)
For every contiguous subarray, we check if 
max of subarray - min subarray + 1 == length of subarray

This shows that all elements in that subarray are contiguous.
They might be shuffled among themselves
This means that we can sort that subarray by shuffling the elements in that subarrray.
Eg:
10 12 11

Here 
12(max) - 10(min) + 1 = 3 
length of subarray = 3

So, this is a possible answer

To handle duplicates like 10 12 12
We keep this subarray in a hashset.
If the element is already present in hashset, then break

*/
int largestSubarray(vector<int> &arr)
{
    int n = arr.size();

    int maxLen = 0;

    for (int i = 0; i < n; i++)
    {
        // make a hashset for each subarray
        unordered_set<int> subarr;
        int minNum = arr[i], maxNum = arr[i];

        for (int j = i; j < n; j++)
        {
            // element already seen, then break
            if (subarr.find(arr[j]) != subarr.end())
                break;

            // else add it to the subarray
            subarr.insert(arr[j]);
            minNum = min(minNum, arr[j]);
            maxNum = max(maxNum, arr[j]);

            // if the subarray has all contiguous elements
            if (maxNum - minNum + 1 == subarr.size())
                maxLen = max(maxLen, maxNum - minNum + 1);
        }
    }

    return maxLen;
}

// 767. Reorganize String
string reorganizeString(string s)
{
    string res = "";

    vector<int> freq(26);
    for (int i = 0; i < s.size(); i++)
    {
        freq[s[i] - 'a']++;
    }

    typedef pair<int, char> pair;

    priority_queue<pair> pq;

    for (int i = 0; i < 26; i++)
    {
        if (freq[i] > 0)
        {
            char ch = i + 'a';
            pq.push({freq[i], ch});
        }
    }

    pair pr = pq.top();
    pq.pop();

    res += pr.second;
    if (pr.first - 1 > 0)
        pq.push({pr.first - 1, pr.second});

    while (pq.size() > 0)
    {
        pair pr = pq.top();
        pq.pop();

        if (res[res.size() - 1] != pr.second)
        {
            res += pr.second;

            if (pr.first - 1 > 0)
                pq.push({pr.first - 1, pr.second});
        }
        else if (pq.size() > 0)
        {
            pair pr2 = pq.top();
            pq.pop();

            res += pr2.second;

            pq.push(pr);

            if (pr2.first - 1 > 0)
                pq.push({pr2.first - 1, pr2.second});
        }
        else
            return "";
    }

    return res;
}

// Check if frequencies can be equal
// https://practice.geeksforgeeks.org/problems/check-frequencies4211/1#
/*
Approach: O(n)
Count all the character frequencies
Find the number of characters with same frequency

Cases:
1. All characters have same frequency, no need to remove anything
2. One character has 1 more frequency than others, rest all have same frequency
    EG: aabbccc -> remove c
3. One character has only one frequency, rest have same
    Eg: aaabbbc -> remove c

*/
bool sameFreq(string s)
{
    vector<int> freq(26);

    // calculate the character frequencies
    for (int i = 0; i < s.size(); i++)
    {
        freq[s[i] - 'a']++;
    }

    // find how many different characters have that frequency
    int freq1 = -1, freq2 = -1;
    unordered_map<int, int> count;
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] > 0)
        {
            if (freq1 == -1 || freq[i] == freq1)
            {
                freq1 = freq[i];
                count[freq1]++;
            }
            else if (freq2 == -1 || freq[i] == freq2)
            {
                freq2 = freq[i];
                count[freq2]++;
            }
            else
                return false;
        }
    }

    // if only one frequency i.e. all characters have same frequence
    if (freq1 == -1 || freq2 == -1)
        return true;
    // if both frequencies have > 1 type of characters, Eg: aabbcccddd
    if (count[freq1] > 1 && count[freq2] > 1)
        return false;

    // the difference between frequence with more than 1 characters - smaller should be 1 (aaabbbcccc)
    // or the smaller character frequency should be 1 (aaaabaaa)
    if (count[freq1] >= count[freq2])
        return freq2 - freq1 == 1 || freq2 == 1;
    else
        return freq1 - freq2 == 1 || freq1 == 1;
}

// Mode of Frequencies (https://www.codechef.com/LTIME87B/problems/MODEFREQ/)
/*
Approach: O(n)
Find the frequency of each element
Then find frequency of each frequency
Find the mode of that
*/
int freqMode(vector<int> &arr)
{
    int n = arr.size();

    unordered_map<int, int> freq;

    for (int i = 0; i < n; i++)
    {
        freq[arr[i]]++;
    }

    unordered_map<int, int> freqCount;

    for (auto ele : freq)
    {
        freqCount[ele.second]++;
    }

    int maxFreq = 0, res;
    for (auto ele : freqCount)
    {
        if (ele.second > maxFreq)
        {
            maxFreq = ele.second;
            res = ele.first;
        }
        else if (ele.second == maxFreq)
            res = min(res, ele.first);
    }

    return res;
}
void modeOfFrequencies()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        vector<int> arr(n);

        for (int i = 0; i < n; i++)
            cin >> arr[i];

        cout << freqMode(arr) << endl;
    }
}

// 438. Find All Anagrams in a String
/*
Approach: O(n)
Make a frequency map of string p
Then using Sliding window of size p.size()
For every window, get the frequency map of string s
if both maps are equal, then it is an anagram
*/
vector<int> findAnagrams(string s, string p)
{
    if (p.size() > s.size())
        return {};

    int n = s.size();
    int m = p.size();

    vector<int> res;
    vector<int> freq1(26), freq2(26);

    // make frequency map of p string
    for (int i = 0; i < m; i++)
    {
        freq1[p[i] - 'a']++;
    }

    int count = 0;
    // frequency of 1st window of s
    for (int i = 0; i < m; i++)
    {
        freq2[s[i] - 'a']++;

        if (freq2[s[i] - 'a'] <= freq1[s[i] - 'a'])
            count++;
    }

    if (count == m)
        res.push_back(0);

    // other windows
    for (int i = m; i < n; i++)
    {
        // inlcude current element
        freq2[s[i] - 'a']++;
        if (freq2[s[i] - 'a'] <= freq1[s[i] - 'a'])
            count++;

        // exclude (i - m) element
        freq2[s[i - m] - 'a']--;
        if (freq2[s[i - m] - 'a'] < freq1[s[i - m] - 'a'])
            count--;

        if (count == p.size())
            res.push_back(i - m + 1);
    }

    return res;
}

// Anagram Palindrome
/*
Approach: O(n)
For a anagram that is a palindrome, 2 Cases:
1. the frequency of all n - 1 characters should be even, 1 should be odd
Eg: aacbbbcaa
OR
2. the frequency of n are even
Eg: aabbaa
*/
int isPossible(string S)
{
    vector<int> freq(26);
    for (char ch : S)
        freq[ch - 'a']++;

    int oddCount = 0;
    for (int f : freq)
    {
        if (f % 2 != 0)
            oddCount++;
        if (oddCount > 1)
            return 0;
    }

    return 1;
}

// 76. Minimum Window Substring
string minWindow(string s, string t)
{
    vector<int> sfreq(26), tfreq(26);

    for(char ch : t)
        tfreq[ch - 'a']++;

    int i = 0, j = 0, count = 0;
    while(j < s.size()){
        sfreq[s[j] - 'a']++;

        if(sfreq[s[j] - 'a'] <= tfreq[s[j] - 'a'])
            count++;

        
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
