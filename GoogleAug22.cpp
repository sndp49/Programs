#include <iostream>
#include <vector>
using namespace std;


/*  There is an array with integers and its length is N, it is sorted,
    how to determine if there is an element repeated more than  N/4.

    Ex:     1, 5, 5, 6, 7, 8, 8, 9  --->  Yes.
            1, 5, 6, 8, 10          --->  No                                                    */



// Complexity: Linear time

int search(vector<int>& nums, int r)
{
  	int count = nums.size()/r, i = 0;

  	while (i<nums.size())
  	{
        int other_idx = i + count - 1;

        if (i + other_idx >= nums.size())
            break;

        if (nums[other_idx] == nums[i])
            return i;				// return index
        else
            i++;
    }

	return -1;
}



// Complexity: O(log N)

int binaryLsearch(vector<int>& nums, int x, int l, int r)
{
    while (l < r)
    {
        int m = l + (r-l)/2;

        if (a[m] == x)
            r = m;
        else if (a[m] < x)
            l = m+1;
    }

    return r;
}

int binaryRsearch(vector<int>& nums, int x, int l, int r)
{
    while (l < r)
    {
        int m = l + (r-l)/2;

        if (a[m] == x)
            l = m;
        else if (a[m] > x)
            r = m-1;
    }

    return l;
}

int search(vector<int>& nums, int r)
{
    int count = nums.size()/r;

    for (int i=0; i<nums.size(); i+=count)
    {
        if (nums[i] == nums[i+count-1])
            return i;
        else if (nums[i+count-1] == nums[i+count])
        {
            int l_idx = binaryLsearch(nums, nums[i+count-1], i, i+count-2);

            int lcnt = i+count - l_idx;

            int r_idx = binaryRsearch(nums, nums[i+count], i+count+1, i+(2*count)-1);

            int rcnt = r_idx - (i+count) + 1;

            if (lcnt + rcnt >= count)
                return  i+count;
        }
    }

    return -1;
}
