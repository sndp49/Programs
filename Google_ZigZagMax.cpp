#include <iostream>
#include <vector>
using namespace std;

// http://www.geeksforgeeks.org/find-the-maximum-element-in-an-array-which-is-first-increasing-and-then-decreasing/

int findMax(const vector<int>& a)
{
    int l = 0, r = a.size()-1, m;

    while (l<r)
    {
        m = l + (r-l)/2;

        if (a[m-1] < a[m])
        {
            if (a[m] > a[m+1])
                return a[m];
            else if (a[m] < a[m+1])
                l = m+1;
        }
        else    // (a[m-1] > a[m])  distinct intergers
        {
            if (a[m] > a[m+1])
                r = m-1;
        }
    }

    return a[l];
}

int main()
{
    const vector<int> nums = {1, 3, 50, 10, 9, 7, 6};
    // const vector<int> nums = {8, 10, 20, 80, 100, 200, 400, 500, 3, 2, 1};
    // const vector<int> nums = {10, 20, 30, 40, 50};       // Corner case (No decreasing part)
    // const vector<int> nums = {120, 100, 80, 20, 0};      // Corner case (No increasing part)

    cout << "Smallest number in the  array is " << min(nums.front(), nums.back()) << endl;
    cout << "Largest element in an array which is first increasing and then decreasing is " << findMax(nums) << endl;

    return 0;
}


/* Algorithm: Binary Search     O(log N)

    if (a[m-1] < a[m] > a[m+1])
        return a[m];
    else if (a[m-1] < a[m] < a[m+1])
        l = m + 1;
    else if (a[m-1] > a[m] > a[m+1])
        r = m - 1;

*/
