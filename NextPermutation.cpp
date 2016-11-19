#include <iostream>
#include <vector>
using namespace std;

// https://leetcode.com/problems/next-permutation/

void nextPermutation(vector<int>& nums)
{
    if (nums.size() <= 1)   return;

    int i, ceil_idx, swap_idx;

    for (i=nums.size()-1; i>0; i--)
    {
        if (nums[i-1] < nums[i])
            break;
    }

    if (i==0)
    {
        sort(nums.begin(), nums.end());
        return;
    }

    swap_idx = i-1;
    ceil_idx = i;

    for (;i<nums.size(); i++)
    {
        if (nums[i]>nums[swap_idx] && nums[i]<nums[ceil_idx])
            ceil_idx = i;
    }


    swap(nums[swap_idx], nums[ceil_idx]);
    sort(nums.begin()+swap_idx+1, nums.end());
}
