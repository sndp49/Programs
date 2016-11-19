#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

/* Given a black box containing sorted elements and two function
    peek() =>   returns an element from the head or tail of the sorted list
    pop()  =>   pops the same element peeked before

    return a sorted list using these two functions in O(n) time                                                                                                                                 */

class BlackBox
{
    vector<int> nums;

    int idx;
public:
    BlackBox(int n) : idx(-1)
    {
        srand (time(NULL));

        for (int i=0; i<n; i++)
        {
            int val = rand()%100;
            nums.push_back(val);
        }

        sort(nums.begin(), nums.end());

        for (int i=0; i<nums.size(); i++)
            cout << nums[i] << ", ";
        cout << endl;
    }

    int     pop();
    int     peek();
    bool    isempty()  { return nums.empty(); }
};

int BlackBox::peek()
{
    if (idx == -1)
        idx = (rand()%2) ? nums.size()-1 : 0;

    return nums[idx];
}

int BlackBox::pop()
{
    if (idx == -1)
        idx = (rand()%2) ? nums.size()-1 : 0;

    int ret = nums[idx];

    if (idx == 0)
        nums.erase(nums.begin());
    else
        nums.pop_back();

    idx = -1;
    return ret;
}
