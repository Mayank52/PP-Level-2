#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
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
For each query we have to tell if the cell is illuminated, and then if its lamp is on we turn it off
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

    // refuel if you dont have enough fuel to reach destination
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

// Count pairs in array whose sum is divisible by K
// (https://www.geeksforgeeks.org/count-pairs-in-array-whose-sum-is-divisible-by-k/)
int count4Divisibiles(int arr[], int n)
{
    int k = 4;

    // Complete the function
    unordered_map<int, int> mp;
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        count += mp[(arr[i] % k)];
        mp[arr[i] % k]++;
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
/*
Approach: O(nlogn) Priority Queue
Make a frequency map of each character in the given string
Push all the elements of map into a Max PQ as {freq, char}
Also keep a queue for blacklist characters
In our case, the element just added to the res is blacklisted so that consecutive characters are not same

Now add the top element of PQ into res
Then push the blacklisted element back into PQ
And the element that was just popped is pushed into blacklist

At the end if PQ is empty but there is still a blacklist element then ans is not possible
else return the ans

This method can be used even if K number of elements cannot be consecutive
We just keep the blacklist as a queue of size K
*/
string reorganizeString(string s)
{
    string res = "";

    // make frequency map
    vector<int> freq(26);
    for (int i = 0; i < s.size(); i++)
    {
        freq[s[i] - 'a']++;
    }

    typedef pair<int, char> pair;

    priority_queue<pair> pq;

    // put the {freq, char} into PQ
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] > 0)
        {
            char ch = i + 'a';
            pq.push({freq[i], ch});
        }
    }

    queue<pair> bl;

    while (pq.size() > 0)
    {
        pair rpair = pq.top();
        pq.pop();

        // add the top of PQ into res
        res += rpair.second;

        // put the previous blacklist element into PQ
        if (bl.size() > 0)
        {
            pq.push(bl.front());
            bl.pop();
        }

        // put the current element into blacklist
        if (rpair.first - 1 > 0)
        {
            bl.push({rpair.first - 1, rpair.second});
        }
    }

    return (bl.size() > 0) ? "" : res;
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

// 908 · Line Reflection
/*
Approach: O(n)
We can find the mirror by directly finding the mid point of the leftmost x coord and rightmost x coord
mirror = (minx + maxx) / 2

Because for a mirror parallel to y axis, the leftmost point will definetley be mapped to the right most point

Then for all remaining coords check if their reflection point in that mirror exists in the array
If not then there is no mirror.

To find mirror just do
mirror = (minx + maxx)

So mirror will have 2 * mirror value
So that we dont have to deal with double values

Then while checking for each point just use that value
Store all points in a hashmap, then for each point in array
For each coord (x, y), we have
(x1 + x2)/2 = mirror

So, x2 = 2*mirror - x1
And we already found mirror*2 value
Just check if mirror - x1 is in map, and the y coord is also same for that point.
*/
bool isReflected(vector<vector<int>> &points)
{
    if (points.size() == 0)
        return true;

    int n = points.size();

    // find the min and max x coord
    int minx = points[0][0];
    int maxx = points[0][0];

    for (vector<int> &p : points)
    {
        if (p[0] < minx)
            minx = p[0];
        else if (p[0] > maxx)
            maxx = p[0];
    }

    // candidate for mirror
    int mirror = minx + maxx;

    // verify
    unordered_map<int, int> coords; // {x : y}
    for (vector<int> &p : points)
    {
        coords[p[0]] = p[1];
    }

    for (vector<int> &p : points)
    {
        // if the mirror of x does not exist
        // or the y coord of the reflection is different
        if (coords.find(mirror - p[0]) == coords.end() || coords[mirror - p[0]] != p[1])
            return false;
    }

    return true;
}

// 380. Insert Delete GetRandom O(1)
/*
Approach: O(1) for each operation
Use a Hashmap, vector
In hashmap we store {element : index}

In array we just store the elements in the order they are inserted

For insert: O(1)
Add element : index to map, and push_back to vector

For random: O(1)
use rand() % arr.size() to get random index and return that element from array

For Remove: O(1)
We have to remove from both array and map.
Get the index of element to be removed from map = remIdx
In array swap element at remIdx with last element
Update the index of the new element at remIdx in map
Then remove the last element
And remove the given element from map

This exact order is important because their might be only one element in the array.
*/
class RandomizedSet
{
public:
    /** Initialize your data structure here. */
    unordered_map<int, int> mp;
    vector<int> arr;

    RandomizedSet()
    {
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        if (mp.find(val) != mp.end())
            return false;

        arr.push_back(val);
        mp[val] = arr.size() - 1;

        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
        if (mp.find(val) == mp.end())
            return false;

        // get index of element to be removed
        int remIdx = mp[val];

        // swap with last element, and update its index in map
        arr[remIdx] = arr[arr.size() - 1];
        mp[arr[remIdx]] = remIdx;

        // remove the element from array, and map
        arr.pop_back();
        mp.erase(val);

        return true;
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        int idx = (rand() % arr.size());

        return arr[idx];
    }
};

// 381. Insert Delete GetRandom O(1) - Duplicates allowed
/*
Approach: O(1) for each operation
Use a Hashmap, vector
In hashmap we store {element : set of indexes}

In array we just store the elements in the order they are inserted

For insert: O(1)
Add element : insert index to set of the element in map, and push_back to vector

For random: O(1)
use rand() % arr.size() to get random index and return that element from array

For Remove: O(1)
We have to remove from both array and map.
Get the index of element to be removed from map = remIdx
In array swap element at remIdx with last element
Remove the remIdx from set of removed element, 
and remove the last index from set of the element which was swapped to remIdx
Then insert the remIdx to the set of new element at remIdx
Then remove the last element from array
And remove the given element from map if its set is now empty

This exact order is important because the value of element at remIdx and last index may be same.
*/
class RandomizedCollection
{
public:
    /** Initialize your data structure here. */
    unordered_map<int, unordered_set<int>> mp;
    vector<int> arr;

    RandomizedCollection()
    {
    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val)
    {
        // if(mp.find(val) != mp.end())
        //     return false;

        arr.push_back(val);
        mp[val].insert(arr.size() - 1);

        return mp[val].size() > 1 ? false : true;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val)
    {
        if (mp.find(val) == mp.end())
            return false;

        int remIdx = *(mp[val].begin());

        if (remIdx == arr.size() - 1)
        {
            arr.pop_back();
            mp[val].erase(remIdx);
        }
        else
        {
            arr[remIdx] = arr[arr.size() - 1];
            mp[arr[remIdx]].erase(arr.size() - 1);

            arr.pop_back();
            mp[val].erase(remIdx);

            mp[arr[remIdx]].insert(remIdx);
        }

        if (mp[val].size() == 0)
            mp.erase(val);

        return true;
    }

    /** Get a random element from the collection. */
    int getRandom()
    {
        int idx = (rand() % arr.size());

        return arr[idx];
    }
};

// 710. Random Pick with Blacklist
/*
Approach: Hashmap
Preprocessing: O(n)
Pick() : O(1)

We keep a hashmap of all blacklisted values : their replacement
So, first we add all blacklist values to map
Then we map those values to a safe value

We keep a pointer at the end
Then for each blacklist value, we reduce the pointer until we reach a safe value.
Then map this blacklist value to that value and reduce the pointer by 1 to next value

While picking we only pick from the first n - blacklist.size() values, as every value after that is now blacklisted
And the safe values after n - blacklist.size() are mapped to the blacklist values before this
So, in a sense we swapped all safe values after this with blacklisted values before this

Then while picking, if random gives a blacklisted value, we return its replacement

Eg:
given n = 9
So values : 0 1 2 3 4 5 6 7 8
blacklist: 3 5 7 8 2
map:
3 : 6
5 : -1
7 : -1
8 : -1
2 : 4
*/
class Solution
{
public:
    unordered_map<int, int> mp; //{blackListed Element : Replacement}
    int size;

    Solution(int n, vector<int> &blacklist)
    {
        size = n - blacklist.size();

        // add all blacklist values to a map
        for (int val : blacklist)
            mp[val] = -1;

        int j = n - 1;
        for (int val : blacklist)
        {
            // if value in safe range
            if (val < size)
            {
                // find the safe value from end
                while (mp.find(j) != mp.end())
                    j--;

                // map this value to that safe value;
                mp[val] = j;
                j--;
            }
        }
    }

    int pick()
    {
        int idx = rand() % size;

        // if this value is blacklisted, then return the mapped safe value, else return this value
        return mp.find(idx) != mp.end() ? mp[idx] : idx;
    }
};

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
/*
Approach: O(n) Sliding Window
Make a frequency map of string t

We use 2 pointers i, j, and a matchCount for the number of elements in string s that match with string t
We start both at 0
Keep moving j forward until, we have the same matchCount
Then we move i to remove the not required characters.
So, we move i forward until the matchCount remains the same

With each iteration we update the minimum size of substring
*/
string minWindow(string s, string t)
{
    int n = s.size();
    int m = t.size();

    if (m > n)
        return "";

    unordered_map<char, int> mp1;
    unordered_map<char, int> mp2;

    for (char c : t)
        mp1[c]++;

    int i = -1, j = -1;
    int matchCount = 0;
    int si = 0, ei = 0, minLen = s.size();

    while (true)
    {
        bool f1 = false;
        bool f2 = false;

        //acquire
        while (j < n - 1 && matchCount < m)
        {
            f1 = true;
            j++;
            mp2[s[j]]++;
            if (mp2[s[j]] <= mp1[s[j]])
                matchCount++;
        }

        //remove
        while (i < j && matchCount == m)
        {
            f2 = true;

            i++;
            mp2[s[i]]--;

            if (mp2[s[i]] < mp1[s[i]])
                matchCount--;
        }

        // update the minimum substring
        if (j - i < minLen)
        {
            si = i;
            ei = j;
            minLen = j - i;
        }

        if (!f1 && !f2)
            break;
    }

    if (i == -1)
        return "";
    return s.substr(si, ei - si + 1);
}

// 49. Group Anagrams
/*
Approach 1: O(m * n)
Make a map of, {frequency map of string : list of strings with same map}
Then just add them all into the res as same groups

Approach 2: O(mlogm * n)
For the key of map we can use the sorted string as well.

Both the frequency map, sorted string will be same for all anagrams

We can also just store the index of that group in map in value
instead of array of strings in that group
Then directly push into that index in the result.
*/
vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    map<vector<int>, vector<string>> map;

    // make map {frequency map : array of strings}
    for (string &str : strs)
    {
        vector<int> freq(26);
        for (char ch : str)
            freq[ch - 'a']++;

        map[freq].push_back(str);
    }

    // add to result
    vector<vector<string>> res;
    for (auto ele : map)
    {
        res.push_back(ele.second);
    }

    return res;
}
vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    unordered_map<string, int> map;
    vector<vector<string>> res;

    // make a map of {sorted string: index in result array}
    for (string &str : strs)
    {
        string temp = str;
        sort(temp.begin(), temp.end());

        // if first string of this group, add the index to map,and add new list to result
        if (map.find(temp) == map.end())
        {
            map[temp] = res.size();
            res.push_back({str});
        }
        // else add to result at the index given by map
        else
        {
            res[map[temp]].push_back(str);
        }
    }

    return res;
}

// 3. Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(string s)
{
    unordered_map<char, int> map; // {char : index}
    int res = 0, start = 0;

    for (int i = 0; i < s.size(); i++)
    {
        if (map.find(s[i]) != map.end())
            start = max(start, map[s[i]] + 1);

        map[s[i]] = i;
        res = max(res, i - start + 1);
    }

    return res;
}

// 813 · Find Anagram Mappings
vector<int> anagramMappings(vector<int> &A, vector<int> &B)
{
    // Write your code here
    unordered_map<int, int> map;

    for (int i = 0; i < B.size(); i++)
    {
        map[B[i]] = i;
    }

    vector<int> res(A.size());
    for (int i = 0; i < A.size(); i++)
    {
        res[i] = map[A[i]];
    }

    return res;
}

// Check if two strings are k-anagrams or not
/*
Approach: O(n)
Make frequency map for strings
Now iterate over frequency map, where ever, the freq1[i] > freq2[i]
add the diff to totalDiff
If totalDiff <= k, then return true else false
*/
bool areKAnagrams(string str1, string str2, int k)
{
    if (str1.size() != str2.size())
        return false;

    int freq1[26] = {0}, freq2[26] = {0};

    for (int i = 0; i < str1.size(); i++)
    {
        freq1[str1[i] - 'a']++;
        freq2[str2[i] - 'a']++;
    }

    int diff = 0;
    for (int i = 0; i < 26; i++)
    {
        if (freq1[i] > freq2[i])
            diff += (freq1[i] - freq2[i]);
    }

    return diff <= k;
}

// Smallest subarray with all occurrences of a most frequent element
/*
Approach: O(n)
Make a map of {val : freq, start index, end index}
So, we find the frequency, first index, last index of each element

We also find the max frequecy.
In case multiple elemets have same frequency, we take the element with smaller subarray
i.e. (end - start + 1) should be smaller
*/
vector<int> smallestSubsegment(int a[], int n)
{
    // Complete the function
    unordered_map<int, vector<int>> map; // {val : freq, start index, end index}
    int maxFreq = 0, val;                // max frequency, element with max frequency

    for (int i = 0; i < n; i++)
    {
        // first occurence of this element
        if (map.find(a[i]) == map.end())
        {
            map[a[i]] = {1, i, i};
        }
        // else update the freq, end index of this element
        else
        {
            map[a[i]][0]++;
            map[a[i]][2] = i;
        }

        // if current element has freq > max frequency
        if (map[a[i]][0] > maxFreq)
        {
            maxFreq = map[a[i]][0];
            val = a[i];
        }
        // if current element has freq = max frequency, check the length of subarray
        else if (map[a[i]][0] == maxFreq)
        {
            int currLen = map[a[i]][2] - map[a[i]][1] + 1;
            int prevLen = map[val][2] - map[val][1] + 1;
            if (currLen < prevLen)
            {
                val = a[i];
            }
        }
    }

    // add the elements in the subarray [start, end] of element with max frequency
    vector<int> res;
    for (int i = map[val][1]; i <= map[val][2]; i++)
        res.push_back(a[i]);

    return res;
}

// 697. Degree of an Array
/*
Approach: O(n)
Same as above
Instead of the subarray, we just need the length
So, just store freq, start in map
Whenever the current frequency is > or = update the
end index will be the current index itself
*/
int findShortestSubArray(vector<int> &nums)
{
    int n = nums.size();

    unordered_map<int, vector<int>> map; // {val : freq, start index}
    int maxFreq = 0, res;

    for (int i = 0; i < n; i++)
    {
        // update the value in map
        if (map.find(nums[i]) == map.end())
            map[nums[i]] = {1, i};
        else
            map[nums[i]][0]++;

        // update the result
        if (map[nums[i]][0] > maxFreq)
        {
            maxFreq = map[nums[i]][0];
            res = i - map[nums[i]][1] + 1;
        }
        else if (map[nums[i]][0] == maxFreq)
            res = min(res, i - map[nums[i]][1] + 1);
    }

    return res;
}

// 166. Fraction to Recurring Decimal
string fractionToDecimal(int numerator, int denominator)
{
    // if there is no decimal part
    if ((long)numerator % denominator == 0)
        return to_string((long)numerator / denominator);

    string res = "";

    // find the sign -> - or +
    if (numerator < 0 && denominator > 0 || numerator > 0 && denominator < 0)
        res += '-';

    // convert numerator and denominator to +ve
    long num = abs(numerator);
    long den = abs(denominator);

    // add the before decimal part to result
    res += to_string(num / den);

    // now find the decimal part
    unordered_map<int, int> mp; // { rem, index in string}
    string decimal = "";

    num = num % den;
    while (num != 0 && mp.find(num) == mp.end())
    {
        // put the current remainder in map with its index
        mp[num] = decimal.size();

        num *= 10;

        decimal += to_string(num / den);
        num = num % den;
    }

    if (num == 0)
        return res + "." + decimal;
    else
    {
        int recIdx = mp[num];
        decimal = decimal.substr(0, recIdx) + '(' + decimal.substr(recIdx) + ')';
        return res + "." + decimal;
    }
}

// 850 · Employee Free Time
/*
Approach 1: o(nlogn)
Add the given times into an array okf intervals
Then sort the intervals in increasing order of start times

Now iterate over the sorted intervals, keep a max end time till now
For each interval, if its start time, is less than the current max end time,
then every employee is free in that time. As every employee who started before this time 
has ended their work. And no other employee has started anything till now
So, add this interval [current max end time, current start time] into the result.

Approach 2: O(nlogk)
Use a min PQ instead of sorting all the intervals
Then it becomes similar to merging k sorted lists
Push the first interval of each employee into PQ
Every time remove the top element and add next interval of that employee into PQ
The size of PQ remains equal to number of employees = k = schedule.size()
Keep a max end time till now
If the max end time till now < current start time, then add {max end time, current start} into result
*/
// Approach 1
vector<Interval> employeeFreeTime(vector<vector<int>> &schedule)
{
    // Write your code here
    vector<vector<int>> intervals;
    for (vector<int> &v : schedule)
    {
        for (int i = 0; i < v.size(); i += 2)
        {
            intervals.push_back({v[i], v[i + 1]});
        }
    }

    sort(intervals.begin(), intervals.end());

    vector<Interval> res;

    int endTime = intervals[0][0];
    for (vector<int> interval : intervals)
    {
        int start = interval[0];
        int end = interval[1];

        if (endTime < start)
        {
            res.push_back(Interval(endTime, start));
        }

        endTime = max(endTime, end);
    }

    return res;
}
// Approach 2:
vector<Interval> employeeFreeTime(vector<vector<int>> &schedule)
{
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq; // {start, end, i, j}

    for (int i = 0; i < schedule.size(); i++)
    {
        pq.push({schedule[i][0], schedule[i][1], i, 0});
    }

    vector<Interval> res;
    int endTime = pq.top()[0];

    while (pq.size() > 0)
    {
        vector<int> rem = pq.top();
        pq.pop();

        int start = rem[0];
        int end = rem[1];
        int i = rem[2];
        int j = rem[3];

        if (endTime < start)
            res.push_back(Interval(endTime, start));

        if (j < schedule[i].size() - 2)
        {
            pq.push({schedule[i][j + 2], schedule[i][j + 3], i, j + 2});
        }

        endTime = max(endTime, end);
    }

    return res;
}

// 378. Kth Smallest Element in a Sorted Matrix
/*
Approach: O(nlogn), Priority Queue
Similar to merging N sorted Linked Lists
Use a min PQ
Add the first element of each row into PQ as {val, row, col}
Then while k > 1
Get the top of PQ, and add the next element of that row into PQ

We can also do this column wise
*/
int kthSmallest(vector<vector<int>> &matrix, int k)
{
    int n = matrix.size();

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    for (int i = 0; i < n; i++)
    {
        pq.push({matrix[i][0], i, 0});
    }

    while (k-- > 1)
    {
        vector<int> rem = pq.top();
        pq.pop();

        int r = rem[1];
        int c = rem[2] + 1;

        if (c < n)
        {
            pq.push({matrix[r][c], r, c});
        }
    }

    return pq.top()[0];
}

// 786. K-th Smallest Prime Fraction
/*
Approach: O(nlogn), Priority Queue
Passes, but Gives TLE
*/
vector<int> kthSmallestPrimeFraction(vector<int> &arr, int k)
{
    int n = arr.size();

    priority_queue<vector<double>, vector<vector<double>>, greater<vector<double>>> pq;

    for (int i = 0; i < n - 1; i++)
    {
        pq.push({arr[i] * 1.0 / arr[n - 1], i * 1.0, (n - 1) * 1.0});
    }

    while (k-- > 1)
    {
        vector<double> rem = pq.top();
        pq.pop();

        double i = rem[1];
        double j = rem[2];

        if (i < j)
            pq.push({arr[i] * 1.0 / arr[j - 1], i, j - 1});
    }

    return {arr[pq.top()[1]], arr[pq.top()[2]]};
}

// 205. Isomorphic Strings
bool isIsomorphic(string s, string t)
{
    unordered_map<char, char> mp;
    unordered_set<char> vis;

    for (int i = 0; i < s.size(); i++)
    {
        // if this element is already mapped
        if (mp.find(s[i]) != mp.end())
        {
            if (mp[s[i]] != t[i])
                return false;
        }
        // if t[i] was already mapped to other element
        else if (vis.find(t[i]) != vis.end())
            return false;
        // else map s[i] to t[i]
        else
        {
            mp[s[i]] = t[i];
            vis.insert(t[i]);
        }
    }

    return true;
}

// 1872 · Minimum Cost to Connect Sticks
/*
Approach: O(nlogn)
To get the minimum x + y every time, we use the minimum x and y
So put all values in a min PQ
Then add the top 2 values and add the sum back into PQ
*/
int MinimumCost(vector<int> &sticks)
{
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int val : sticks)
        pq.push(val);

    int res = 0;

    while (pq.size() > 1)
    {
        int min1 = pq.top();
        pq.pop();

        int min2 = pq.top();
        pq.pop();

        res += min1 + min2;

        pq.push(min1 + min2);
    }

    return res;
}

// 1167. Minimum Time to Build Blocks (Not Available to submit)
/*
Approach: O(nlogn)
To get the minimum time, we need to add the minimum split time to the maximum value
As every time we split, the split time will increase, so we want that the value that is already greater, should be
resolved first so, less split time is added to it.
So, we solve it in a bottom up manner i.e. solve the minimum value first.

So, similar to previous,  put all values in a min PQ
Then take the top 2 values. we will add split to the max of two values
Since its a min PQ, the second value will always be max of the two

Then we add the total time for that i.e. maxValue + split back into PQ
The last element remaining in PQ is the result

Eg: blocks = [3 7 2 10 3], split = 5
So, PQ: 2 3 3 7 10
first we take the minimum 2 :  2 3
Add max(2, 3) + 5 = 8 into PQ

PQ: 3 7 8 10
Add max(3, 7) + 5 = 12 into PQ

PQ: 8 10 12
Add max(8, 10) + 5 = 15 into PQ

PQ: 12 15
add 15 + 5 = 20 into PQ

Now result is 20

Its the same approach as in Huffman coding

Every time we split a worker the cost is 5, so lower you are in the tree formed, more the cost will be added
So, we want the lowest values to be at the bottom.
*/
int minBuildTime(vector<int> &blocks, int split)
{
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int val : blocks)
        pq.push(val);

    while (pq.size() > 1)
    {
        int rem1 = pq.top();
        pq.pop();

        int rem2 = pq.top();
        pq.pop();

        pq.push(split + rem2);
    }

    return pq.top();
}

// 480. Sliding Window Median
/*
Approach: O(nlogk) (k = size of window, n = size of array)
Similar to 295. Find Median from Data Stream
We keep a min PQ(right), and a max PQ(left)
max PQ contains the left half of the array, and min PQ contains the right half

For every new element, add it to the right half, then add the top of right half to left half.
This way we can make sure that every element in max PQ is smaller than min PQ
And remove the (i - k)th element, so now we have only current window elements in the PQs
In case of odd number of elements we keep one extra element in the max PQ i.e left half
After adding element, check the size of both PQs and move elements to make size equal
2 Cases:
    1. If max PQ's size > min PQ's size + 1
    Then move the top of max PQ to min PQ
    2. If min PQ's size > max PQ
    Then move top of min PQ to max PQ

So, in case of n being 
    odd: top of max PQ is answer, as it has an extra element
    even: (max PQ top + min PQ top) / 2 is answer
*/
vector<double> medianSlidingWindow(vector<int> &nums, int k)
{
    multiset<double> left;  // max PQ
    multiset<double> right; // min PQ

    vector<double> res;

    // first window
    for (int i = 0; i < k; i++)
    {
        // add element to the current window
        right.insert(nums[i]);
        left.insert(*right.begin());
        right.erase(right.begin());

        // make size of left and right equal
        if (left.size() > right.size() + 1)
        {
            right.insert(*left.rbegin());
            left.erase(left.find(*left.rbegin()));
        }
        else if (right.size() > left.size())
        {
            left.insert(*right.begin());
            right.erase(right.begin());
        }
    }

    // add the median of first window to result
    if (k % 2 == 0)
        res.push_back((*right.begin() + *left.rbegin()) / 2);
    else
        res.push_back(*left.rbegin());

    // other windows
    for (int i = k; i < nums.size(); i++)
    {
        // add new element
        right.insert(nums[i]);
        left.insert(*right.begin());
        right.erase(right.begin());

        // remove (i - k)th element
        if (left.find(nums[i - k]) != left.end())
            left.erase(left.find(nums[i - k]));
        else
            right.erase(right.find(nums[i - k]));

        // make size of left and right equal
        if (left.size() > right.size() + 1)
        {
            right.insert(*left.rbegin());
            left.erase(left.find(*left.rbegin()));
        }
        if (right.size() > left.size())
        {
            left.insert(*right.begin());
            right.erase(right.begin());
        }

        // add the median of current window to result
        if (k % 2 == 0)
            res.push_back((*right.begin() + *left.rbegin()) / 2);
        else
            res.push_back(*left.rbegin());
    }

    return res;
}

// 992. Subarrays with K Different Integers
/*
Approach: Time: O(n), Space: O(k)
We cannot directly find exactly k distinct in O(n).
But we can find at most k distinct using 2 pointers. 
And count of exactly k distinct = count of at most k distinct - count of at most k - 1 distinct

Eg: 
[1,2,1,2,3], k = 2

i = 0, j = 0, count = 0

First iteration: i = 0, j = 0
j = 0 -> freq: {1: 1}, count = 1
j = 1 -> freq: {1: 1, 2: 1}, count = 1 + 2
j = 2 -> freq: {1: 2, 2: 1}, count = 1 + 2 + 3
j = 3 -> freq: {1: 2, 2: 2}, count = 1 + 2 + 3 + 4
j = 4 -> freq: {1: 2, 2: 2, 3: 1}, Now freq.size() == 3 > 2, so , decrease the current element's frequency by 1
    As, we will count it in the next iteration when it is actually needed, otherwise it is counted twice

Then increase i, until freq.size() is 2 again. And so on...

Do this once for k = 2, then k = 1, and then return the difference to get count of exactly k.
*/
int atMostKDistinct(vector<int> &nums, int k)
{
    int i = 0, count = 0;
    unordered_map<int, int> freq;

    for (int j = 0; j < nums.size(); j++)
    {
        // include current element
        freq[nums[j]]++;

        // after including, if distinct count > k, then start exlcuding from left
        while (freq.size() > k)
        {
            freq[nums[i]]--;

            if (freq[nums[i]] == 0)
                freq.erase(nums[i]);

            i++;
        }

        // now include the count of subarrays with start = i, end = j
        count += j - i + 1;
    }

    return count;
}
int subarraysWithKDistinct(vector<int> &nums, int k)
{
    return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
}

// 1248. Count Number of Nice Subarrays
/*
Approach: Time: O(n), Space: O(1)
Same as previous question (992. Subarrays with K Different Integers)
We dont a need a map since we only need a odd count
*/
int atMostKOdd(vector<int> &nums, int k)
{
    int i = 0, count = 0;
    int oddCount = 0;

    for (int j = 0; j < nums.size(); j++)
    {
        // include current element
        if (nums[j] % 2 != 0)
            oddCount++;

        // after including, if odd count > k, then start exlcuding from left
        while (oddCount > k)
        {
            if (nums[i] % 2 != 0)
                oddCount--;

            i++;
        }

        // now include the count of subarrays with start = i, end = j
        count += j - i + 1;
    }

    return count;
}
int numberOfSubarrays(vector<int> &nums, int k)
{
    return atMostKOdd(nums, k) - atMostKOdd(nums, k - 1);
}

// 1358. Number of Substrings Containing All Three Characters
/*
Approach: O(n)
Same as k distinct

*/
int atMostKDistinct(string &s, int k)
{
    int i = 0, count = 0;
    unordered_map<char, int> freq;

    for (int j = 0; j < s.size(); j++)
    {
        // include current element
        freq[s[j]]++;

        // after including, if distinct count > k, then start exlcuding from left
        while (freq.size() > k)
        {
            freq[s[i]]--;

            if (freq[s[i]] == 0)
                freq.erase(s[i]);

            i++;
        }

        // now include the count of subarrays with start = i, end = j
        count += j - i + 1;
    }

    return count;
}
int numberOfSubstrings(string s)
{
    return atMostKDistinct(s, 3) - atMostKDistinct(s, 2);
}

// 904. Fruit Into Baskets
/*
Approach: O(n)
We need to find the max length subarray with distinct at most 2
Same approach as at most k distinct 
Just instead of count we keep the max length
*/
int totalFruit(vector<int> &fruits)
{
    int maxLen = 0;
    unordered_map<int, int> freq;

    int i = 0;
    for (int j = 0; j < fruits.size(); j++)
    {
        // add current element's frequency
        freq[fruits[j]]++;

        // while distinct element count > 2
        while (freq.size() > 2)
        {
            freq[fruits[i]]--;

            if (freq[fruits[i]] == 0)
                freq.erase(fruits[i]);

            i++;
        }

        // update max length
        maxLen = max(maxLen, j - i + 1);
    }

    return maxLen;
}

// 1234. Replace the Substring for Balanced String
/*
Approach: O(n)
We find the min length substring, so that in the remaining string
no character has frequency > n / 4
This means that by changing the characters in the chosen substring 
we can make the frequency of each character n / 4

eg: "WWEQERQWQWWRWWERQWEQ", answer = 4
Here total length = 20
So, each character should have freq = 20 / 4 = 5
Frequency of each character = W: 8, Q: 5, R: 3, E: 4
So, if we choose the substring WQWW (index 7 to 10)
Because this is the shortest subtring after removing which every character will have frequency <= n / 4
So, by changing the characters in this substring, we can correct the frequency for the remaining characters
Like, here we need 2 R, 1 E, and we 3 extra W. So, we can make it RQRE. Now each character will have n / 4 frequecy.
*/
int balancedString(string s)
{
    int n = s.size();

    unordered_map<char, int> freq;
    int minLen = n;

    for (char ch : s)
    {
        freq[ch]++;
    }

    if (freq['W'] == n / 4 && freq['R'] == n / 4 && freq['Q'] == n / 4 && freq['E'] == n / 4)
        return 0;

    int i = 0;
    for (int j = 0; j < n; j++)
    {
        freq[s[j]]--;

        while (i <= j && freq['W'] <= n / 4 && freq['R'] <= n / 4 && freq['Q'] <= n / 4 && freq['E'] <= n / 4)
        {
            minLen = min(minLen, j - i + 1);
            freq[s[i]]++;
            i++;
        }
    }

    return minLen;
}

// 209. Minimum Size Subarray Sum
/*
Approach: 2 Pointers, O(n)
Keep i = 0, j = 0

If the currSum < target, move j forward one step
then until the currSum >= target, keep moving i forward
*/
int minSubArrayLen(int target, vector<int> &nums)
{
    int n = nums.size();

    int i = 0, minLen = n + 1, currSum = 0;

    for (int j = 0; j < n; j++)
    {
        currSum += nums[j];

        while (currSum >= target)
        {
            minLen = min(minLen, j - i + 1);

            currSum -= nums[i];
            i++;
        }
    }

    return minLen <= n ? minLen : 0;
}

// 862. Shortest Subarray with Sum at Least K
/*
Wrong Approach: 2 Pointers
We cannot use 2 pointer approach here as -ve numbers are also present
Eg: [84,-37,32,40,95], K = 167
Here i = 0, j = 4, sum = 214
So, you increase i to 1 and sum = 130
Now i wont increase, but we should increase i as increasing it will increase the sum
because it will be 130 - (-37)
So, because of negative numbers 2 pointer approach cannot be used.

Correct Approach: O(n), Monotonic queue
In the normal 2 pointer approach, we increase the end pointer(j) until sum < k
Then when sum becomes >= k, we increase the start pointer to find the minimum range
We can do this in case of positive numbers as we know on increasing the start the sum
will decrease. But with -ve numbers sum may increase as well.

So, we maintain a monotonic queue of start points
In this queue we have a order of start points on in increasing order of sum b/w [start, current end]
So, now for the current end, while the sum b/w [current end, start at front of queue] >= k
We move to the next start which is the next element in queue.
So, just pop_front until sum is >= k, this way we shorten the current range
Since we are maintaining a queue in which the sum of next start point is definitely smaller than previous one
So, now the 2 pointer approach logic works.
Now to maintain the monotonic queue before pushing current index to its end
pop_back until the sum in range [start, current back] > current sum

Also, we maintain a prefix sum so that we can find the sum in range [start, end] in O(1) time
No need to take seperate prefixSum array. Just modify the given array.

*/
int shortestSubarray(vector<int> &nums, int k)
{
    int n = nums.size();

    int res = n + 1;
    deque<int> que;
    que.push_back(0);

    for (int j = 0; j < n; j++)
    {
        // find prefix sum for current index
        if (j > 0)
            nums[j] += nums[j - 1];

        // if the current sum >= k, then update the result
        if (nums[j] >= k)
            res = min(res, j + 1);

        // increase the start of range until sum b/w [start, end] >= k
        while (que.size() > 0 && nums[j] - nums[que.front()] >= k)
        {
            res = min(res, j - que.front());
            que.pop_front();
        }

        // remove all elements from end of queue that are > current element to maintain increasing queue
        while (que.size() > 0 && nums[que.back()] >= nums[j])
            que.pop_back();

        // push current element into queue
        que.push_back(j);
    }

    return res == n + 1 ? -1 : res;
}

// 567. Permutation in String
/*
Approach: 2 pointers, O(n)
Use 2 pointers, to find a substring in s2 whose frequency map is equal to s1 string's frequency map
*/
bool checkInclusion(string s1, string s2)
{
    vector<int> freq1(26), freq2(26);

    for (char ch : s1)
        freq1[ch - 'a']++;

    int i = 0;

    for (int j = 0; j < s2.size(); j++)
    {
        // if current character not present in s1, then reset values
        if (freq1[s2[j] - 'a'] == 0)
        {
            freq2.assign(26, 0);
            i = j + 1;
            continue;
        }

        // include current character
        freq2[s2[j] - 'a']++;

        // exclude until extra character is removed
        while (freq2[s2[j] - 'a'] > freq1[s2[j] - 'a'])
        {
            freq2[s2[i] - 'a']--;
            i++;
        }

        // if all characters
        if (j - i + 1 == s1.size())
            return true;
    }

    return false;
}

// 632. Smallest Range Covering Elements from K Lists
/*
Approach: O(nlogk)
Similar to Merge K sorted Lists
Push the first element of each list into a Min PQ
Also, find the max element of these first elements

Now, that max element is the max of current range, and top of PQ is min of current range
So, at every step, pop the top element, that is min of current range, and max we 
already have, using this update the overall shortest range
Then push the next element of that list into the PQ.
Also, while pushing the next element update the current max.
*/
vector<int> smallestRange(vector<vector<int>> &nums)
{
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    int start = INT_MAX, end = INT_MIN, currMax = INT_MIN;

    // push first element of each list into PQ
    for (int i = 0; i < nums.size(); i++)
    {
        pq.push({nums[i][0], i, 0});
        currMax = max(currMax, nums[i][0]);
    }

    start = pq.top()[0];
    end = currMax;

    while (pq.size() > 0)
    {
        int num = pq.top()[0];
        int i = pq.top()[1];
        int j = pq.top()[2];

        pq.pop();

        // update the current range
        if (currMax - num < end - start)
        {
            start = num;
            end = currMax;
        }

        // push next element into PQ
        if (j + 1 < nums[i].size())
        {
            // update the current max with new element
            currMax = max(currMax, nums[i][j + 1]);
            pq.push({nums[i][j + 1], i, j + 1});
        }
        else
            break;
    }

    return {start, end};
}

// 706. Design HashMap
class Node
{
public:
    int key;
    int val;
    Node *next;

    Node(int k, int v)
    {
        this->key = k;
        this->val = v;
        this->next = nullptr;
    }
};
class MyHashMap
{
private:
    vector<Node *> buckets;
    int size;
    double loadFactor;

    int hashfunction(int key)
    {
        return key % buckets.size();
    }
    Node *findNode(int idx, int key)
    {
        // if node with key is present, return that node, else return the last node of list,
        // so that we can attach the new node to its end
        Node *curr = buckets[idx], *prev = nullptr;

        while (curr != nullptr && curr->key != key)
        {
            prev = curr;
            curr = curr->next;
        }

        return curr == nullptr ? prev : curr;
    }
    void rehash()
    {
        // copy the current buckets into a temporary array
        vector<Node *> arr = buckets;

        // double the size of buckets
        buckets.assign(buckets.size() * 2, new Node(-1, -1));

        // add all elements in buckets into the new buckets
        for (Node *node : arr)
        {
            Node *curr = node->next; // skip the dummy head
            while (curr != nullptr)
            {
                put(curr->key, curr->val);
                curr = curr->next;
            }
        }
    }

public:
    /** Initialize your data structure here. */
    MyHashMap()
    {
        this->buckets.resize(4, new Node(-1, -1)); // dummy heads
        this->size = 0;
        this->loadFactor = 2.0;
    }

    /** value will always be non-negative. */
    void put(int key, int value)
    {
        int idx = hashfunction(key);
        Node *node = findNode(idx, key);

        // not already present
        if (node->key != key)
        {
            Node *newNode = new Node(key, value);
            node->next = newNode;
            size++;
        }
        // already present
        else
            node->val = value;

        // rehash
        if (size * 1.0 / buckets.size() > loadFactor)
            rehash();
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key)
    {
        int idx = hashfunction(key);
        Node *node = findNode(idx, key);

        return node->key == key ? node->val : -1;
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key)
    {
        int idx = hashfunction(key);

        Node *curr = buckets[idx], *prev = nullptr;

        while (curr != nullptr && curr->key != key)
        {
            prev = curr;
            curr = curr->next;
        }

        // if node is present, then remove it
        if (curr != nullptr)
        {
            prev->next = curr->next;
            size--;
        }
    }
};

// 705. Design HashSet
class Node
{
public:
    int key;
    Node *next;

    Node(int k)
    {
        this->key = k;
        this->next = nullptr;
    }
};
class MyHashSet
{
private:
    vector<Node *> buckets;
    int size;
    double loadFactor;

    int hashfunction(int key)
    {
        return key % buckets.size();
    }
    Node *findNode(int idx, int key)
    {
        // if node with key is present, return that node, else return the last node of list,
        // so that we can attach the new node to its end
        Node *curr = buckets[idx], *prev = nullptr;

        while (curr != nullptr && curr->key != key)
        {
            prev = curr;
            curr = curr->next;
        }

        return curr == nullptr ? prev : curr;
    }
    void rehash()
    {
        // copy the current buckets into a temporary array
        vector<Node *> arr = buckets;

        // double the size of buckets
        buckets.assign(buckets.size() * 2, new Node(-1));

        // add all elements in buckets into the new buckets
        for (Node *node : arr)
        {
            Node *curr = node->next; // skip the dummy head
            while (curr != nullptr)
            {
                add(curr->key);
                curr = curr->next;
            }
        }
    }

public:
    /** Initialize your data structure here. */
    MyHashSet()
    {
        this->buckets.resize(4, new Node(-1)); // dummy heads
        this->size = 0;
        this->loadFactor = 2.0;
    }

    void add(int key)
    {
        int idx = hashfunction(key);
        Node *node = findNode(idx, key);

        // not already present
        if (node->key != key)
        {
            Node *newNode = new Node(key);
            node->next = newNode;
            size++;
        }

        // rehash
        if (size * 1.0 / buckets.size() > loadFactor)
            rehash();
    }

    void remove(int key)
    {
        int idx = hashfunction(key);

        Node *curr = buckets[idx], *prev = nullptr;

        while (curr != nullptr && curr->key != key)
        {
            prev = curr;
            curr = curr->next;
        }

        // if node is present, then remove it
        if (curr != nullptr)
        {
            prev->next = curr->next;
            size--;
        }
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key)
    {
        int idx = hashfunction(key);
        Node *node = findNode(idx, key);

        return node->key == key;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}