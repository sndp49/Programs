#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
using namespace std;

void findSubarray(const vector<int>& arr)   // Optimal solution
{
    int i(0), j, max_len(1);

    pair<int, int> ans(0,0);

    while (i < arr.size())
    {
        bool skip = false;

        for (j = i+max_len-1; j>=i; j--)
        {
            if (arr[j] >= arr[j+1])
            {
                i = j+1;
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            i += max_len-1;

            while (i+1<arr.size() && arr[i] < arr[i+1])
            {
                max_len++;
                i++;
            }

            ans = {i-max_len+1, i};
        }
    }

    printf("\nLongest increasing subarray starts at index %d and ends at index %d \n", ans.first, ans.second);
}

void findSubarray2(const vector<int> arr)       // Finds all increasing subarrays and their lengths
{
    int i, len = arr.size(), max_len = 0, cur_len = 1, longestSubarrayIndex = 0;

    unordered_map<int,int> s;       // Map denoting the last element index and first elemt index
    s[0] = 0;

    for (i=1; i<len; i++)
    {
        if (arr[i] >= arr[i-1])
        {
            s[i] = s[i-1];              // s.emplace(i, s[i-1]);

            cur_len = i - s[i] + 1;

            if (cur_len > max_len)
            {
                max_len = cur_len;
                longestSubarrayIndex = it->first;
            }
        }
        else
            s[i] = i;                   // s.emplace(i, i);
    }

    printf("\nLongest increasing subarray is of length %d and is from [%d,%d] \n", max_len, s[longestSubarrayIndex], longestSubarrayIndex);
}


// Maximum Product in a contiguous subarray
int maxSubarrayProduct(const vector<int> a)
{
    int max_ending_here = 1;    // max positive product ending at the current position; always +ve
    int min_ending_here = 1;    // min negative product ending at the current position; always -ve

    int max_so_far = 1;         // Initialize overall max product

    /* Traverse through the array. Following values are maintained after the i'th iteration:
       max_ending_here is always 1 or some positive product ending with arr[i]
       min_ending_here is always 1 or some negative product ending with arr[i]  */
    for (int i=0; i<a.size(); i++)
    {
        if (a[i] > 0)
        {
            max_ending_here = max_ending_here * a[i];
            min_ending_here = min (min_ending_here * a[i], 1);
        }
        else if (a[i] < 0)
        {
            int tmp = max_ending_here;

            max_ending_here = max (min_ending_here * a[i], 1);
            min_ending_here = tmp * a[i];
        }
        else // (a[i] = 0)
            max_ending_here = min_ending_here = 1;

        max_so_far = max (max_so_far, max_ending_here);
    }

    return max_so_far;
}

int main()
{
    const int array[] = {44,55,66,77,6,7,3,4,7,2,3,4,6,1,2,3,4,5,6,8,9,10,0,1};
    int len = sizeof(array)/sizeof(array[0]);

    vector<int> arr(array, array+len);
    findSubarray(arr);

    const vector<int> a = {6, -3, -10, 0, 2};
    cout << "\nMax continous product in the subarray is " << maxSubarrayProduct(a) << endl;

    return 0;
}
