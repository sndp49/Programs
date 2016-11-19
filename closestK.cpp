#include "priorityQ.h"
#include <algorithm>
using namespace std;

// Design an algorithm  to compute the k elements closest to the median of an array

int main()
{
    int k = 4;   // k elements closest

    //int arr[] = {7,14,10,12,2,11,29,3,4,17,28,15,67,6,5,1,8,9};
    int arr[] = {5,1,3,6,2,4,7,8,0,9};
    int i, min, max, len = sizeof(arr)/sizeof(int);

    typedef priority_queue<int, vector<int>, mycomparision> que;

    // Find medians
    que MaxH;           // left
    que MinH(true);     // right

    for (i=0; i<len/2; i++)
        MinH.push(arr[i]);

    for (i=len/2; i<len; i++)
        MaxH.push(arr[i]);

    while(MinH.top() < MaxH.top())
    {
        min = MinH.top();
        MinH.pop();

        max = MaxH.top();
        MaxH.pop();

        MaxH.push(min);
        MinH.push(max);
    }

    if (len%2)
        cout << "\nMedian is => " << MaxH.top() << endl;
    else
        cout << "\nMedians are => " << MinH.top() << ", " << MaxH.top() << endl;

    /*nth_element(arr, arr+((len-1)/2), arr+len);
    cout << "\nMedian is => " << arr[(len-1)/2] << endl;*/

    cout << "\nk elements closest to the median are => " << endl;

    while(k)
    {
        cout << MaxH.top() << ", " << MinH.top() << ", ";
        MaxH.pop();
        MinH.pop();
        k-=2;
    }

    cout << endl;
    return 0;
}
