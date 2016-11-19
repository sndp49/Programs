#include <iostream>
#include <map>
using namespace std;

class mycomp
{
    bool rev;
public:
    mycomp(bool flag = true) : rev(flag) {}

    bool operator() (const char& lhs, const char& rhs) const
    {
        if (rev)
            return lhs < rhs;   // increasing . Min first
        else
            return lhs > rhs;   // decreasing . Max first
    }
};

void print(multimap<char, int, mycomp>&);

int main()
{
    multimap<char, int, mycomp> mmap;
    mmap.insert(pair<char, int>('a', 1));
    mmap.insert(pair<char, int>('b', 2));
    mmap.insert(pair<char, int>('b', 2));
    mmap.insert(pair<char, int>('c', 3));
    mmap.insert(pair<char, int>('c', 4));
    print(mmap);

    multimap<char, int, mycomp> dmmap(false);
    dmmap.insert(mmap.begin(), mmap.end());
    print(dmmap);

    return 0;
}

void print(multimap<char, int, mycomp>& mmap)
{
    for (auto it = mmap.begin(); it != mmap.end(); it++)
        cout << it->first << " = " << it->second << endl;
    cout << endl;
}


#ifdef false
#include <iostream>
#include <map>
using namespace std;

bool fncomp (char lhs, char rhs) { return lhs>rhs; }

int main ()
{
  multimap<char,int> first;

  first.insert(std::pair<char,int>('a',10));
  first.insert(std::pair<char,int>('b',15));
  first.insert(std::pair<char,int>('b',20));
  first.insert(std::pair<char,int>('c',25));

  bool (*fn_pt) (char,char) = fncomp;
  multimap<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as comp

  fifth.insert(first.begin(), first.end());

  for (auto it = fifth.begin(); it != fifth.end(); it++)
    cout << it->first << "\t" << it->second << endl;

  return 0;
}
#endif
