#include <iostream>
#include <limits.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
#include <list>

using namespace std;
// 925. Long Pressed Name
/*
Approach: 2 Pointer
Time Complexity: O(n+m), Space: O(1)

To be Long Pressed:
- The typed should have the same characters in the same order
- only the freq may be more than the name string but in the correct order

So, you can only type the character more than required times in the correct order

Eg: 
name: alex, typed: aallexa
here ans is false because of 'a' at the end
alex, aallexxx is true
alex, alex is true

so we use 2 pointers to solve it
*/
bool isLongPressedName(string name, string typed)
{
    if (name[0] != typed[0])
        return false;

    int i = 0, j = 0;
    while (i < name.size() && j < typed.size())
    {
        //if both are equal
        if (name[i] == typed[j])
        {
            i++;
            j++;
        }
        else
        {
            //if current character is same as last one -> it is long pressed
            if (typed[j] == typed[j - 1])
                j++;
            else
                return false;
        }
    }

    if (i < name.size())
        return false;

    //if j has not reached the end then check if the remaining is repeated
    //Eg- alex, aallexa
    if (j < typed.size())
    {
        while (j < typed.size())
        {
            //if not repeated than false
            if (typed[j] != typed[j - 1])
                return false;
            j++;
        }
    }

    return true;
}

// 11. Container With Most Water
/*
Approach: 2 Pointer
Time: O(n)
*/
int maxArea(vector<int> &height)
{
    int n = height.size();

    int maxWater = 0, i = 0, j = n - 1;
    while (i < j)
    {
        //length(j-i) * min height
        maxWater = max(maxWater, (j - i) * min(height[i], height[j]));

        if (height[i] < height[j])
            i++;
        else
            j--;
    }

    return maxWater;
}

// 977. Squares of a Sorted Array
/*
Approach: 2 Pointer
Time: O(n)

Approach: 
Since array is sorted, so the max square will either be of the max element or the min element(in case of -ve numbers)
So, We use 2 pointers, start and end
at each step we find the max element between both elements and place it at the end of result array
*/
vector<int> sortedSquares(vector<int> &nums)
{
    int n = nums.size();

    vector<int> res(n);
    int i = 0, j = n - 1, idx = n - 1;
    while (i <= j)
    {
        if (abs(nums[i]) > abs(nums[j]))
        {
            res[idx] = nums[i] * nums[i];
            i++;
        }
        else
        {
            res[idx] = nums[j] * nums[j];
            j--;
        }
        idx--;
    }

    return res;
}

// 169. Majority Element (Boyer Moore Voting Algo)
int majorityElement(vector<int> &nums)
{
    int n = nums.size();
    int cand = nums[0], count = 1;

    for (int i = 1; i < nums.size(); i++)
    {
        if (nums[i] == cand)
            count++;
        else
            count--;

        if (count == 0)
        {
            cand = nums[i];
            count = 1;
        }
    }

    count = 0;
    for (int i = 0; i < nums.size(); i++)
        if (cand == nums[i])
            count++;

    return count > n / 2 ? cand : -1;
}

// 229. Majority Element II
vector<int> majorityElement(vector<int> &nums)
{
    int n = nums.size();

    int cand1 = 0, cand2 = 0, count1 = 0, count2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] == cand1)
            count1++;
        else if (nums[i] == cand2)
            count2++;
        else if (count1 == 0)
        {
            cand1 = nums[i];
            count1 = 1;
        }
        else if (count2 == 0)
        {
            cand2 = nums[i];
            count2 = 1;
        }
        else
        {
            count1--;
            count2--;
        }
    }

    count1 = 0;
    count2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] == cand1)
            count1++;
        else if (nums[i] == cand2)
            count2++;
    }

    vector<int> res;

    if (count1 > n / 3)
        res.push_back(cand1);
    if (count2 > n / 3)
        res.push_back(cand2);

    return res;
}

// 556. Next Greater Element III
/*
Approach:
For the number, start from ones digit, and go left until num[i-1]>num[i]
i.e. until digit to my left is greater than me
When num[i-1]<num[i], then start from i and go right to find the just greater number than num[i-1]
now swap these
Then sort the numbers i to ones place in increasing order to minimise that to get just greater element.
We dont need to sort, we can reverse them, as they are already in decreasing order

If the whole number is in decreasing order then, next greater is not possible

Eg: 8 7 3 9 4 8 7 5 3 2
Start from ones digit i.e. 2 and go left until 4 < 8
Then find just greater than 4 in 8 to 2 which is 5
So, it becomes 8 7 3 9 5 8 7 4 3 2
Now, we have to minimize the number to right of 5 to get the just greater
Reverse(8...2) to get increasing order

Eg: 12222333
We need to find the rightmost just greater, like in this we will swap 2 with 3 on ones place
Then only the reverse will give increasing order

*/
int nextGreaterElement(int n)
{
    string num = to_string(n);

    //Find the first dereasing number
    int i = num.size() - 1;
    while (i > 0 && num[i - 1] >= num[i])
        i--;

    if (i == 0)
        return -1;

    //find the just greater on its right
    long idx1 = i - 1, idx2 = i;
    for (; i < num.size(); i++)
    {
        //we have to find the right most just greater, so use <=
        if (num[i] > num[idx1] && num[i] <= num[idx2])
            idx2 = i;
    }

    // swap the two places
    swap(num[idx1], num[idx2]);

    //reverse the number on right
    reverse(num.begin() + idx1 + 1, num.end());

    long res = stol(num);

    return res > INT_MAX ? -1 : res;
}

// 628. Maximum Product of Three Numbers
/*
Sort the array
Max will be:
1. Last 3 (All positive)
2. First Two(-ve * -ve) * Last(+ve)
*/
int maximumProduct(vector<int> &nums)
{
    if (nums.size() == 0)
        return 0;
    sort(nums.begin(), nums.end());
    return max(nums[nums.size() - 1] * nums[nums.size() - 2] * nums[nums.size() - 3], nums[0] * nums[1] * nums[nums.size() - 1]);
}

// Max Chunks To Make Sorted
/*
Approach: 
It will form a chunk if max till now from left is equal to i
which means that everything smaller than it lies to its left so it can form a chunk
*/
int maxChunksToSorted(vector<int> &arr)
{
    int n = arr.size();
    int maxTillNow = 0, count = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        maxTillNow = max(arr[i], maxTillNow);
        if (maxTillNow == i)
            count++;
    }

    return count;
}

// 768. Max Chunks To Make Sorted II
/*
Approach:
For each index check:
max till now from left(i) <= min from right(i+1)
So, we are checking if everything till now is less than the numbers on my right
then it will form a chunk
*/
int maxChunksToSorted(vector<int> &arr)
{
    int n = arr.size();

    vector<int> leftMax(n);
    vector<int> rightMin(n);

    //left max array
    leftMax[0] = arr[0];
    for (int i = 1; i < n; i++)
        leftMax[i] = max(leftMax[i - 1], arr[i]);

    //right min array
    rightMin[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--)
        rightMin[i] = min(rightMin[i + 1], arr[i]);

    //last element will always form a chunk so 1 for that and check till second last
    int chunks = 1;
    for (int i = 0; i < n - 1; i++)
        if (leftMax[i] <= rightMin[i + 1])
            chunks++;

    return chunks;
}

// 795. Number of Subarrays with Bounded Maximum
/*
Time : O(n), Space : O(1)
Eg: 0 3 1 4 11 1 5 4 6
L = 3, R = 6

For element at index 3, i.e. 4, we have valid arrays:
{4}, {1 4}, {3 1 4}, {0 3 1 4}
For index 6, i.e. 5, we have valid arrays:
{5}, {1 5}

For each element, if it is 
1. a[i]<L : then it can be a part of all valid subarrays before it until the last valid index
   So, ans = ans + count for last element

2. a[i] in range: then this element will form 1 subarray alone,
and can be added to every valid subarray before it till last valid index
So, ans: (i - last valid index) + 1
here, i - last valid index gives the count of valid subarrays before it

3. a[i] > R : then we will reset the valid count to 0 as no element after it can be a part of any subarray before it
and we change the last  valid idx to current idx + 1, as this index will be invalid and we start from its right

*/
int numSubarrayBoundedMax(vector<int> &A, int L, int R)
{
    int n = A.size();
    int count = 0, dp = 0, lastIdx = 0; //count = total ans, dp = last valid count, lastIdx = last valid index

    for (int i = 0; i < n; i++)
    {
        if (A[i] < L)
            count += dp;
        else if (A[i] >= L && A[i] <= R)
        {
            dp = i - lastIdx + 1;
            count += dp;
        }
        else
        {
            dp = 0;
            lastIdx = i + 1;
        }
    }

    return count;
}

// 747. Largest Number At Least Twice of Others
/*
Find max and second max element
Check if max1 >= 2*max2
*/
int dominantIndex(vector<int> &nums)
{
    //if size is 1 than it is trivially greater than all other
    if (nums.size() == 1)
        return 0;

    //initialise the max1 and max2
    int maxIdx1, maxIdx2;
    if (nums[0] > nums[1])
    {
        maxIdx1 = 0;
        maxIdx2 = 1;
    }
    else
    {
        maxIdx1 = 1;
        maxIdx2 = 0;
    }

    for (int i = 2; i < nums.size(); i++)
    {
        //new max1, put old value in max2
        if (nums[i] > nums[maxIdx1])
        {
            maxIdx2 = maxIdx1;
            maxIdx1 = i;
        }
        //else just update max2, as in [0,0,3,2]
        else if (nums[i] > nums[maxIdx2])
            maxIdx2 = i;
    }

    return nums[maxIdx1] >= 2 * nums[maxIdx2] ? maxIdx1 : -1;
}

// 238. Product of Array Except Self
/*
Time: O(n), Space: O(1)
*/
vector<int> productExceptSelf(vector<int> &nums)
{
    int n = nums.size();
    vector<int> res(n);

    //store left products in the res array itself
    int leftProduct = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        res[i] = leftProduct;
        leftProduct *= nums[i];
    }

    //multiply those leftProducts with the rightProduct
    int rightProduct = nums[n - 1];
    for (int i = n - 2; i > 0; i--)
    {
        res[i] = res[i] * rightProduct;
        rightProduct *= nums[i];
    }

    res[0] = rightProduct;

    return res;
}

// 508. Wiggle Sort (LintCode)
void wiggleSort(vector<int> &nums)
{
    if (nums.size() <= 1)
        return;

    for (int i = 0; i < nums.size() - 1; i++)
    {
        if (i % 2 == 0 && nums[i] > nums[i + 1])
            swap(nums[i], nums[i + 1]);
        if (i % 2 != 0 && nums[i] < nums[i + 1])
            swap(nums[i], nums[i + 1]);
    }
}

// 345. Reverse Vowels of a String
string reverseVowels(string s)
{
    int n = s.size();
    if (n == 0)
        return s;

    vector<char> vowels{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    int i = 0, j = n - 1;
    while (i < j)
    {
        while (i < j && find(vowels.begin(), vowels.end(), s[i]) == vowels.end())
            i++;
        while (j > i && find(vowels.begin(), vowels.end(), s[j]) == vowels.end())
            j--;

        swap(s[i], s[j]);
        i++;
        j--;
    }

    return s;
}

// 41. First Missing Positive
int firstMissingPositive(vector<int> &nums)
{
    int n = nums.size();

    for (int i = 0; i < n; i++)
    {
        while (nums[i] > 0 && nums[i] < n + 1 && nums[nums[i] - 1] != nums[i])
            swap(nums[i], nums[nums[i] - 1]);
    }

    for (int i = 0; i < n; i++)
    {
        if (nums[i] != i + 1)
            return i + 1;
    }

    return n + 1;
}

// 849. Maximize Distance to Closest Person
/*
Approach 1: O(n), O(n)
Let left[i] be the distance from seat i to the closest person sitting to the left of i.
Similarly, let right[i] be the distance to the closest person sitting to the right of i. 
This is motivated by the idea that the closest person in seat i sits a distance min(left[i], right[i]) away.
Then find the position with max distance from both sides.

Approach 2: O(n), O(1)
For each group of K empty seats between two people, we can take into account the candidate answer (K+1) / 2.
For groups of empty seats between the edge of the row and one other person, the answer is K,
and we should take into account those answers too.
*/
//Approach 1:
int maxDistToClosest(vector<int> &seats)
{
    int n = seats.size();

    //distance to closest person on left
    vector<int> leftClosest(n, 0);
    leftClosest[0] = seats[0] == 0 ? 1 : 0;
    for (int i = 1; i < n; i++)
    {
        if (seats[i] != 1)
            leftClosest[i] = leftClosest[i - 1] + 1;
    }

    //distance to closest person on right
    vector<int> rightClosest(n, 0);
    rightClosest[n - 1] = seats[n - 1] == 0 ? 1 : 0;
    for (int i = n - 2; i >= 0; i--)
    {
        if (seats[i] != 1)
            rightClosest[i] = rightClosest[i + 1] + 1;
    }

    int maxDist = -1;
    //update the maxDist for 0 and n-1 index
    if (seats[0] == 0)
        maxDist = rightClosest[0];
    if (seats[n - 1] == 0)
        maxDist = max(maxDist, leftClosest[n - 1]);
    for (int i = 1; i < n - 1; i++)
    {
        //update the maxDist for each index
        int currClosest = min(leftClosest[i], rightClosest[i]);
        if (seats[i] == 0)
        {
            maxDist = max(maxDist, currClosest);
        }
    }

    return maxDist;
}
//Approach 2:
int maxDistToClosest(vector<int> &seats)
{
    int n = seats.size();
    int dist = 0, res = 0;

    //dist for seats in between
    for (int i = 0; i < n; i++)
    {
        if (seats[i] == 1)
            dist = 0;
        else
        {
            dist++;
            res = max(res, (dist + 1) / 2);
        }
    }

    //dist from 0
    for (int i = 0; i < n; i++)
    {
        if (seats[i] == 1)
        {
            res = max(res, i);
            break;
        }
    }

    //dist from n-1
    for (int i = n - 1; i >= 0; i--)
    {
        if (seats[i] == 1)
        {
            res = max(res, n - 1 - i);
            break;
        }
    }

    return res;
}

// 903 · Range Addition (Lintcode)
/*
Approach 1: Brute Force O(n*k)
Approach 2: Time: O(n + k), Space: O(n)(for the result array)
We can use the concept of prefix sum here.
In Prefix sum, we have can find sum of a range in O(1) after making the prefix array.
Here we are given the sum (sort of), and we have to update the array
So, this is reverse of prefix sum.

For every query, we have a {lb, ub, inc}
We will do res[lb] += inc and res[ub] -= inc
This way we can add the inc to every element in range {lb, ub}
We will do prefix sum. Now, every element after lb will get the inc,
and at ub+1, we did a -inc, so it will get cancelled out and not contribute outside of its range.
*/
vector<int> getModifiedArray(int length, vector<vector<int>> &updates)
{
    int n = length;
    vector<int> res(n, 0);

    //For each query, update lb, ub+1 in res, O(k)
    for (int i = 0; i < updates.size(); i++)
    {
        int lb = updates[i][0];
        int ub = updates[i][1];
        int inc = updates[i][2];

        res[lb] += inc;
        if (ub + 1 < n) // ub + 1 < arr.size
            res[ub + 1] -= inc;
    }

    //Do Prefix sum on res, O(n)
    for (int i = 1; i < n; i++)
        res[i] += res[i - 1];

    return res;
}

// 912 · Best Meeting Point (Lintcode)
/*
Approach: O(n*m)
Find median of all 1s in matrix
Median in a 1D array {x1, x2, x3, x4, x5} is x3, for even there are two 1D.

For 2D, find median of all x coords and median of y coords seperately.
This will be the meeting point.
Then find the distance using that meeting point.

To find median you need the xcoords and ycoords to be sorted.
So, use seperate loops for x(row wise) and y(col wise) coords to get them in increasing order
*/
int minTotalDistance(vector<vector<int>> &grid)
{
    vector<int> xcoords, ycoords;

    //Find the xcoords of all 1s
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
            if (grid[i][j] == 1)
                xcoords.push_back(i);
    }
    //Find the ycoords of all 1s
    for (int j = 0; j < grid[0].size(); j++)
    {
        for (int i = 0; i < grid.size(); i++)
            if (grid[i][j] == 1)
                ycoords.push_back(j);
    }

    //Find median
    int medianX = xcoords[xcoords.size() / 2];
    int medianY = ycoords[ycoords.size() / 2];

    //Find total minimum distance
    int minDist = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
            if (grid[i][j] == 1)
                minDist += abs(medianX - i) + abs(medianY - j);
    }

    return minDist;
}

// 75. Sort Colors
void sortColors(vector<int> &nums)
{
    int i = 0, idx = 0, j = nums.size() - 1;
    while (idx <= j)
    {
        if (nums[idx] < 1)
        {
            swap(nums[idx], nums[i]);
            i++;
            idx++;
        }
        else if (nums[idx] > 1)
        {
            swap(nums[idx], nums[j]);
            j--;
        }
        else
            idx++;
    }
}

// 670. Maximum Swap
/*
Approach 1: O(n), O(n)
For eg: 9988853427
Find a suffix max array.
For every digit from left if it is not equal to its suffix max, swap it with it.
In this case, 5 will be the first digit from left not equal to its suffix max.
So, swap it and that is ans.

Approach 2: O(10*n) = O(n), O(10) = O(1)
Store all last occurences of each number in an array (first occurence from right)
So, make 10 size array for digits 0-9
number:     9 9 8 8 8 5 3 4 2 7
lastt idx:  0 1 2 3 4 5 6 7 8 9

Last occurence array :
Idx(Number):  0  1  2 3 4 5  6 7 8 9
last idx:    -1 -1  8 6 7 5 -1 9 4 1

Now, for each number from left check if any number greater than it has occured on its right
Swap those two

*/
// Approach 1:
int maximumSwap(int num)
{
    //Convert int to string
    string str = to_string(num);
    int n = str.size();

    vector<char> suffixMax(n); //store index, not elements

    //Find the suffixMax
    suffixMax[n - 1] = n - 1;
    for (int i = str.size() - 2; i >= 0; i--)
    {
        if (str[i] > str[suffixMax[i + 1]])
            suffixMax[i] = i;
        else
            suffixMax[i] = suffixMax[i + 1];
    }

    //For the first element < its suffixMax, swap it with suffix max and return
    for (int i = 0; i < n; i++)
    {
        if (str[i] < str[suffixMax[i]])
        {
            swap(str[i], str[suffixMax[i]]);
            return stoi(str);
        }
    }

    return num;
}
//Approach 2:
int maximumSwap(int num)
{
    string str = to_string(num);

    vector<int> lastIdx(10, -1);

    //make the lastIdx array
    for (int i = str.size() - 1; i >= 0; i--)
    {
        int n = str[i] - '0';
        if (lastIdx[n] == -1)
            lastIdx[n] = i;
    }

    //start from leftmost number
    for (int i = 0; i < str.size(); i++)
    {
        int n = str[i] - '0';
        //find the largest number on its right
        for (int j = 9; j > n; j--)
        {
            if (lastIdx[j] > i)
            {
                swap(str[i], str[lastIdx[j]]);
                return stoi(str);
            }
        }
    }

    return num;
}

// 754. Reach a Number
/*
Approach: O(sqrt(target))
Keep going towards the number until you reach it or cross it
If you cross it, find the difference between the number and current position.
If difference is:
- Even -> This is the ans
- Odd-> Take another step
    - If Difference is even -> ans
    - Odd -> take another step
        - Now it will definately be even, so got the ans

Whenever the difference between target and your position is even,
The target can be reached by making a step till now negative
Like if we have to reach 17 , and we reach 21 by: 1 + 2 + 3 + 4 + 5 + 6
Then we have to go back 4 steps
So, if we flip +2 to -2, we can do that
As that will decrease 2*2 = 4 steps (2 -> 0 -> -2)
If difference was 6, we can flip to 3 to -3 (3 -> 0 -> -3)

Time: 
n(n+1)/2 = target
=> n^2 = target
=> n = sqrt(target)

For eg: reach 17
1 + 2 + 3 + 4 + 5 + 6 = 21
21 - 17 = 4 , so ans is 6 steps
If we have to reach 14
1 + 2 + 3 + 4 + 5 = 15
15-14 = 1 (Odd)
Take another step -> 15+ 6 = 21
21-14 = 7 (Odd)
Take another step -> 21 + 7 = 28
28-14 = 14 (Even)

Ans is 7 steps

Within 3 you will always get even as
If you got odd first time, then 2nd it will be
even(number) + odd(added) = odd(number)
3rd Time
odd(number) + even(added) = even(number)
*/
int reachNumber(int target)
{
    //convert the negative numbers into positive
    target = abs(target);

    int i = 1, sum = 0;
    //reach or cross the target
    while (sum < target)
    {
        sum += i;
        i++;
    }

    //even
    if ((sum - target) % 2 == 0)
        return i - 1;
    //odd
    else
    {
        sum += i;
        //2nd even
        if ((sum - target) % 2 == 0)
            return i;
        //3rd time it will be even
        else
            return i + 1;
    }
}

// https://www.geeksforgeeks.org/minimum-number-platforms-required-railwaybus-station/
/*
Approach: O(n), O(1)
Similar to Merge two sorted arrays
*/
int findPlatform(int arr[], int dep[], int n)
{
    sort(arr, arr + n);
    sort(dep, dep + n);

    int i = 0, j = 0, currPlatforms = 0, maxPlatforms = INT_MIN;
    while (i < n)
    {
        //Train arrives, <= as, if arrival and departure of two trains are same, we need seperate platforms
        if (arr[i] <= dep[j])
        {
            currPlatforms++;
            i++;
        }
        //Train departs
        else
        {
            currPlatforms--;
            j++;
        }

        maxPlatforms = max(maxPlatforms, currPlatforms);
    }

    return maxPlatforms;
}

// Sieve of Eratosthenes (Standard Algo)
/*
To Find Prime numbers till n
Time: O(n*log(logn)) which is nearly O(n)
Space: O(n)

Time Complexity:
= N/2 + N/3 + N/5 + .......
= N(1/2 + 1/3 1/5 + ......)
= N(loglogn)

It is only valid for n<=10^8
Because we cannot make an array greater than 10^8.
So, loglog(10^8) = log(26) = 6
So, O(Nloglogn) = O(6N)
So, it is nearly linear
*/
vector<int> sieveOfEratosthenes(int n)
{
    vector<bool> nums(n + 1, false); //false: prime, true: non prime
    //for numbers 2 to sqrt(n)
    for (int i = 2; i * i <= n; i++)
    {
        //if this has not been marked, then mark its multiple
        //also it is a prime number
        if (!nums[i])
        {
            //start from its next multiple after itself
            for (int j = 2 * i; j <= n; j += i)
                nums[j] = true;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++)
        if (!nums[i])
            primes.push_back(i);

    return primes;
}

//Segmented Sieve
/*
Approach:
Since the maximum allowed size of array is 10^8, for inputs greater than that we can use segmented sieve
In this,
1. Calculate all primes till root(n) using Sieve of Erastothenes
2. Using those primes calculate the primes is range [m,n].
   Make an array of size n-m+1, then using the primes till root(n) find all primes in that range using sieve algo.
We only need to check for numbers in range n, m
So for each prime, we start marking false from ceil(m / num) * num,
Eg: In [21, 50], 
We get primes till root(50) = [2,3,5,7]
For these primes,we use sieve algo and mark al their multiples
For table of 2 we will start checking from
ceil(21 / 2) * 2 = 11*2 = 22

Eg: input is m = 10^6, n = 10^9
Now we find primes till root(10^9) i.e 10^(4.5) using normal Sieve
Then using those we find the primes in range given

Also, in case m is less than root n, we will have to include the req primes in result as well
Like m = 4, n = 50

*/
vector<int> segmentedSieve(int m, int n)
{
    //get primes till root(n)
    vector<int> primestillRootN = sieveOfEratosthenes(sqrt(n));

    //make nums array of size n-m+1
    vector<bool> nums(n - m + 1, false); //true: non-prime, false: prime

    //for all primes found, run the sieve algo
    //To map the numbers in range m,n to 0 indexing for array, use [j-m]
    for (int i = 0; i < primestillRootN.size(); i++)
    {
        double num = primestillRootN[i];
        for (int j = ceil(m / num) * num; j <= n; j += num)
        {
            if (j - m >= 0)
                nums[j - m] = true;
        }
    }

    vector<int> res;
    //if m < root(n)
    if (m <= sqrt(n))
    {
        //include all till root(n) that are in range
        for (int ele : primestillRootN)
            if (ele >= m)
                res.push_back(ele);
        //now from our array start from the first number after root(n)
        //Eg: In [4, 50], we included 5,7 already, so we start from 8
        for (int i = sqrt(n) - m + 1; i < nums.size(); i++)
            if (!nums[i])
                res.push_back(i + m);
    }
    //else just include all marked prime
    else
    {
        for (int i = 0; i < nums.size(); i++)
            if (!nums[i])
                res.push_back(i + m);
    }

    return res;
}

// 763. Partition Labels
/*
Approach: Time: O(n), Space: O(26)=O(1)
Two keep every character in at most one string, if we include it into a string
then will include till its last occurence into same string

So, make an array of last occurences of all letters.
Now iterate through string again and keep updating the current last occurence it needs to go to.
Whenever you reach that occurence include into res
Similar to Max Sorted Chunks
*/
vector<int> partitionLabels(string S)
{
    //Make the last idx array of all letters
    vector<int> lastIdx(26, 0);
    for (int i = 0; i < S.size(); i++)
        lastIdx[S[i] - 'a'] = i;

    vector<int> res;
    int currLastIdx = 0, si = -1; //start idx of current string
    for (int i = 0; i < S.size(); i++)
    {
        //update the current last idx we need to go to
        currLastIdx = max(currLastIdx, lastIdx[S[i] - 'a']);

        //if this idx is last then push into result the length of current string
        if (i == currLastIdx)
        {
            res.push_back(i - si);
            si = i;
        }
    }

    return res;
}

// 915. Partition Array into Disjoint Intervals
/*
Keep a left Max element (max from 0 till now),
and a right Min element (min from now till n-1)

At each index check if my leftMax <= rightMin of element to my right
then that is the answer
*/
int partitionDisjoint(vector<int> &A)
{
    int n = A.size();
    vector<int> rightMin(n);

    rightMin[n - 1] = A[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        rightMin[i] = min(rightMin[i + 1], A[i]);
    }

    int leftMax = A[0];
    for (int i = 0; i < n - 1; i++)
    {
        leftMax = max(leftMax, A[i]);
        if (leftMax <= rightMin[i + 1])
            return i + 1;
    }

    return -1;
}

// https://www.codechef.com/SNCKPE19/problems/BUDDYNIM
/*
Cases: 
1. If total stones in A != total stones in B
    Alice Wins
2. If total stones in A == total stones in B
    If the number of piles is the same and the structure of all the piles are same
        Bob Wins
    Else
        Alice wins

The piles also include 0 values, so we have to remove them before comparing the structures
*/
void sol()
{
    int t;
    cin >> t;
    while (t-- > 0)
    {
        int n, m;
        cin >> n >> m;

        vector<int> a, b;

        //dont include 0s into the array
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            if (x != 0)
                a.push_back(x);
        }
        for (int i = 0; i < m; i++)
        {
            int x;
            cin >> x;
            if (x != 0)
                b.push_back(x);
        }

        //update the size for the non zero arrays
        n = a.size();
        m = b.size();

        int atotal = 0, btotal = 0;

        for (int i = 0; i < n; i++)
            atotal += a[i];
        for (int i = 0; i < m; i++)
            btotal += b[i];

        //if total is unequal or (total is same but number of piles is unequal)
        //Alice wins
        if (atotal != btotal || (atotal == btotal && n != m))
        {
            cout << "Alice" << endl;
            continue;
        }

        int flag = 0;
        //sort to compare the structures
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        for (int i = 0; i < n; i++)
        {
            //structure is different -> Alice Wins
            if (a[i] != b[i])
            {
                cout << "Alice" << endl;
                flag = 1;
                break;
            }
        }

        if (flag == 1)
            continue;
        else
            cout << "Bob" << endl;
    }
}

// 881. Boats to Save People
/*
Approach: O(nlogn + n)
If the heaviest person can share a boat with the lightest person, then do so. 
Otherwise, the heaviest person can't pair with anyone, so they get their own boat.
*/
int numRescueBoats(vector<int> &people, int limit)
{
    int n = people.size();

    sort(people.begin(), people.end());

    //if the heaviest person is above limit,
    //not possible to fit them all
    if (people[n - 1] > limit)
        return -1;

    int i = 0, j = n - 1, count = 0;
    while (i < j)
    {
        //heavy and light together
        if (people[j] + people[i] <= limit)
        {
            count++;
            i++;
            j--;
        }
        //heavy alone
        else
        {
            j--;
            count++;
        }
    }

    if (i == j)
        count++;

    return count;
}

// 462. Minimum Moves to Equal Array Elements II
/*
Approach: O(nlogn + n)
Find the median
Median is the element in the middle of a sorted array
Get all elements to the median
*/
int minMoves2(vector<int> &nums)
{
    int n = nums.size();

    sort(nums.begin(), nums.end());

    int median = nums[n / 2];

    int moves = 0;
    for (int ele : nums)
        moves += abs(median - ele);

    return moves;
}

// 905. Sort Array By Parity
/*
Approach: O(n), 
Two Pointer:
start from begin and end
When odd swap with end => end--
When even => begin++

We cant begin++ after swap as we may get odd after swap
Eg: [3,4,2,1]
*/
vector<int> sortArrayByParity(vector<int> &A)
{
    int n = A.size();
    int i = 0, j = n - 1;
    while (i < j)
    {
        if (A[i] % 2 == 1)
        {
            swap(A[i], A[j]);
            j--;
        }
        else
            i++;
    }

    return A;
}

// 920 · Meeting Rooms (Lintcode)
class Interval
{
public:
    int start, end;
    Interval(int start, int end)
    {
        this->start = start;
        this->end = end;
    }
};
bool canAttendMeetings(vector<Interval> &intervals)
{
    //sort using custom comparator, here we use a lambda expression
    sort(intervals.begin(), intervals.end(), [](const Interval &lhs, const Interval &rhs)
         { return lhs.start < rhs.start; });

    //if any interval start is less than previous interval end, return false
    for (int i = 1; i < intervals.size(); i++)
    {
        if (intervals[i].start < intervals[i - 1].end)
            return false;
    }

    return true;
}

// 43. Multiply Strings
/*
Approach:
Things to note:
Eg: a=123, b=56
1.Given two strings a, b, the max size of the product string will be a.size() + b.size()
So, in eg: size of ans will be max 3 + 2 = 5
2.To find the index of the product in answer, we use idx1 = i + j, idx2= i+ j + 1
Eg:
num1: 1 2 3 (i=0,1,2)
num2:   5 6 (j= 0,1)
ans: _ _ _ _ _  (idx = 0,1,2,3,4)

So when we multiply 3*6 = 18
so 18 in ans array will be at idx1 = i + j = 2 + 1 = 3 and idx2 = 2 + 1 + 1 = 4
Meaning 1 at index 3, and 8 at index 4

So, to the res, we multiply two digits, add them to the idx2 and store the remainder(18%10) at idx2, carry(18/10) at idx1
Then when we have  multiplied 123*6
Then we have to multiply by 5, and add the two
So, we will add simultaneously instead of storing them all.
*/
string multiply(string num1, string num2)
{
    int n = num1.size();
    int m = num2.size();
    vector<int> res(n + m, 0);

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            int idx1 = i + j;
            int idx2 = i + j + 1;

            int val = (num1[i] - '0') * (num2[j] - '0') + res[idx2];

            res[idx2] = val % 10;
            res[idx1] += val / 10;
        }
    }

    string product = "";
    int i = 0;
    //to remove prefix zeroes
    while (i < res.size() && res[i] == 0)
        i++;
    while (i < res.size())
    {
        char c = res[i] + '0';
        product += c;
        i++;
    }

    //if product is 0
    if (product.size() == 0)
        return "0";

    return product;
}

// 1031. Maximum Sum of Two Non-Overlapping Subarrays
/*
Wrong Approach 1: Greedy Approach
Pick L size max array first, then pick M size max array
Then Pick M size max first and then L Size max
Then return the max of these two

Eg: 2 2 7 8 9 9 7 2, L=3, M=2
Here pick L size array : 8 9 9
M size : 2 7
Gives 35
Then M size first: 9 9
L size: 2 7 8
Gives 35

But the max ans will be (7 8 9 9 7) = 42
Using this approach we will not get the ans 
As while picking the L or M size max sum subarray first we pick it form inbetween the actual ans
So, We will never be able to pick the remaining.

Wrong Approach 2: Greedy Approach
Take max of: Max L then Max M, Max M then Max L, Max L+M size at once
Eg: 7 10 3 18 5 7
1. L = 10 3 18, M = 2 cant find
2. M = 18 5 , L = 7 10 3
3. L+M = 7 10 3 18 5

But actual ans is 7 10, 18 5 7

So, only way is to check all possible L,M size subarrays
Correct Approach : O(n)
Make a prefixMax, suufixMax where each element is the max window sum of size min(L, M) ending at that index
Then for each window of size max(L, M) , add the max of the max(prefixSum on left, suffixSum on right)
Update overall max for each index
*/
int maxSumTwoNoOverlap(vector<int> &A, int L, int M)
{
    int n = A.size();
    vector<int> prefixMax(n), suffixMax(n);

    int m = min(L, M);
    int l = max(L, M);

    //Prefix Max for window of size min(L, M)
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (i - m >= 0)
            sum = sum + A[i] - A[i - m];
        else
            sum = sum + A[i];

        if (i > m - 1)
            prefixMax[i] = max(prefixMax[i - 1], sum);
        //first window from left
        else if (i == m - 1)
            prefixMax[i] = sum;
    }

    //Suffix Max for window of size min(L, M)
    sum = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (i + m < n)
            sum = sum + A[i] - A[i + m];
        else
            sum = sum + A[i];

        if (n - i > m)
            suffixMax[i] = max(suffixMax[i + 1], sum);
        //first window from right
        else if (n - i == m)
            suffixMax[i] = sum;
    }

    sum = 0;
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        //get sum of current window
        if (i - l >= 0)
            sum = sum + A[i] - A[i - l];
        else
            sum = sum + A[i];

        //update the res
        if (i > l - 1 && i + 1 < n)
            res = max(res, sum + max(prefixMax[i - l], suffixMax[i + 1]));
        //for first window, check with only suffixMax
        else if (i == l - 1)
            res = sum + suffixMax[i + 1];
        //for last window check only prefix max
        else if (i == n - 1)
            res = max(res, sum + prefixMax[i - l]);
    }

    return res;
}

// 42. Trapping Rain Water
//Approach 1 : Time: O(3n), Time: O(2n)
int trap(vector<int> &height)
{
    if (height.size() == 0)
        return 0;

    int n = height.size();
    vector<int> prefixMax(n), suffixMax(n);

    prefixMax[0] = height[0];
    for (int i = 1; i < n; i++)
        prefixMax[i] = max(height[i], prefixMax[i - 1]);

    suffixMax[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; i--)
        suffixMax[i] = max(height[i], suffixMax[i + 1]);

    int totalWater = 0;
    for (int i = 1; i < n - 1; i++)
        totalWater += min(prefixMax[i], suffixMax[i]) - height[i];

    return totalWater;
}
//Approach 2: O(n), O(1)
int trap(vector<int> &height)
{
    if (height.size() == 0)
        return 0;

    int n = height.size();
    int i = 0, j = n - 1;
    int leftMax = height[0], rightMax = height[n - 1], totalWater = 0;
    while (i < j)
    {
        leftMax = max(leftMax, height[i]);
        rightMax = max(rightMax, height[j]);

        if (leftMax < rightMax)
            totalWater += leftMax - height[i++];
        else
            totalWater += rightMax - height[j--];
    }

    return totalWater;
}

// 407. Trapping Rain Water II
int trapRainWater(vector<vector<int>> &heightMap)
{
    int n = heightMap.size();
    int m = heightMap[0].size();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    //push first and last row into priority queue
    for (int i = 0; i < m; i++)
    {
        pq.push({heightMap[0][i], 0, i});
        pq.push({heightMap[n - 1][i], n - 1, i});
        vis[0][i] = true;
        vis[n - 1][i] = true;
    }
    //push first and last column into priority queue
    for (int i = 0; i < n; i++)
    {
        pq.push({heightMap[i][0], i, 0});
        pq.push({heightMap[i][m - 1], i, m - 1});
        vis[i][0] = true;
        vis[i][m - 1] = true;
    }

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int totalWater = 0, maxTillNow = 0;
    while (pq.size() != 0)
    {
        int h = pq.top()[0];
        int i = pq.top()[1];
        int j = pq.top()[2];
        pq.pop();

        maxTillNow = max(maxTillNow, h);

        for (int d = 0; d < 4; d++)
        {
            int x = i + dir[d][0];
            int y = j + dir[d][1];

            if (x >= 0 && y >= 0 && x < n && y < m && !vis[x][y])
            {
                vis[x][y] = true;
                totalWater += max(0, maxTillNow - heightMap[x][y]);
                pq.push({heightMap[x][y], x, y});
            }
        }
    }

    return totalWater;
}

// 239. Sliding Window Maximum
/*
Approach 1: O(3n), O(2n)
Using Prefix Max and Suffix Max
To find the prefix and suffix max, we only maintain the max of each window
For Eg: 1 3 -1 -3 5 3 6 7, K=3
So prefix max: 1 3 3 -3 5 5 6 7
suffix max: 3 3 -1 5 5 3 7 7
Whenever a new window starts, the max of that index is itself

so ans[i] = max(suffixMax[i], prefixMax[i + k - 1])
suffixMax[i] = suffix max of the first element of window
prefixMax[i + k - 1] = prefix max of the last element of window

So there will be 2 types of windows
Eg: (1 3 -1) (-3 5 3) (6 7)
1. Within 1 complete window like (-3 5 3)
    In this case prefix max = suffix max
2. part of two windows like (-1 -3 5)
    In this case, suffix max gives max of first window, and prefix max gives max of second window

Approach 2: O(n), O(n)
Using a queue to maintain the max of window

*/
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    int n = nums.size();
    vector<int> prefixMax(n), suffixMax(n);

    //make prefixMax
    for (int i = 0; i < n; i++)
    {
        //for first element and start of windows from left
        if (i == 0 || i % k == 0)
            prefixMax[i] = nums[i];
        //for other elements of window
        else
            prefixMax[i] = max(prefixMax[i - 1], nums[i]);
    }

    //make suffixMax
    for (int i = n - 1; i >= 0; i--)
    {
        //for last element and start of windows from right
        if (i == n - 1 || (i + 1) % k == 0)
            suffixMax[i] = nums[i];
        //for other elements of window
        else
            suffixMax[i] = max(suffixMax[i + 1], nums[i]);
    }

    //find result
    vector<int> res(n - k + 1);
    for (int i = 0; i < n - k + 1; i++)
    {
        res[i] = max(suffixMax[i], prefixMax[i + k - 1]);
    }

    return res;
}
//Approach 2:
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    vector<int> res;
    list<int> que;
    int i;

    //add elements of first window
    for (i = 0; i < k; i++)
    {
        //remove all elements from end that are less than current element
        while (que.size() > 0 && nums[que.back()] < nums[i])
            que.pop_back();
        que.push_back(i);
    }

    res.push_back(nums[que.front()]);

    for (; i < nums.size(); i++)
    {
        //remove first element if its index is out of current window
        if (que.size() > 0 && que.front() <= (i - k))
            que.pop_front();

        //remove all elements from end that are less than current element
        while (que.size() > 0 && nums[que.back()] < nums[i])
            que.pop_back();

        //add the current element
        que.push_back(i);

        //front of que is max element of window
        res.push_back(nums[que.front()]);
    }

    return res;
}

// 56. Merge Intervals
vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    if (intervals.size() == 0)
        return {};

    vector<vector<int>> res;
    sort(intervals.begin(), intervals.end());
    res.push_back(intervals[0]);
    int j = 0;
    for (int i = 1; i < intervals.size(); i++)
    {
        //if the start point of current interval is less than end point of previous interval, then merge with previous
        if (intervals[i][0] <= res[j][1])
        {
            res[j][0] = min(res[j][0], intervals[i][0]);
            res[j][1] = max(res[j][1], intervals[i][1]);
        }
        //else push it as a new interval into res
        else
        {
            res.push_back(intervals[i]);
            j++;
        }
    }

    return res;
}

// 986. Interval List Intersections
/*
Approach: O(n)
Two Intervals overlap in two cases:

|______|             |_______|      1
    |______|  OR  |______|          2

They will overlap only when
start2 <= end1 && start1 <= end2 
interval: [max(start1, start2), min(end1, end2)]

Because we may get (8,12)  and (13, 15) here start1<end2 but they dont overlap

Algo
Take two pointers: i=0 , j=0, one for each list
Check both conditions -> get interval: [max(start1, start2), min(end1, end2)]
Whichever has smaller end point move that pointer ahead
*/
vector<vector<int>> intervalIntersection(vector<vector<int>> &firstList, vector<vector<int>> &secondList)
{
    vector<vector<int>> res;

    int n = firstList.size(), m = secondList.size();
    int i = 0, j = 0;

    while (i < n && j < m)
    {
        int start1 = firstList[i][0];
        int end1 = firstList[i][1];
        int start2 = secondList[j][0];
        int end2 = secondList[j][1];

        if (start2 <= end1 && start1 <= end2)
        {
            int si = max(start1, start2);
            int ei = min(end1, end2);
            res.push_back({si, ei});
        }

        if (end1 < end2)
            i++;
        else
            j++;
    }

    return res;
}

// 57. Insert Interval
vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
{
    int n = intervals.size();
    vector<vector<int>> res;

    int i = 0;
    //add all intervals less than the new interval to res i.e. whose end < newInterval Start
    while (i < n && intervals[i][1] < newInterval[0])
        res.push_back(intervals[i++]);

    //merge until current interval <= new interval end
    vector<int> mergedInterval = newInterval;
    while (i < n && intervals[i][0] <= newInterval[1])
    {
        mergedInterval[0] = min(intervals[i][0], mergedInterval[0]);
        mergedInterval[1] = max(intervals[i][1], mergedInterval[1]);
        i++;
    }
    res.push_back(mergedInterval);

    //add remaining into res
    while (i < n)
        res.push_back(intervals[i++]);

    return res;
}

// 134. Gas Station
/*
Approach 1: O(n) (Shubesh Sir's Approach)
Algo: 
If total gas < total cost 
    No ans possible.
Else
    1. Calculate Delta(Gas-Cost), prefixDelta (Prefix sum of delta)
    2. Now find the min prefix delta
    3. Ans is minIdx + 1

Eg:
10 6 1 3 12 3 9 7 4         Gas
9 4 2 6 5 8 10 3 7          Cost
1 2 -1 -3 7 -5 -1 4 -3      Delta
1 3 2 -1 6 1 0 4 1          PrefixDelta

Min prefix delta is -1 at i=3
So ans is index 4 i.e. station with gas=12

Approach 2: O(n) (Discuss Section approach)
If From Station A, you can only reach station B
Then from any station between A, B, you can never go beyond B
So, we dont need to check for those
*/
//Approach 1:
int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{
    int n = gas.size();
    int totalGas = 0, totalCost = 0;
    for (int i = 0; i < n; i++)
    {
        totalCost += cost[i];
        totalGas += gas[i];
    }

    if (totalGas < totalCost)
        return -1;

    int minPrefixDeltaIdx = 0, minPrefixDelta = 10e8, prefixDelta = 0;

    for (int i = 0; i < n; i++)
    {
        int delta = gas[i] - cost[i];
        prefixDelta += delta;
        if (prefixDelta < minPrefixDelta)
        {
            minPrefixDeltaIdx = i;
            minPrefixDelta = prefixDelta;
        }
    }

    return (minPrefixDeltaIdx + 1) % n;
}
//Approach 2:
int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{
    int n = gas.size();

    int maxGas = 0, maxCost = 0;
    for (int i = 0; i < n; i++)
    {
        maxGas += gas[i];
        maxCost += cost[i];
    }

    if (maxGas < maxCost)
        return -1;

    int res = -1;
    for (int i = 0; i < n; i++)
    {
        int currStation = i, count = 0, currGas = 0;
        while (count < n)
        {
            //find the gas at current station
            currGas += (gas[currStation] - cost[currStation]);

            //if gas<0, means could not pay the cost, than break;
            //gas=0 is fine, as we were able to pay the whole cost and can move to next station
            if (currGas < 0)
                break;

            //move to next station
            currStation = (currStation + 1) % n;

            //increase the count of stations visited
            count++;
        }

        //cycle complete -> got our answer
        if (count == n)
        {
            res = i;
            break;
        }
        //make this station the current station, thus ignoring all stations b/w A and B
        else
            i = currStation;
    }

    return res;
}

// 891. Sum of Subsequence Widths
/*
Approach: O(nlogn)
In a subsequence, order matters
Eg: [5,2,3,1,4]
Here [5,3,1] is valid, but [5,1,3] is not

But in this question we only need the min and max of subsequence, so order does not matter
So,we do
1. Sort the array
2. For each element, it will be the min element in all subseq that start from it
   and max element in all subseq that end with it
   So, ans = ans + Number of subsequence it is max in * num - Number of subseq it is min in * num

Number of subsequence it is max in = Subseq with elements on its left = 2^(i-1)
Number of subsequence it is min in = Subseq with elements on its right = 2^(n-i-1)
*/
//Approach 1:
int modPow(long x, long n, long M)
{
    if (n == 0)
        return 1;
    else if (n % 2 == 0) //n is even
        return modPow((x * x) % M, n / 2, M);
    else //n is odd
        return (x * modPow((x * x) % M, (n - 1) / 2, M)) % M;
}
int sumSubseqWidths(vector<int> &nums)
{
    int n = nums.size();

    sort(nums.begin(), nums.end());

    const long MOD = 1000000007;
    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        long long maxSubseqCount = modPow(2, i, MOD);
        long long minSubseqCount = modPow(2, n - i - 1, MOD);

        ans = (ans % MOD + (maxSubseqCount % MOD * nums[i] % MOD) % MOD) % MOD;
        ans = (ans % MOD - (minSubseqCount % MOD * nums[i] % MOD) % MOD + MOD) % MOD;
    }

    return ans;
}
//Approach 2: Optimization in Approach 1
int sumSubseqWidths(vector<int> &nums)
{
    int n = nums.size();

    sort(nums.begin(), nums.end());

    const long MOD = 1000000007;
    int ans = 0;

    //Instead of calculating power of 2 everytime, we can find the power of 2 for all i=0 to n, and store them
    //Then use this array to get the required powers of 2 for i and n-i-1
    vector<long> powerOf2(n);
    powerOf2[0] = 1;
    for (int i = 1; i < n; i++)
        powerOf2[i] = (powerOf2[i - 1] * 2) % MOD;

    for (int i = 0; i < n; i++)
    {
        long maxSubseqCount = powerOf2[i];
        long minSubseqCount = powerOf2[n - i - 1];

        // ans = ans + maxSubseqCount * nums[i] - minSubseqCount * nums[i];
        ans = (ans % MOD + (maxSubseqCount % MOD * nums[i] % MOD) % MOD) % MOD;
        ans = (ans % MOD - (minSubseqCount % MOD * nums[i] % MOD) % MOD + MOD) % MOD;
    }

    return ans;
}

// 853. Car Fleet
/*
Approach: O(nlogn + n)
Sort the position and speed in increasing order of position
Two cars are part of fleet if car i's time to reach target is less than car infront of it
Then they both move with the lower car's speed
So, start from end, calculate the time and if time is less than the time for car infront then same fleet
else new fleet
*/
int carFleet(int target, vector<int> &position, vector<int> &speed)
{
    int n = position.size();

    if (n <= 1)
        return n;

    //sort in inc order of position
    vector<vector<int>> cars(n, vector<int>(2));
    for (int i = 0; i < n; i++)
        cars[i] = {position[i], speed[i]};
    sort(cars.begin(), cars.end());

    //last car is 1 fleet
    double fleetTime = ((double)target - cars[n - 1][0]) / cars[n - 1][1];
    int fleetCount = 1;

    //for each car before, find its time
    for (int i = n - 2; i >= 0; i--)
    {
        double currTime = ((float)target - cars[i][0]) / cars[i][1];
        //if time > fleet time, make it a new fleet and update the fleet time for cars before it
        if (currTime > fleetTime)
        {
            fleetTime = currTime;
            fleetCount++;
        }
    }

    return fleetCount;
}

// https://www.geeksforgeeks.org/find-smallest-number-whose-digits-multiply-given-number-n/
/*
Approach:
The answer will always have digits that are all factors of n
So, we have to form a ans containing factors of n whose product is n
To, minimize it we need the least number of digits, so greater factors are better
We can not use factors > 9 as
If we use 12 as a factor of 24, then in the ans we will have to do 1*2*other factors not 12*other factors
So, that is the wrong answer
So, to get the max single digit factors we go 9-0 and whichever is a factor, we divide n by it and do the same for the quotient

Eg: n = 84
So, starting from 9, first factor is 7 and 84/7=12
Now find factors of 12
Also now we can just start from the last factor that is 7, instead of 9 as if they did not divide n
then they wont divide its factors either
Now, factor starting from 7 is 6, 12/6=2
factors of 2 starting from 6, is 2, 2/2 = 1

So factors are = 7,6,2
smallest answer is increasing order of factors = 267

*/
string getSmallest(long long N)
{
    if (N <= 9)
        return to_string(N);

    string res = "";
    int i = 9;
    while (i > 1)
    {
        if (N % i == 0)
        {
            res = to_string(i) + res;
            N /= i;
        }
        else
            i--;
    }

    if (N != 1)
        return "-1";

    return res;
}

// https://www.geeksforgeeks.org/first-negative-integer-every-window-size-k/
/*
Approach: O(n)
start from end
For each element:
    - If it is -ve, then it is the ans
    - else its closest -ve in k size window
    - else ans is 0

So, start from end and keep updating the closest negative number's index
*/
vector<long long> printFirstNegativeInteger(long long int A[], long long int n, long long int k)
{
    vector<long long> res(n - k + 1);
    long long closestNeg = n; //index of closest negative number in window

    for (int i = n - 1; i >= 0; i--)
    {
        //for first window from end
        if (i + k - 1 > n - 1)
        {
            if (A[i] < 0)
                closestNeg = i;
            continue;
        }

        //if the current number is -ve, then it is the ans
        if (A[i] < 0)
        {
            res[i] = A[i];
            closestNeg = i;
        }
        else
        {
            //else if the closest -ve number is in its window, then that is the ans
            if (closestNeg <= i + k - 1)
                res[i] = A[closestNeg];
            //else ans is 0
            else
                res[i] = 0;
        }
    }

    return res;
}

// 883 · Max Consecutive Ones II (Lintcode)
/*
Approach 1: O(n)
Take two pointers i=0, j=0;
Here i = start of consecutive 1s with atmost 1 zero
j = end of consecutive 1s with atmost 1 zero

Keep a zeroCount
Keep incresing j until zeroCount<=1
When zeroCount becomes >1, we have to remove the extra zero, so increase i until you remove a zero
and ans at each index is given by j-i+1

Worst case this is O(2n)

To get O(n), store the index of last zero encoutered, then while removing zero, jump i directly to that index + 1
*/
int findMaxConsecutiveOnes(vector<int> &nums)
{
    int n = nums.size();
    int i = 0, j = 0, zeroCount = 0, ans = 0, onesCount = 0;

    while (j < n)
    {
        //inc zeroCount if 0
        if (nums[j] == 0)
            zeroCount++;

        //if zeroCount becomes > 1, then remove a zero
        while (zeroCount > 1)
        {
            if (nums[i] == 0)
                zeroCount--;
            i++;
        }

        //update ans
        ans = max(ans, j - i + 1);
        j++;
    }

    return ans;
}

// 1004. Max Consecutive Ones III
/*
Approach O(n):
Exactly same as with 1 zero
Just keep moving i until zeroCount > k

And to use the second approach here we would need extra space
*/
int longestOnes(vector<int> &nums, int k)
{
    int n = nums.size();
    int i = 0, j = 0, zeroCount = 0, ans = 0, onesCount = 0;

    while (j < n)
    {
        if (nums[j] == 0)
            zeroCount++;

        while (zeroCount > k)
        {
            if (nums[i] == 0)
                zeroCount--;
            i++;
        }

        ans = max(ans, j - i + 1);
        j++;
    }

    return ans;
}

// https://www.geeksforgeeks.org/maximum-sum-of-smallest-and-second-smallest-in-an-array/
/*
Approach: O(n)
If we consider all subarrays, we find that the max ans for min + second min you can get is only with 2 size subarrays
Eg: 5 3 1 4 6
Here all subarrays starting with 5 are
5 3 , ans=8
5 3 1, ans=4
5 3 1 4, ans=4
5 3 1 4 6, ans=4

Similarly for arrays starting from other indexes(in subarrays we take consecutive elements)

This is because after first 2 elements there are 3 possibilities for any new element:
 - Next element > first 2 -> min and 2nd min still is first 2
 - Next element < first 2 -> min will change and sum will decrease as new min is smaller
 - Next element between first 2 -> 2nd min will decrease, and so the sum will decrease


So, ans = max of sum of 2 consecutive elements

*/
long long pairWithMaxSum(long long arr[], long long N)
{
    long long res = arr[0] + arr[1];

    for (int i = 1; i < N - 1; i++)
        res = max(res, arr[i] + arr[i + 1]);

    return res;
}

// 632. Smallest Range Covering Elements from K Lists
/*
Approach : O(nlogm) (n=total elements in all lists, m=number of lists)
The approach is similar to Merge K Sorted lists

Use a min pq, to store 1 element from each list at a time
We add the first element of each list into pq
Then we pop the first element and add next element of that list into pq

When we pop we get the min element, this is the start of range
When we push into pq, we update the end of range with max
And each step we, calculate the current range, and update the min range before we push into pq

At a time the pq always contains 1 element from each list.
So getting the top element gives the min of range, and the overall max has the max of range
This helps to find the range and update the answer
*/
vector<int> smallestRange(vector<vector<int>> &nums)
{
    int n = nums.size();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    int currMax = INT_MIN, range = INT_MAX, ansStart, ansEnd;

    //push the first elements of all lists into pq
    for (int i = 0; i < n; i++)
    {
        //find the max while adding to pq
        currMax = max(currMax, nums[i][0]);
        pq.push({nums[i][0], i, 0});
    }

    while (pq.size() > 0)
    {
        //get the min element from pq
        vector<int> rtop = pq.top();
        int ele = rtop[0];
        int i = rtop[1];
        int j = rtop[2];
        pq.pop();

        //if the current range is smaller, then update the answer
        if (currMax - ele + 1 < range)
        {
            range = currMax - ele + 1;
            ansStart = ele;
            ansEnd = currMax;
        }

        //push the next element of the list, whose element we got from pq
        if (j < nums[i].size() - 1)
        {
            //before adding to pq, update the current max
            currMax = max(currMax, nums[i][j + 1]);
            pq.push({nums[i][j + 1], i, j + 1});
        }
        //if list has ended, then break;
        else
            break;
    }

    return {ansStart, ansEnd};
}

// 1679. Max Number of K-Sum Pairs
int maxOperations(vector<int> &nums, int k)
{
    sort(nums.begin(), nums.end());

    int i = 0, j = nums.size() - 1, count = 0;
    while (i < j)
    {
        if (nums[i] + nums[j] < k)
            i++;
        else if (nums[i] + nums[j] > k)
            j--;
        else
        {
            count++;
            i++;
            j--;
        }
    }

    return count;
}

int main()
{
    return 0;
}