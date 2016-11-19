#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

// http://algs4.cs.princeton.edu/24pq/

class Heap                  // Max Heap
{
    vector<int> nums;

    void heapify(int);
    void buildMaxHeap();

    void swim(int);
    void sink(int i)    { heapify(i); }

public:

    Heap(const vector<int>& v) : nums(v)
    { buildMaxHeap(); }

    bool isEmpty()  { return nums.empty(); }

    int  size()     { return nums.size(); }

    int  top()      { return nums[0]; }
    void pop();

    void push_back(int);        // value
    void update(int, int);      // index, value
};


void Heap::heapify(int i)
{
    int l = 2*i+1, r = 2*i+2, g;

    if (l<size() && nums[l] > nums[i])
        g = l;
    else
        g = i;

    if (r<size() && nums[r] > nums[g])
        g = r;

    if (g != i)
    {
        swap(nums[i], nums[g]);
        heapify(g);
    }
}

void Heap::buildMaxHeap()
{
    for (int i = (size()-1)/2; i>=0; i--)
        heapify(i);
}

void Heap::pop()
{
    nums[0] = nums.back();
    nums.pop_back();

    heapify(0);
}

void Heap::swim(int i)
{
    int p = (i-1)/2;

    if (p >= 0 && nums[p] < nums[i])
    {
        swap(nums[p], nums[i]);
        swim(p);
    }
}

void Heap::push_back(int val)
{
    nums.push_back(val);
    swim(nums.size()-1);
}


void Heap::update(int i, int val)   // Either swim or sink is executed fully. As they are mutually exclusive
{
    if (i>=size())
    {
        cout << "Error: Illegal index" << endl;
        assert(0);
    }

    nums[i] = val;
    swim(i);
    sink(i);
}
