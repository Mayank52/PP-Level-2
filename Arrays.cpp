#include <iostream>
#include <vector>

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

//Max Chunks To Make Sorted
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

int main()
{
    return 0;
}