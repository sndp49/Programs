#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <cassert>
using namespace std;

// Complexity: O(log N)  (insert and find)


class LFU
{
    unordered_map<int, vector<int>> cache;       // key, [value, frequency]
    map<int, unordered_set<int>> freq;           // count, key

    int capacity;
public:

    LFU(int cap) : capacity(cap) {}

    bool insert(int, int);
    int getValue(int);

    void print();
};

bool LFU::insert(int k, int v)                      // Complexity: O(log N)
{
    if (cache.find(k) != cache.end())
        return false;

    if (cache.size() == capacity)
    {
        int minFreq = freq.begin()->first;
        int del = *(freq.begin()->second.begin());   // delete key with least frequency

        if (freq[minFreq].size() == 1)
            freq.erase(minFreq);
        else
            freq[minFreq].erase(del);

        cache.erase(del);
    }

    cache[k] = {v, 1};
    freq[1].insert(k);

    return true;
}

int LFU::getValue(int k)                            // Complexity: O(log N)
{
    if (cache.find(k) == cache.end())
    {
        printf("\nError: Key %d not found", k);
        assert(0);
    }

    int val = cache[k][0];

    freq[cache[k][1]].erase(k);

    if (freq[cache[k][1]].empty())
        freq.erase(cache[k][1]);

    freq[++cache[k][1]].insert(k);

    return val;
}

void LFU::print()
{
    cout << "Key\tValue\tCount" << endl;

    for (auto it = cache.begin(); it != cache.end(); it++)
        cout << it->first << "\t" << it->second[0] << "\t" << it->second[1] << endl;

    cout << endl;
}
