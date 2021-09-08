#include <bits/stdc++.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

// 206. Reverse Linked List
ListNode *reverseList(ListNode *head)
{
    ListNode *curr = head;
    ListNode *prev = nullptr;

    while (curr != nullptr)
    {
        ListNode *next = curr->next;

        curr->next = prev;

        prev = curr;
        curr = next;
    }

    return prev;
}

// 876. Middle of the Linked List
ListNode *middleNode(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// 141. Linked List Cycle
bool hasCycle(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;

    while (slow != nullptr && fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}

// 142. Linked List Cycle II
ListNode *detectCycle(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return nullptr;

    ListNode *slow = head;
    ListNode *fast = head;

    while (slow != nullptr && fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            break;
    }

    if (slow != fast)
        return nullptr;

    slow = head;

    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

// 138. Copy List with Random Pointer
/*
Approach: O(n)
1. Make new nodes and put them between the original node and its next node
2. Assign Random Pointers to the new Nodes
3. Extract the new nodes and restore the original list

Eg:
List: 1 2 3 4 5 6

Step 1:
For each node we make a new node and put it in between itself and next node
After Insert:
List: 1 1copy 2 2copy 3 3copy 4 4copy 5 5copy

Step 2: 
Now the random pointer of each new node can easily be assigned. For the current node,
Its next node is its clone. So, the random of clone = next node of random of current
As the current node's random pointer is pointing to the original random node.
And next of that random node is the clone of that random node

Step 3:
Simply take all clone nodes and make a seperate list, and restore the original list

List: 1 2 3 4 5 6
Clone: 1copy 2copy 3copy 4copy 5copy 6copy



*/
Node *copyRandomList(Node *head)
{
    if (head == nullptr)
        return nullptr;

    // insert new nodes
    Node *curr = head;

    while (curr != nullptr)
    {
        Node *clone = new Node(curr->val);
        clone->val = curr->val;
        clone->next = curr->next;
        curr->next = clone;
        curr = curr->next->next;
    }

    // assign random pointers to copied nodes
    curr = head;

    while (curr != nullptr)
    {
        if (curr->random != nullptr)
            curr->next->random = curr->random->next;

        curr = curr->next->next;
    }

    // extract the cloned list
    curr = head;
    Node *cloneHead = head->next;

    while (curr != nullptr)
    {
        Node *clone = curr->next;

        curr->next = curr->next->next;
        if (clone->next != nullptr) // last node does not have a next node
            clone->next = clone->next->next;

        curr = curr->next;
    }

    return cloneHead;
}

// 160. Intersection of Two Linked Lists
/*
Approach 1: O(n)
1. Find length of lists
2. Find the difference between lengths.
3. Whichever list has greater length, traverse it for difference number of nodes such that the remainig
    nodes in both lists are equal
4. Then traverse them both together, and wherever they become equal is the intersection point

Approach 2: Cycle Detection, O(n)
Make the next pointer of one list point to second list's head. Then we will have a cycle in the list
Then just use Floyd's Algo, to find the start of the cyle, that will be the intersection point.
*/
// Approach 2:
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    ListNode *curr = headA;

    while (curr->next != nullptr)
        curr = curr->next;

    // point last node of ListA to headB, thus making a cycle
    curr->next = headB;

    // get the cycle start point
    ListNode *ans = detectCycle(headA);

    // restore the linked list structure
    curr->next = nullptr;

    return ans;
}

// 146. LRU Cache
/*
Approach: O(1) operations
We use a Doubly linked list to maintain the nodes in the order of least recently used
And a hashmap to maintain {key : address} of each node currently present in the list
so that we can access them in O(1) from the list. 

get(int key): O(1)
When we need to get a key from the cache,
We check if it is present in the hashmap.
If it is present then we remove it from its current position in list, and 
put it at the end of the list as it is the most recently used now.
If it is not present then just return -1.

put(int key, int value): O(1)
To put a new element, we check if it is already present
If it is already present, then:
    1. Update its value
    2. Make it most recently used: Remove it from its current position in list, and put in at the end of list.
If it is not present:
    1. Check if the capacity of list is full, we can check the size of hashmap for this
       If capacity is full, then remove the first element of list i.e. the least recently used node.
       So, remove the last node of list, and remove it from the hashmap as well.
    2. Then we make a new node, and add it to the end of list, and put it in the hashmap

In the code, I have made a dummy head and tail for the doubly linked list to avoid all edge cases
while adding and removing nodes. So, the actual first node is the head->next node and the actual 
last node is tail->prev node. We never change the dummy head and tail.
*/
class Node
{
public:
    int key;
    int val;
    Node *next;
    Node *prev;

    Node(int val, int key)
    {
        this->val = val;
        this->key = key;
        next = nullptr;
        prev = nullptr;
    }
};
class LRUCache
{
private:
    Node *head, *tail; // head is oldest, tail is latest
    int capacity;
    unordered_map<int, Node *> mp; //{key: node}

    void addLast(Node *node)
    {
        // add a node just before the dummy tail
        node->next = tail;
        node->prev = tail->prev;

        tail->prev->next = node;
        tail->prev = node;
    }
    void removeNode(Node *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;

        // make a dummy head and tail, so that we dont have to handle edge cases for the linked list
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        // if node is not present
        if (mp.find(key) == mp.end())
            return -1;

        // else remove it from its current position in list, and add at the end
        Node *node = mp[key];

        removeNode(node);
        addLast(node);

        return node->val;
    }

    void put(int key, int value)
    {
        // if already present
        if (mp.find(key) != mp.end())
        {
            // remove it from its current position in list, and add at the end
            Node *node = mp[key];

            node->val = value; // update its value
            removeNode(node);
            addLast(node);
        }
        else
        { // if size is full, then remove the first node
            if (mp.size() == capacity)
            {
                mp.erase(head->next->key);
                removeNode(head->next);
            }

            // add the node to end of the list, and into the map
            Node *node = new Node(value, key);
            addLast(node);
            mp[key] = node;
        }
    }
};

// 460. LFU Cache
class LFUCache
{
public:
    LFUCache(int capacity)
    {
    }

    int get(int key)
    {
    }

    void put(int key, int value)
    {
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
