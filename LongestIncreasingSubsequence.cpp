#include <iostream>
#include <vector>
using namespace std;

//  http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/

int ceil (const int x, const vector<int>& al, int len)
{
    int l = -1, r = len-1, m;

    while (r-l > 1)
    {
        m = l+(r-l)/2;

        if (al[m] >= x)
            r = m;
        else
            l = m;
    }

    return r;
}

int LIS(const vector<int>& a)   // returns only lenth
{
    vector<int> al(a.size());   // active lists

    al[0] = a[0];

    int len = 1;    // always point to the empty slot

    for (int i=1; i<a.size(); i++)
    {
        if (a[i] < al[0])       // new smallest element
            al[0] = a[i];
        else if (a[i] > al[len-1])
            al[len++] = a[i];
        else    // a[i] falls in between
            al[ceil(a[i], al, len)] = a[i];
    }

    return len;
}

int ceil (const int x, const vector<int>& al, int len, const vector<int>& nums)
{
    int l = -1, r = len-1, m;

    while (r-l > 1)
    {
        m = l+(r-l)/2;

        if (nums[al[m]] >= x)
            r = m;
        else
            l = m;
    }

    return r;
}


void LIS(const vector<int>& nums, vector<int>& res)
{
    int n = nums.size();

    vector<int> al(n);
    vector<int> prev_index(n, -1);

    al[0] = 0;

    int len = 1;    // always point to the empty slot

    for (int i=1; i<n; i++)
    {
        if (nums[i] < nums[al[0]])
            al[0] = i;
        else if (nums[i] > nums[al[len-1]])
        {
            prev_index[i] = al[len-1];
            al[len++] = i;
        }
        else
        {
            int idx = ceil(nums[i], al, len, nums);
            prev_index[i] = al[idx-1];
            al[idx] = i;
        }
    }

    res.assign(len, 0);

    for (int i=len-1, idx = al[len-1]; idx != -1; idx = prev_index[idx], i--)
        res[i] = nums[idx];
}

int main()
{
    const vector<int> A = {2, 5, 3, 7, 11, 8, 10, 13, 0, 1, 4, 5, 6, 9, 12, 14, 15};
    //const vector<int> A = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9};

    cout << "\nLength of the longest increasing subsequence is " << LIS(A) << endl;

    vector<int> res;
    LIS(A, res);

    for (int elem : res)
        cout << elem << ", ";
    cout << endl;

    return 0;
}


// same as LIS but using upper_bound

int LIS2(const vector<int>& nums)
{
    vector<int> al;

    al.push_back(nums[0]);

    for (int i=1; i<nums.size(); i++)
    {
        if (nums[i] < al[0])
            al[0] = nums[i];
        else if (nums[i] > al.back())
            al.push_back(nums[i]);
        else
        {
            auto it = upper_bound(al.begin(), al.end(), nums[i]);   // upper_bound returns an index with value greater than nums[i]
            *it = nums[i];
        }
    }

    return al.size();
}
