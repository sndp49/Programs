#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

/*  LRU =>  Least recently used cache (key, value)  Pb 12.16 Pg.97
Create a List of Keys.
Hash table we store for each key a reference to its location in the Queue and value. (hash[key] = pair<auto, value>)
Each time a key is looked up that is found in the hash table, we move it to the front of the queue.
When queue exceeds capacity & a lookup is performed that is not found in the hash-table, the result is placed in the hash-table and at the head of the queue. Item at the tail is deleted.      */

class LRU
{
    typedef unordered_map<int, pair<list<int>::iterator, int>> Table;   // key, < Q location, value >
    Table cache;
    list<int> Q;                                                        // Q of keys

    int capacity;                                                       // Maximum capacity of the cache

    void move2Front(int key, Table::iterator &it)
    {
        Q.erase(it->second.first);
        Q.push_front(key);
        it->second.first = Q.begin();
    }

    public:
        const bool lookup(int key, int* val)
        {
            auto fit = cache.find(key);

            if (fit == cache.end())
                return false;

            *val = fit->second.second;              // return value if found
            move2Front(key, fit);
            return true;
        }

        void insert(int key, int value)
        {
            auto fit = cache.find(key);

            if (fit != cache.end())
                move2Front(key, fit);
            else
            {
                if (cache.size() == capacity)
                {
                    cache.erase(Q.back());
                    Q.pop_back();
                }

                Q.push_front(key);
                //cache.emplace(key, Q.begin(), value);
                cache.emplace(key, make_pair(Q.begin(), value));
            }
        }

        const bool erase(int key)
        {
            auto fit = cache.find(key);
            if (fit == cache.end())
                return false;

            Q.erase(fit->second.first);
            cache.erase(fit);
            return true;
        }
};
