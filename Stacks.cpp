#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// 739. Daily Temperatures
/*
Approach: O(n), O(n)
Same Approach as Next Greater on Right
Make a stack of indexes, and every time
current element > st.top() index element, then its ans is
res[i] = current index - st.top()
*/
vector<int> dailyTemperatures(vector<int> &temperatures)
{
    int n = temperatures.size();

    stack<int> st;
    vector<int> res(n);

    for (int i = 0; i < n; i++)
    {
        while (st.size() > 0 && temperatures[st.top()] < temperatures[i])
        {
            int idx = st.top();
            st.pop();

            res[idx] = i - idx;
        }

        st.push(i);
    }

    return res;
}

// Maximum Difference
/*
Approach: O(n)
Using only 1 stack
Similar Approach to Next Smaller on Right
In this NSR, elements in stack are always in increasing order
So, for each element
if st.top() element is > current element
Then for the top() element,
next smaller on right = current element
next smaller on left = element just below it in stack

Also, the array may have duplicate elements, so dont push equal elements into the stack
The stack should remain in strictly increasing order    
*/
int findMaxDiff(int A[], int n)
{
    stack<int> st;
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        while (st.size() > 0 && A[st.top()] > A[i])
        {
            // pop the top element, and calculate the diff for its NSR - NSL
            st.pop();

            int nextSmaller = A[i];
            int prevSmaller = st.size() > 0 ? A[st.top()] : 0;

            res = max(res, abs(nextSmaller - prevSmaller));
        }

        if (st.size() > 0 && A[i] == A[st.top()])
            continue;

        st.push(i);
    }

    while (st.size() > 0)
    {
        st.pop();

        int prevSmaller = st.size() > 0 ? A[st.top()] : 0;

        res = max(res, prevSmaller);
    }

    return res;
}

// 84. Largest Rectangle in Histogram
/*
Approach: O(n), O(n)
Using same approach as previous question

For each rectangle,
height = its height
width = NSR - NSL + 1 - 2 = NSR - NSL - 1
area = height * width

We store index in stack
*/
int largestRectangleArea(vector<int> &heights)
{
    stack<int> st;
    st.push(-1);

    int res = 0;

    for (int i = 0; i < heights.size(); i++)
    {
        while (st.top() != -1 && heights[st.top()] > heights[i])
        {
            // calculate the area for element at st.top()
            int h = heights[st.top()];
            st.pop();

            int w = i - st.top() - 1;

            res = max(res, h * w);
        }

        st.push(i);
    }

    // for elements left in stack, NSR is n
    while (st.top() != -1)
    {
        int h = heights[st.top()];
        st.pop();

        int w = heights.size() - st.top() - 1;

        res = max(res, h * w);
    }

    return res;
}

// 85. Maximal Rectangle
/*
Approach: O(n * m)
Keep a heights array, and for each row update the heights array,
and find the largest area rectangle for that array
*/
int largestRectangleArea(vector<int> &heights)
{
    stack<int> st;
    st.push(-1);

    int res = 0;

    for (int i = 0; i < heights.size(); i++)
    {
        while (st.top() != -1 && heights[st.top()] > heights[i])
        {
            // calculate the area for element at st.top()
            int h = heights[st.top()];
            st.pop();

            int w = i - st.top() - 1;

            res = max(res, h * w);
        }

        st.push(i);
    }

    // for elements left in stack, NSR is n
    while (st.top() != -1)
    {
        int h = heights[st.top()];
        st.pop();

        int w = heights.size() - st.top() - 1;

        res = max(res, h * w);
    }

    return res;
}
int maximalRectangle(vector<vector<char>> &matrix)
{
    if (matrix.size() == 0)
        return 0;

    int n = matrix.size();
    int m = matrix[0].size();

    vector<int> heights(m, 0);
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            // if current element is 1, then add 1 to the height of this rectangle
            if (matrix[i][j] == '1')
                heights[j] += 1;
            // if it is 0, then make the height of rectangle, as it cannot make a rectangle
            else
                heights[j] = 0;

        // find the largest rectangle for this array
        res = max(res, largestRectangleArea(heights));
    }

    return res;
}

// 20. Valid Parentheses
bool isValid(string s)
{
    stack<char> st;

    for (char c : s)
    {
        if (c == '(' || c == '{' || c == '[')
        {
            st.push(c);
        }
        else
        {
            if (st.size() == 0)
                return false;
            else if (c == ')' && st.top() != '(')
            {
                return false;
            }
            else if (c == '}' && st.top() != '{')
            {
                return false;
            }
            else if (c == ']' && st.top() != '[')
            {
                return false;
            }
            st.pop();
        }
    }

    return st.size() == 0;
}

// 32. Longest Valid Parentheses
int longestValidParentheses(string s)
{
    stack<int> st;
    st.push(-1);

    int res = 0;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
            st.push(i);
        else
        {
            if (st.top() != -1 && s[st.top()] == '(')
            {
                st.pop();
                res = max(res, i - st.top());
            }
            else
                st.push(i);
        }
    }

    return res;
}

// Count the Reversals(https://practice.geeksforgeeks.org/problems/count-the-reversals0401/1)
/*
Approach: O(n)
First do the same thing as valid paranthesis, to remove all the valid paranthesis
At the end only invalids are left in stack.
Now we count the remaining open brackets, close brackets

We have 4 cases:
Open: Even, Close: Even -> Ans = Open / 2 + Close / 2
Open: Odd, Close: Odd   -> Ans = Open / 2 + Close / 2 + 2
Open: Even, Close: Odd -> Not Possible
Open: Odd, Close: Even  -> Not Possible

Eg: Odd and Odd
Remaining are: }}}{{{
Now From 3 close: }}}
We can reverse One close to make open, that will balance 2 close brackets, 
Similarly for open, reverse 1 open to balance 2 opens
Then We will be left with }{
for this we will have to reverse them both
So, total = 3/2 + 3/2 + 2

Even and Even: }}}}{{{{
Here reverse 2 close two balance the remaining 2 close
And reverse 2 opens to balance the remaining 2 opens
Total = 4/2 + 4/2

In case of odd and even, it is not possible to balance all of them 
as one will be left always as total number is odd

Also, instead of stack, we can just keep a closeCount, openCount
And +1 for open and -1 for close to get the required remaining count
*/
int countRev(string s)
{
    int openCount = 0, closeCount = 0;

    for (char ch : s)
    {
        if (ch == '{')
            openCount++;
        else if (ch == '}')
        {
            // if there is open bracket left before it, then this balances that
            if (openCount > 0)
                openCount--;
            // else this bracket is unbalanced
            else
                closeCount++;
        }
    }

    if (openCount % 2 == 0 && closeCount % 2 == 0)
        return openCount / 2 + closeCount / 2;
    else if (openCount % 2 != 0 && closeCount % 2 != 0)
        return openCount / 2 + closeCount / 2 + 2;
    else
        return -1;
}

// 921. Minimum Add to Make Parentheses Valid
/*
Approach: O(n)
Remove Valid Paranthesis
Whatever remains, is the answer as they all need to be balanced with a new bracket
*/
int minAddToMakeValid(string s)
{
    int openCount = 0, closeCount = 0;

    for (char ch : s)
    {
        if (ch == '(')
            openCount++;
        else if (ch == ')')
        {
            // if there is open bracket left before it, then this balances that
            if (openCount > 0)
                openCount--;
            // else this bracket is unbalanced
            else
                closeCount++;
        }
    }

    return openCount + closeCount;
}

// 735. Asteroid Collision
/*
Approach: O(n)
We have 4 cases:
+, -
-, +
+, +
-, -

Only in case of +, - will both asteroids collide, in all others, they will never collide
So, use a stack and for +ve values push into stack
For -ve values, if the top of stack is positive, then see which has greater value, and push that into stack

In this way whatever is left in the stack at the end is the result.
*/
vector<int> asteroidCollision(vector<int> &asteroids)
{
    stack<int> st;
    vector<int> res;

    for (int i = 0; i < asteroids.size(); i++)
    {
        // +ve value -> push into stack directly
        if (asteroids[i] > 0)
            st.push(asteroids[i]);
        else
        {
            bool destroyed = false;
            // (+, -) -> collision case
            while (st.size() > 0 && st.top() > 0)
            {
                // top is smaller and destroyed
                if (st.top() < abs(asteroids[i]))
                    st.pop();
                // both equal -> both destroyed
                else if (st.top() == abs(asteroids[i]))
                {
                    st.pop();
                    destroyed = true;
                    break;
                }
                // current value is smaller, current is destroyed
                else
                {
                    destroyed = true;
                    break;
                }
            }

            // if current survived, then push it into stack
            if (!destroyed)
                st.push(asteroids[i]);
        }
    }

    // all elements in stack are part of result
    while (st.size() > 0)
    {
        res.push_back(st.top());
        st.pop();
    }

    reverse(res.begin(), res.end());

    return res;
}

// 844. Backspace String Compare
/*
Approach 1: O(n), With Stack
We can just use stacks to find the strings after backspaces, and compare those strings

Approach 2: O(n), Without Stack
We can keep 2 pointers at the end of each string
Then we keep a backspace count for both strings
For each character  if it is a backspace, then increase backspace count
And if the character is not backspace, but ackspace count > 0, then ignore that character

Then compare the characters, where the pointers stop
*/
bool backspaceCompare(string s, string t)
{
    int i = s.size() - 1, j = t.size() - 1;
    int bsCount1 = 0, bsCount2 = 0;

    // run the loop until either string is still remaining, because the only remaining characters might be backspaces
    while (i >= 0 || j >= 0)
    {
        // Keep going back until either this character is a '#' or was removed because of a '#'
        while (i >= 0 && (bsCount1 > 0 || s[i] == '#'))
        {
            if (s[i] == '#')
                bsCount1++;
            else
                bsCount1--;

            i--;
        }

        while (j >= 0 && (bsCount2 > 0 || t[j] == '#'))
        {
            if (t[j] == '#')
                bsCount2++;
            else
                bsCount2--;

            j--;
        }

        // if the characters are not equal
        if (i >= 0 && j >= 0 && s[i] != t[j])
            return false;

        // if one string ended, but other did not
        if ((i < 0 && j >= 0) || (i >= 0 && j < 0))
            return false;

        i--;
        j--;
    }

    // they are equal
    return true;
}

// Reverse First K elements of Queue (https://practice.geeksforgeeks.org/problems/reverse-first-k-elements-of-queue/1#)
/*
Approach: O(n)
1. Push the first k elements into stack and pop them from queue
2. Push the elements of stack back into queue
3. For the que.size() - k elements, which have to maintain the same order, pop them from front
 and push them back into the same queue

 Eg: 1 2 3 4 5 6, K = 3
 Stack: 1 2 3
 Queue: 4 5 6

 Then,
 Stack: Empty
 Queue: 4 5 6 3 2 1

 Then, 
 Queue: 3 2 1 4 5 6
*/
queue<int> modifyQueue(queue<int> que, int k)
{
    //add code here.
    int remCount = que.size() - k;

    stack<int> st;
    while (k-- > 0)
    {
        st.push(que.front());
        que.pop();
    }

    while (st.size() > 0)
    {
        que.push(st.top());
        st.pop();
    }

    while (remCount-- > 0)
    {
        que.push(que.front());
        que.pop();
    }

    return que;
}

// 402. Remove K Digits
/*
Approach: O(n)
To get the smallest number, we basically replace the digits at higher positions
with a digit at a lower position which is smaller
Eg: 45436
Here it is beneficial to replace 4 at leftmost with 3 from its right

So, using this idea, we use a stack and for each element
While the top element > current element and k > 0, pop it

Then at the end the stack contains the answer
*/
string removeKdigits(string num, int k)
{
    stack<char> st;
    string res = "";

    for (int i = 0; i < num.size(); i++)
    {
        // pop until top element > current element and k > 0
        while (k > 0 && st.size() > 0 && st.top() > num[i])
        {
            st.pop();
            k--;
        }

        st.push(num[i]);
    }

    // for remaining k, remove top elements
    while (k-- > 0)
        st.pop();

    // put the stack into result string
    while (st.size() > 0)
    {
        res += st.top();
        st.pop();
    }

    // remove leading zeroes like "002" should be "2"
    for (int i = res.size() - 1; i >= 0; i--)
    {
        if (res[i] == '0')
            res.pop_back();
        else
            break;
    }

    // reverse the result to get the answer
    reverse(res.begin(), res.end());

    return res.size() > 0 ? res : "0";
}

int main()
{
    return 0;
}