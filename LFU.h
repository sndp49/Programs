#include <iostream>
#include <unordered_map>
#include <cassert>
using namespace std;

// Complexity: O(1) (delete, insert, find)

class LFU
{
    int capacity;

    struct data                                 // doubly-linked-list to hold data (value)
    {
        int key, value;
        data *prev, *next;

        data(int k, int v) : key(k), value(v)
        {   prev = next = NULL; }
    };

    struct node                                 // doubly-linked-list to hold frequency
    {
        int cnt;

        node *left, *right;

        unordered_map<int, data*> keys;
        data *front, *back;

        node(int count) : cnt(count)
        {
            left = right = NULL;
            front = back = NULL;
        }

        bool isEmpty()  { return (front == NULL); }
    };

    node *head;

    void remove();                              // delete the least frequent data

    unordered_map<int, node*> cache;            // key, frequency node

public:

    LFU(int cap) : capacity(cap)
    {   head = new node(0);   }

    bool insert(const int, const int);

    int getValue(const int);

    void print();
};


bool LFU::insert(const int k, const int v)
{
    if (cache.find(k) != cache.end())
        return false;

    if (cache.size() == capacity)
        remove();           // deleting the least frequent key

    node* cur = NULL;

    if (!head->right)   // empty
    {
        cur = new node(1);

        head->right = cur;
        cur->left   = head;
    }
    else if (head->right->cnt == 1)
        cur = head->right;
    else // head->right->cnt > 1
    {
        cur = new node(1);

        node* nex   = head->right;

        head->right = cur;
        cur->left   = head;
        cur->right  = nex;
        nex->left   = cur;
    }

    if (cur->isEmpty())
        cur->front = cur->back = new data(k, v);
    else
    {
        data* d = new data(k, v);

        cur->back->next = d;
        d->prev = cur->back;

        cur->back = d;
    }

    cache[k] = cur;
    cur->keys[k] = cur->back;

    return true;
}


int LFU::getValue(const int k)
{
    if (cache.find(k) == cache.end())
    {
        cout << "\nError: Key not found" << endl;
        assert(0);
    }

    node* cur = cache[k];
    data* d   = cur->keys[k];

    int val = d->value;

    if (d == cur->front)
    {
        data* nex  = d->next;
        cur->front = nex;

        if (nex)
            nex->prev = NULL;
    }
    else if (d == cur->back)
    {
        data* pre = d->prev;
        cur->back = pre;
        pre->next = NULL;
    }
    else
    {
        data* pre = d->prev;
        data* nex = d->next;

        pre->next = nex;
        nex->prev = pre;
    }

    if (!cur->right)                        // check if cur->right is present
    {
        node* new_node = new node(cur->cnt+1);
        cur->right     = new_node;
        new_node->left = cur;
    }
    else if (cur->right->cnt != 1+cur->cnt)
    {
        node* new_node = new node(cur->cnt+1);

        node* r = cur->right;

        cur->right      = new_node;
        new_node->left  = cur;
        new_node->right = r;
        r->left         = new_node;
    }

    if (!cur->right->front)
    {
        cur->right->front = cur->right->back = d;
        d->prev = d->next = NULL;
    }
    else
    {
        cur->right->back->next = d;
        d->prev = cur->right->back;
        d->next = NULL;
        cur->right->back = d;
    }

    cache[k] = cur->right;                      // mutate cache
    cur->keys.erase(k);                         // delete key from current node
    cache[k]->keys[k] = cur->right->back;       // add key to cur_node+1

    if (cur->isEmpty())
    {
        node* delMe = cur;

        node* l = cur->left;
        node* r = cur->right;

        delete delMe;
        delMe = NULL;

        if (l == head)
        {
            head->right = r;
            r->left = head;
        }
        else
        {
            l->right = r;
            r->left  = l;
        }
    }

    return val;
}


void LFU::remove()
{
    assert(capacity != 0);          // if capacity == 0 assert

    data* del = head->right->front;
    data* nex = del->next;

    int del_key = del->key;

    cache[del_key]->keys.erase(del_key);    // delete keys from cache
    cache.erase(del_key);

    if (!nex)                               // single element in the list
    {
        delete del;
        del = NULL;

        node* delMe     = head->right;
        node* next_node = delMe->right;

        delete delMe;
        delMe = NULL;

        if (!next_node)
            head->right = NULL;
        else
        {
            head->right      = next_node;
            next_node->left  = head;
        }
    }
    else
    {
        delete del;
        del = NULL;

        head->right->front = nex;
        nex->prev = NULL;
    }
}


void LFU::print()
{
    cout << "Key\tValue\tCount" << endl;

    node* cur = head->right;

    while (cur)
    {
        data *curD = cur->front;

        while (curD)
        {
            cout << curD->key << "\t" << curD->value << "\t" << cur->cnt << endl;
            curD = curD->next;
        }

        cur = cur->right;
    }

    cout << endl;
}
