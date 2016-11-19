#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <string>
using namespace std;

class NestedInteger
{
    shared_ptr<void> data;
    int type;                       // 0 => integer  1 => string    2 => nested_list

public:

    NestedInteger(int v)                                    : data(make_shared<int>(v)), type(0)                    { cout << "Integer..." << endl; }
    NestedInteger(string s)                                 : data(make_shared<string>(s)), type(1)                 { cout << "String..." << endl; }
    NestedInteger(const initializer_list<NestedInteger>& l) : data(make_shared<vector<NestedInteger>>(l)), type(2)  { cout << "Nested..." << endl; }

    bool isInteger()    { return (this->type == 0); }
    int  getInteger()   { return *(static_pointer_cast<int>(data)); }

    bool   isString()   { return (this->type == 1); }
    string getString()  { return *(static_pointer_cast<string>(data)); }

    vector<NestedInteger> getList();
};

vector<NestedInteger> NestedInteger::getList()
{
    return *(static_pointer_cast<vector<NestedInteger>>(data));
}


class NestedIterator
{
    stack<NestedInteger> st;

public:
    NestedIterator(const vector<NestedInteger>& l)
    {
        for (int i = l.size()-1; i>=0; i--)
            st.push(l[i]);
    }

    bool hasNext();

    int Next()
    {
        int ret = st.top().getInteger();
        st.pop();

        return ret;
    }
};


bool NestedIterator::hasNext()
{
    if (st.empty()) return false;

    while (!st.top().isInteger())
    {
        vector<NestedInteger> l = st.top().getList();
        st.pop();

        for (int i = l.size()-1; i>=0; i--)
            st.push(l[i]);
    }

    return true;
}

int main()
{
    NestedIterator nit({0, { 1 }, 2, { 3, {4, 5}, { 6, 7, { 8 }}}});

    while (nit.hasNext())
        cout << nit.Next() << ", ";
    cout << endl;

    return 0;
}
