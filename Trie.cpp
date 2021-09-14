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
    char ch; // we can remove ch, as we are not actually using this anywhere
    bool endOfWord;
    vector<Node *> children;

    Node(char ch)
    {
        this->ch = ch;
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
        root = new Node('#');
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        Node *curr = root;

        for (int i = 0; i < word.size(); i++)
        {
            if (curr->children[word[i] - 'a'] == nullptr)
            {
                Node *node = new Node(word[i]);
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
class WordDictionary
{
    Node *root;

public:
    /** Initialize your data structure here. */
    WordDictionary()
    {
        root = new Node();
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

So, first to create trie for each number we will need O(32*n)
And same for finding the max for each number.



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
    int val;
    vector<Node *> children; //{0, 1}

    Node(int val)
    {
        this->val = val;
        this->children.assign(2, nullptr);
    }
};
void insert(int num, Node *root)
{
}
int maxXOR(int num, Node *root)
{
    int sum = 0;

    return sum;
}
int findMaximumXOR(vector<int> &nums)
{
    Node *root = new Node(-1);

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
vector<string> findAllConcatenatedWordsInADict(vector<string> &words)
{
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
