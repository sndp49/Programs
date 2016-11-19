#include <iostream>
#include <vector>
using namespace std;

// Given an array consisting of +ve and -ve integers, find the largest contiguos sub-array, subject to a constraint that the sum is less than K ?

pair<int, int> getSubarray(vector<int> nums, int k)
{
    map<int, int> sums; // sum, index

    int sum = nums[0];
    sums[sum] = 0;

    pair<int, int> res = {0, 0};
    int max_sum = sum;

    for (int i=1; i<nums.size(); i++)
    {
        sum += nums[i];

        if (sum == k)
            return {0, i};

        auto fit = sums.upper_bound(sum - k);

        if (fit != sums.end() && max_sum < sum - fit->first)    //   see explanation below
        {
            max_sum = sum - fit->first;
            res = {fit->second+1, i};
        }
    }

    return res;
}

// Complexity: O(N logN)

#ifdef false
auto fit = sums.upper_bound(sum - K);

    if sum - K = X then upper_bound(X) will return 'Y', such that Y > X

So, if sum - K = X then
       sum - K < Y (since Y > X)

So,    sum - Y < K (so the resultant is strictly less than K)
#endif
