#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>

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
int maxDistToClosest(vector<int> &seats)
{
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

Approach 2: O(n), O(1)
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
            for (int j = 2*i; j <= n; j += i)
                nums[j] = true;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++)
        if (!nums[i])
            primes.push_back(i);

    return primes;
}


int main()
{
    return 0;
}