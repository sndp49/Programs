#include "Iterator.h"

Iterator::Iterator(const vector<int>& nums)
{
    this->d = new data(nums.data(), nums.size());
}

Iterator::Iterator(const Iterator& other)
{
    //cout << " Copy Constructor" << endl;
    this->d       = new data(other.d->begin, other.d->n);
    this->d->i    = other.d->i;
}

bool Iterator::hasNext() const
{
    return this->d->i < this->d->n;
}

int Iterator::next()
{
    int ret = *(this->d->begin + this->d->i++);

    return ret;
}

Iterator& Iterator::operator++()
{
    if (this->hasNext())
        this->next();

    return *this;
}

Iterator Iterator::operator++(int)
{
    Iterator tmp(*this);

    if (this->hasNext())
        this->next();

    return tmp;
}

const int& Iterator::operator*()
{   return *(this->d->begin + this->d->i);  }

Iterator::~Iterator()
{
    //cout << "Base destructor... ";
    this->d->begin = NULL;
    delete d;
}

PeekingIterator& PeekingIterator::operator++()
{
    Iterator::next();
    return *this;
}

PeekingIterator  PeekingIterator::operator++(int)
{
    PeekingIterator tmp(*this);
    Iterator::next();
    return tmp;
}

int main()
{
    srand(time(NULL));
    cout << "Peek\tNext" << endl;

    vector<int> nums = {1,2,3,4,5,6};

    PeekingIterator* it = new PeekingIterator(nums);

    while (it->hasNext())
    {
        if (rand()%2)
            cout << it->peek();

        cout << "\t" << it->next() << endl;
    }

    delete it;

    cout << "\n\nUsing Prefix operator" << endl;

    PeekingIterator pre_it(nums);

    while (pre_it.hasNext())
        cout << (++pre_it).peek() << endl;

    cout << "\n\nUsing Postfix operator" << endl;


    PeekingIterator post_it(nums);

    while (post_it.hasNext())
        cout << *(post_it++) << endl;       //cout << (post_it++).peek() << endl;

    cout << endl;

    return 0;
}
