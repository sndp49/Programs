#include <iostream>
#include <vector>
using namespace std;

//  http://www.cplusplus.com/reference/iterator/iterator/

class Iterator
{
protected:
    struct data
    {
        const int *begin;
        int i;
        const int n;

        data(const int* ptr, size_t len) : begin(ptr), i(0), n(len) {}
    };

    data *d;

public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& other);
    virtual ~Iterator();

    bool hasNext() const;
    int  next();

    Iterator&  operator++();        // prefix operator
    Iterator   operator++(int);     // postfix operator

    const int& operator*();
};


class PeekingIterator : public Iterator
{
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {}
    ~PeekingIterator()      { /*cout << "Derived class destructor... ";*/ }

    bool hasNext() const    { return Iterator::hasNext(); }
    int  peek()             { return Iterator(*this).next(); }  // Iterator(*this) makes a copy of current iterator, then call next on the copied iterator to get the next value without affecting current iterator.
    int  next()             { return Iterator::next(); }

    PeekingIterator& operator++();
    PeekingIterator  operator++(int);
    const int&       operator*()        { return *Iterator(*this); }
};
