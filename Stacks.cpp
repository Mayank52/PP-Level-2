#include <iostream>
#include <stack>
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

int main()
{
    return 0;
}