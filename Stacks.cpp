#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>

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

// 316. Remove Duplicate Letters
/*
Approach: O(n)
Similar to remove K digits,
Since we need the lexicographically smallest, we maintain a increasing stack
So, for each element we pop from stack until the top is > the current element
Here we the condition for removing elements is that we can remove duplicates
So, first we find the frequency all elements
Then when we have to pop we will only remove the top if its freq > 0
Also, we will not push an element into the stack if it already contains that element
So, keep a boolean seen to mark the element true when it is pushed into the stack
*/
string removeDuplicateLetters(string s)
{
    vector<int> freq(26, 0);
    vector<bool> seen(26, false);
    stack<char> st;

    for (int i = 0; i < s.size(); i++)
        freq[s[i] - 'a']++;

    for (int i = 0; i < s.size(); i++)
    {
        freq[s[i] - 'a']--;
        if (seen[s[i] - 'a'])
            continue;

        while (st.size() != 0 && st.top() > s[i] && freq[st.top() - 'a'] > 0)
        {
            seen[st.top() - 'a'] = false;
            st.pop();
        }

        st.push(s[i]);
        seen[s[i] - 'a'] = true;
    }

    string ans = "";
    while (st.size() != 0)
    {
        ans += st.top();
        st.pop();
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

// 155. Min Stack
/*
Approach: O(1) for all operations
Keep a stack, a min value = minVal

Push:
Instead of pushing the exact val into stack, we push (val - minVal) into stack.
And if the value we have to push into stack is < minVal
Then update minVal.
Also, since it was less, so the value into stack i.e. val - minVal
would have been -ve.
So, in the stack all -ve values indicate that the minVal was updated
And the original value at that top is equal to the minVal

Pop:
Now as we have pushed (val - minVal) into stack.
So, to retrieve the original value we do
If the top value is > 0 ,
    popped value = top = val - minVal
    So, val = top + minVal
Else
    If the top value is < 0 , then it means that val - minVal < 0,
    which means this val is the new minimum, So, when it is at the top,
    then the minVal will have the original val stored.
    So, val = minVal
    Also, at this point, we will have to update the minVal
    top of stack = top = val - previous minVal
    Here, val = the current minVal
    So, top = minVal - previous minVal
    previous minVal = minVal - top
    So, now our minVal = minVal - top
    And if we have to return the popped value, 
    then the return value is the minVal before updating it just now

Top:
Same as pop
if(top < 0)
    val = minVal + top
else
    val = minVal

getMin:
return the minVal value
*/
class MinStack
{
public:
    /** initialize your data structure here. */
    stack<long> st;
    int minVal = 0;

    MinStack()
    {
    }

    void push(int val)
    {
        if (st.size() == 0)
            minVal = val;

        st.push((long)val - minVal);
        minVal = min(minVal, val);
    }

    void pop()
    {
        if (st.top() < 0)
            minVal -= st.top();

        st.pop();
    }

    int top()
    {
        if (st.top() > 0)
            return st.top() + minVal;
        else
            return minVal;
    }

    int getMin()
    {
        return minVal;
    }
};

// Generate Binary Numbers(https://practice.geeksforgeeks.org/problems/generate-binary-numbers-1587115620/1#)
/*
Approach: BFS, O(n) 
If we make a binary tree with root 1
And for every left child add 0, and add 1 for every right child
Then for every node in a full binary tree(rooted at 1), 
2*i represents its left child
2*i + 1 represents its right child

This way we can get all binary numbers
Because mulitplying number by 2 is equivalent to adding a 0 in binary representation
And mulitplying number by 2 and adding 1 is equivalent to adding a 1 in binary representation
*/
vector<string> generate(int N)
{
    // Your code here
    vector<string> res;

    queue<string> que;
    que.push("1");
    N--;

    while (que.size() > 0)
    {
        string str = que.front();
        que.pop();

        res.push_back(str);

        if (N-- > 0)
            que.push(str + '0');
        if (N-- > 0)
            que.push(str + '1');
    }

    return res;
}

// 946. Validate Stack Sequences
/*
Approach: O(n)
*/
bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
{
    stack<int> st;
    int j = 0;

    for (int i = 0; i < pushed.size(); i++)
    {
        // push current into stack
        st.push(pushed[i]);

        // before moving to next push, pop all elements that have to be popped
        while (j < popped.size() && st.size() > 0 && st.top() == popped[j])
        {
            st.pop();
            j++;
        }
    }

    return j == popped.size();
}

// How to efficiently implement k stacks in a single array?(Not available to submit anywhere)
/*
Approach:
Push: O(1)
Pop: O(1)
Space: O(n)
*/
class KStacksArray
{
public:
    int n = 100;
    int numberOfStacks = 3;
    vector<int> arr, next;
    vector<int> top;
    int free = 0;

    KStacksArray(int size, int sn)
    {
        n = size;
        numberOfStacks = sn;
        arr.resize(size);
        next.resize(size);
        top.resize(sn);
    }
    void push(int val, int stackNo)
    {
        int idx = free;

        arr[idx] = val;
        free = next[idx];
        next[idx] = top[stackNo];
        top[stackNo] = idx;
    }
    int pop(int stackNo)
    {
        int idx = top[stackNo];
        int rem = arr[idx];

        arr[idx] = 0;
        top[stackNo] = next[idx];
        next[idx] = free;
        free = idx;

        return rem;
    }
};

// How to efficiently implement k Queues in a single array?(Not available to submit anywhere)
/*
Approach:
Push: O(1)
Pop: O(1)
Space: O(n)
*/
class KQueuesArray
{
public:
    int n = 100;
    int numberOfQueues = 3;
    vector<int> arr, next;
    vector<int> top;
    int free = 0;

    KQueuesArray(int size, int qn)
    {
        n = size;
        numberOfQueues = qn;
        arr.resize(size);
        next.resize(size);
        top.resize(qn);
    }
    void push(int val, int stackNo)
    {
        int idx = free;

        arr[idx] = val;
        free = next[idx];
        next[idx] = top[stackNo];
        top[stackNo] = idx;
    }
    int pop(int stackNo)
    {
        int idx = top[stackNo];
        int rem = arr[idx];

        arr[idx] = 0;
        top[stackNo] = next[idx];
        next[idx] = free;
        free = idx;

        return rem;
    }
};

// 224. Basic Calculator
/*
Approach: Infix Evaluation
*/
stack<int> operands;
stack<char> operators;
int eval(int val1, int val2, char op)
{
    if (op == '+')
        return val1 + val2;
    else if (op == '-')
        return val1 - val2;
    else if (op == '*')
        return val1 * val2;
    else
        return val1 / val2;
}
void performOperation()
{
    // pop the top 2 operands and evaluate them with the top operator
    int val2 = operands.top();
    operands.pop();
    int val1 = operands.top();
    operands.pop();
    int op = operators.top();
    operators.pop();

    operands.push(eval(val1, val2, op));
}
int calculate(string s)
{
    // map to keep precedence of all operators
    unordered_map<char, int> precedence;
    precedence['+'] = 1;
    precedence['-'] = 1;
    precedence['*'] = 2;
    precedence['/'] = 2;
    precedence['('] = 0;

    if (s[0] == '-')
        s = '0' + s;

    int i = 0;
    while (i < s.size())
    {
        if (s[i] == ' ')
        {
            i++;
            continue;
        }

        // number -> push into operands stack
        if (s[i] >= '0' && s[i] <= '9')
        {
            int num = 0;
            while (i < s.size() && s[i] >= '0' && s[i] <= '9')
            {
                num = num * 10 + (s[i] - '0');
                i++;
            }

            operands.push(num);
        }
        // opening bracket -> push into operators stack
        else if (s[i] == '(')
        {
            operators.push(s[i]);
            i++;
        }
        // closing bracket -> solve everything until the last open bracket
        else if (s[i] == ')')
        {
            while (operators.size() > 0 && operators.top() != '(')
            {
                performOperation();
            }

            // remove the ( bracket
            operators.pop();
            i++;
        }
        // operators
        else
        {
            // if current operator's precedence <= top of stack operator, solve the top
            while (operators.size() > 0 && precedence[s[i]] <= precedence[operators.top()])
            {
                performOperation();
            }

            // then push this operator into stack
            operators.push(s[i]);
            i++;
        }
    }

    // solve the operators remaining in stack
    while (operators.size() > 0)
    {
        performOperation();
    }

    return operands.top();
}

// 895. Maximum Frequency Stack
/*
Approach:
Push: O(1), Pop: O(1)
Space: O(n)

We use a frequency map to maintain {val: frequency}
And a frequencyStack map to maintain {frequency: stack with elements that have this frequency}

Push:
Update the frequency of the element
Then in the frequency stack, push this element to the stack of its current frequency
And update the max frequency

Pop:
Get the top element of the stack corresponding to max frequency
Then update its frequency and pop it from the stack of max frequency
And if the stack of max frequency is now empty
Then reduce the max frequency by 1

While popping max frequency either remains the same or is reduced by 1
Because if the element that was just removed was the only element with that frequency
then its new frequency is the max frequency which is -1 of previous
And if it was not the only max frequency element, then max frequency remains the same
*/
class FreqStack
{
public:
    unordered_map<int, int> freq;
    unordered_map<int, stack<int>> freqStack;
    int maxFreq = 0;

    FreqStack()
    {
    }

    void push(int val)
    {
        freq[val]++;

        freqStack[freq[val]].push(val);

        maxFreq = max(maxFreq, freq[val]);
    }

    int pop()
    {
        int remVal = freqStack[maxFreq].top();
        freqStack[maxFreq].pop();

        if (freq[remVal] > 0)
            freq[remVal]--;

        if (freqStack[maxFreq].size() == 0)
            maxFreq--;

        return remVal;
    }
};

int main()
{
    return 0;
}