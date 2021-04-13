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
int main()
{
    return 0;
}