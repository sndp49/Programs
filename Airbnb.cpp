#include <iostream>
#include <vector>
using namespace std;

/*  Provide a set of positive integers (an array of integers). Each integer represent number of nights user request on Airbnb.com.
    If you are a host, you need to design and implement an algorithm, to find out the maximum number a nights you can accommodate. The constrain is that you have to reserve at least one day between each request, so that you have time to clean the room.

Ex: input: [1, 2, 3]             output: 4,  because you will pick 1 and 3
    input: [5, 1, 2, 6]          output: 11, because you will pick 5 and 6
    input: [5, 1, 2, 6, 20, 2]   output: 27, because you will pick 5, 2, 20                                                                                                                                                          */

int findMax(const vector<int>& a)
{
    int i, n = a.size();

    vector<int> cur(a.size(), 0);
    vector<int> max_till_here(a.size()+1, 0);

    max_till_here[n-1] = cur[n-1] = a[n-1];

    for (i=n-2; i>=0; i--)
    {
        cur[i] = a[i] + max_till_here[i+2];
        max_till_here[i] = max(cur[i], max_till_here[i+1]);
    }

    return max_till_here[0];
}


int main()
{
    const vector<int> a = {1,5,1,2,6,20,2};
    //const vector<int> a = {5,1,2,6};
    //const vector<int> a = {1,2,3};

    cout << "\nMaximum the number of days of occupancy " << findMax(a) << endl;
}
