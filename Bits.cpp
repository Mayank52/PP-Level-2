#include <bits/stdc++.h>

using namespace std;

// Basics
/*
Operators:
OR: |
AND: &
XOR: ^ (Diff: 1, Same: 0)
Negation: ~ (Flip all bits, 0 to 1, and 1 to 0)
Left Shift: << (Shift all bits to left by 1, and append 0 to rightmost position)
Right Shift: >> (Shift all bits to right by 1, and append 0 to leftmost position)
Triple Left Shift: <<<
Triple Right Shift: >>>

Some useful bit operations: 
1. -x = 2's complement = ~x + 1
2. ON ith bit (from right) : x | (1 << i), 
    Eg: x = 10011010, i = 3 => bitmask = 00000100, x | bitmask = 10011110
3. OFF ith bit (from right): x & ~(1 << i)
    Eg: x = 10011010, i = 3 => bitmask = 11111011, x & bitmask = 10011010
4. toggle its bit (from right): x ^ (1 << i)
    Eg: x = 10011010, i = 3 => bitmask = 00000100, x ^ bitmask = 10011110

XOR Properties:
1. x ^ x = 0
2. x ^ y = y ^ x
3. If x ^ y = z, then x = z ^ y
   Because x^y = z => x^y^y = z^y => x = y^z


*/

// Print Value Of Rsb Mask (https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-levelup/bit-manipulation/print-value-of-rsb-mask-official/ojquestion)
int rightmostSetBit(int x)
{
    return x & -x;
}

// Count number of set bits: Kernighans Algorithm (https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-levelup/bit-manipulation/kernighans-algo-official/ojquestion)
int kernighansAlgo(int n)
{
    int count = 0;

    while (n > 0)
    {
        count++;
        n &= (n - 1);
    }

    return count;
}

// Gray Code (https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-levelup/bit-manipulation/gray-code/ojquestion)
vector<int> grayCode(int n)
{
    vector<int> res{0, 1};
    int pos = 2;

    while (n-- > 1)
    {
        vector<int> temp;

        for (int i = 0; i < res.size(); i++)
        {
            int num = res[i] & (0 << pos);
            temp.push_back(num);
        }

        for (int i = res.size() - 1; i >= 0; i--)
        {
            int num = res[i] | (1 << pos);
            temp.push_back(num);
        }

        res = temp;
    }

    return res;
}

// 136. Single Number
/*
Approach: O(n)
x^x = 0
So, x^x^y = y

So, if we take xor of all elements in array, then all duplicates will
cancel each other and only the single element will be left.
*/
int singleNumber(vector<int> &nums)
{
    int res = 0;

    for (int i = 0; i < nums.size(); i++)
        res ^= nums[i];

    return res;
}

// 260. Single Number III
/*
Approach: 
*/
vector<int> singleNumber(vector<int> &nums)
{
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
