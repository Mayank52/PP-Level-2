#include <bits/stdc++.h>

using namespace std;

// 208. Implement Trie (Prefix Tree)
/*
Approach: 
insert(string word): O(length of word)
We start with first character of the given word and keep current node at root
Then traverse over the word and for each character check if the current
node has a child for that character or not. If not, then make a new node 
and add it to its children. And then move to the next node.
Do the same for all characters.
At the end, mark true that a word ends here in the node for last character

search(string word): O(length of word)
Same approach as insert
Traverse the word and move to next node in trie for each character
If the next node does not exist for some character, then return false
At the end, if the word ends here is true then return true else return false

startsWith(string prefix): O(length of prefix)
Same as search
At the end if the whole prefix exists in trie, then return true.

*/
class Node
{
public:
    bool endOfWord;
    vector<Node *> children;

    Node()
    {
        this->endOfWord = false;
        children.assign(26, nullptr);
    }
};
class Trie
{
private:
    Node *root;

public:
    /** Initialize your data structure here. */
    Trie()
    {
        root = new Node();
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        Node *curr = root;

        for (int i = 0; i < word.size(); i++)
        {
            if (curr->children[word[i] - 'a'] == nullptr)
            {
                Node *node = new Node();
                curr->children[word[i] - 'a'] = node;
            }

            curr = curr->children[word[i] - 'a'];
        }

        curr->endOfWord = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        Node *curr = root;

        for (int i = 0; i < word.size(); i++)
        {
            if (curr->children[word[i] - 'a'] != nullptr)
                curr = curr->children[word[i] - 'a'];
            else
                return false;
        }

        return curr->endOfWord;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        Node *curr = root;

        for (int i = 0; i < prefix.size(); i++)
        {
            if (curr->children[prefix[i] - 'a'] != nullptr)
                curr = curr->children[prefix[i] - 'a'];
            else
                return false;
        }

        return true;
    }
};

// 211. Design Add and Search Words Data Structure
class WordDictionary
{
private:
    Node *root;

public:
    /** Initialize your data structure here. */
    WordDictionary()
    {
        this->root = new Node();
    }

    void addWord(string word)
    {
        Node *curr = root;

        for (int i = 0; i < word.size(); i++)
        {
            if (curr->children[word[i] - 'a'] == nullptr)
            {
                Node *node = new Node();
                curr->children[word[i] - 'a'] = node;
            }

            curr = curr->children[word[i] - 'a'];
        }

        curr->endOfWord = true;
    }

    bool search(string &word, int idx, Node *curr)
    {
        if (idx == word.size())
            return curr->endOfWord;

        if (word[idx] == '.')
        {
            for (int i = 0; i < curr->children.size(); i++)
            {
                if (curr->children[i] != nullptr && search(word, idx + 1, curr->children[i]))
                    return true;
            }
        }
        else if (curr->children[word[idx] - 'a'] != nullptr)
            return search(word, idx + 1, curr->children[word[idx] - 'a']);

        return false;
    }
    bool search(string word)
    {
        return search(word, 0, root);
    }
};

// 421. Maximum XOR of Two Numbers in an Array
/*
Approach: O(32*n) = O(n)
Make a Trie using the binary representation of each number
Then we use this trie to find the max XOR for each number
In XOR, opposite bits give 1, and same bits give 0
So, if our current bit is 0, then in trie, we try to go to the next node
with value 1, if available else we go to 0. Similarly for 1 we go to 0.
So, for each number we use the trie to find its max answer. And the 
height of trie will be 32 max because int has 32 bits.

Then for each number while traversing we calculate the sum by adding 2^pos to the sum for every XOR = 1
Like for 11010 we have: 2^4 + 2^3 + 0 + 2^1 + 0

So, first to create trie for each number we will need O(32*n).
Since int has only 32 bits, so just go over each bit from leftmost bit, and put it into Trie

And same iteration for finding the max for each number.
For each bit you check if its opposite bit is present as the next child, then add 2*i to the sum
If opposite bit is not present then go to next node, but sum remains the same.
To find the opposite bit we can just use (bit ^ 1) as ^ flips the bit so it will give the opposite bit.

To get the ith bit of a number, we right shift i times, so that ith bit is now rightmost
num >> i, will bring ith bit to rightmost position 
now (num >> i) & 1, will give if last bit is 0 or 1, as 0 & 1 = 0, 1 & 1 = 1

Eg: 3, 10, 5, 25, 2, 8
3: 00011
10: 01010
5: 00101
25: 11001
2: 00010
8: 01000

Now using this make a trie. And then using trie we can find the answer for 
each number by finding the next favorable bit in trie.

*/
class Node
{
public:
    vector<Node *> children; //{0, 1}

    Node()
    {
        this->children.assign(2, nullptr);
    }
};
void insert(int num, Node *root)
{
    Node *curr = root;

    // iterate over all 32 bits i.e. 0 - 31 of the number
    for (int i = 31; i >= 0; i--)
    {
        // to get the ith bit of num
        int bit = (num >> i) & 1;

        if (curr->children[bit] == nullptr)
        {
            Node *node = new Node();
            curr->children[bit] = node;
        }

        curr = curr->children[bit];
    }
}
int maxXOR(int num, Node *root)
{
    int sum = 0;

    Node *curr = root;

    // iterate over all 32 bits i.e. 0 - 31 of the number
    for (int i = 31; i >= 0; i--)
    {
        // to get the ith bit of num
        int bit = (num >> i) & 1;

        // if opposite bit is available
        if (curr->children[(bit ^ 1)] != nullptr)
        {
            curr = curr->children[(bit ^ 1)];
            sum += (1 << i); // sum = sum + 2^i
        }
        // else
        else
        {
            curr = curr->children[bit];
        }
    }

    return sum;
}
int findMaximumXOR(vector<int> &nums)
{
    Node *root = new Node();

    for (int val : nums)
        insert(val, root);

    int res = 0;
    for (int val : nums)
    {
        int myAns = maxXOR(val, root);
        res = max(res, myAns);
    }

    return res;
}

// 677. Map Sum Pairs
class Node
{
public:
    int val;
    vector<Node *> children;

    Node(int val)
    {
        this->val = val;
        this->children.assign(26, nullptr);
    }
};
class MapSum
{
private:
    Node *root;

public:
    /** Initialize your data structure here. */
    MapSum()
    {
        root = new Node(0);
    }

    void insert(string key, int val)
    {
        Node *curr = root;

        for (int i = 0; i < key.size(); i++)
        {
            if (curr->children[key[i] - 'a'] == nullptr)
            {
                Node *node = new Node(0);
                curr->children[key[i] - 'a'] = node;
            }

            curr = curr->children[key[i] - 'a'];
        }

        curr->val = val;
    }

    int getSum(Node *node)
    {
        int sum = node->val;

        for (Node *child : node->children)
        {
            if (child != nullptr)
                sum += getSum(child);
        }

        return sum;
    }
    int sum(string prefix)
    {
        Node *curr = root;

        for (int i = 0; i < prefix.size(); i++)
        {
            if (curr->children[prefix[i] - 'a'] == nullptr)
                return 0;

            curr = curr->children[prefix[i] - 'a'];
        }

        return getSum(curr);
    }
};

// 472. Concatenated Words
/*
Approach: O(n * maxWordLength^2), Trie + DP
First make a Trie using all words.
Then similar to word break, for each word we iterate over it until it is present in Trie.
If at any character, we find that a word has ended here, then we make a call to check for the remaining 
word again from the top of the trie. And after the whole word has ended if the count is 2 or more then return true.

Eg: 
Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Here for "catsdogcats"
We start checking for 0th index. This goes until it finds that 'cat' is a word.
So, then we check for the remaining "sdogcats" from the top of the trie again.
We cannot just keep checking after the 't' node in trie, because then we will find that 
'cats' is also a word, and the count will become 2. But althought there are 2 words in 'cats' i.e. cat and cats
but they are not concatenated.
So, we need to check for the next word from the root again.

Also, for eg: [a, aa,aaa,aaaaa,aaaaaa]
In this case we will keep checking for same case again and again
So, use memoization to improve the solution.
*/
class Node
{
public:
    bool endOfWord;
    vector<Node *> children;

    Node()
    {
        this->endOfWord = false;
        children.assign(26, nullptr);
    }
};
Node *root;
void insert(string word)
{
    Node *curr = root;

    for (int i = 0; i < word.size(); i++)
    {
        if (curr->children[word[i] - 'a'] == nullptr)
        {
            Node *node = new Node();
            curr->children[word[i] - 'a'] = node;
        }

        curr = curr->children[word[i] - 'a'];
    }

    curr->endOfWord = true;
}
bool isConcatenated(string &word, int idx, int count, vector<int> &dp)
{
    // if word is finished, then if count >= 2, then return true, else false
    if (idx == word.size())
        return count > 1;

    if (dp[idx] != -1)
        return dp[idx];

    // start checking from root of Trie
    Node *curr = root;

    for (int i = idx; i < word.size(); i++)
    {
        // if the next character is not present in trie, then just return false
        if (curr->children[word[i] - 'a'] == nullptr)
            return dp[idx] = false;

        curr = curr->children[word[i] - 'a'];

        // if current character is a end of word, then we increase count by 1, and check if the remaining string is concatenated
        if (curr->endOfWord)
        {
            if (isConcatenated(word, i + 1, count + 1, dp))
                return dp[idx] = true;
        }
    }

    return dp[idx] = false;
}
vector<string> findAllConcatenatedWordsInADict(vector<string> &words)
{
    root = new Node();

    // Insert all words into Trie
    for (string &word : words)
        insert(word);

    vector<string> res;
    for (string &word : words)
    {
        // create a new dp for this word
        vector<int> dp(word.size(), -1);

        // if this word is concatenated, then push it into result
        if (isConcatenated(word, 0, 0, dp))
            res.push_back(word);
    }

    return res;
}

// 212. Word Search II
/*
Approach: O((n*m)*(4^(n*m)))
Put all words into Trie. For each node also keep the word that end there.
Then go to each element in the matrix, if the root has a child for that character, then start searching for any
words in the trie starting from that character
For searching check all 4 directions of the current cell, and if the current trie node has a child
with that character, then move to that cell.
For each cell check if the endOfWord for the current node is true, then add the word into result, and mark 
the endOfWord as false so that same word is not added more than once.
Also mark each cell visited so that you dont visit again, and unmark while backtracking.
*/
class Node
{
public:
    bool endOfWord;
    string word;
    vector<Node *> children;

    Node()
    {
        this->endOfWord = false;
        children.assign(26, nullptr);
    }
};
Node *root;
vector<string> res;
void insert(string word)
{
    Node *curr = root;

    for (int i = 0; i < word.size(); i++)
    {
        if (curr->children[word[i] - 'a'] == nullptr)
        {
            Node *node = new Node();
            curr->children[word[i] - 'a'] = node;
        }

        curr = curr->children[word[i] - 'a'];
    }

    curr->endOfWord = true;
    curr->word = word;
}
void search(vector<vector<char>> &board, int i, int j, Node *curr)
{
    int n = board.size(), m = board[0].size();

    if (curr->endOfWord)
    {
        res.push_back(curr->word);
        curr->endOfWord = false;
    }

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    char ch = board[i][j];
    board[i][j] = '#';

    for (int d = 0; d < 4; d++)
    {
        int x = i + dir[d][0];
        int y = j + dir[d][1];

        if (x >= 0 && y >= 0 && x < n && y < m && board[x][y] != '#' && curr->children[board[x][y] - 'a'] != nullptr)
            search(board, x, y, curr->children[board[x][y] - 'a']);
    }

    board[i][j] = ch;
}
vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
{
    int n = board.size(), m = board[0].size();

    root = new Node();

    for (string &word : words)
        insert(word);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (root->children[board[i][j] - 'a'] != nullptr)
                search(board, i, j, root->children[board[i][j] - 'a']);
        }
    }

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
