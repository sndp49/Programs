#include <iostream>
#include <vector>
using namespace std;

//  https://leetcode.com/problems/create-maximum-number/

/* Soln:    https://discuss.leetcode.com/topic/36805/c-16ms-fastest-beats-97
            https://discuss.leetcode.com/topic/32298/short-python-ruby-c/2
            https://discuss.leetcode.com/topic/32272/share-my-greedy-solution                                                                                                                                                                       */


vector<int> maxNum(vector<int> nums, const int k)
{
    if (nums.size() == k)
        return nums;

    vector<int> res;

    for (int i=0; i<nums.size(); i++)
    {
        while (!res.empty() && res.size() + nums.size() - i > k && nums[i] > res.back())
            res.pop_back();

        res.push_back(nums[i]);
    }

    res.resize(k);

    return res;
}

vector<int> merge(vector<int> nums1, vector<int> nums2, const int k)
{
    vector<int> res;

    int i = 0, j = 0;

    while (i<nums1.size() && j<nums2.size())
    {
        if (nums1[i] > nums2[j])
            res.push_back(nums1[i++]);
        else if (nums1[i] < nums2[j])
            res.push_back(nums2[j++]);
        else // nums1[i] == nums2[j]
        {
            int p = i, q = j;

            while (p<nums1.size() && q<nums2.size() && nums1[p] == nums2[q])
            {
                p++;
                q++;
            }

            if (q == nums2.size() || (p<nums1.size() && nums1[p] > nums2[q]))
                res.push_back(nums1[i++]);
            else
                res.push_back(nums2[j++]);
        }
    }

    if (i<nums1.size())
        res.insert(res.end(), nums1.begin()+i, nums1.end());

    if (j<nums2.size())
        res.insert(res.end(), nums2.begin()+j, nums2.end());

    return res;
}

vector<int> maximum(vector<int> res, vector<int> nums)
{
    if (res.empty())
        return nums;

    for (int i=0; i<res.size(); i++)
    {
        if (res[i] > nums[i])
            return res;
        else if (res[i] < nums[i])
            return nums;
    }

    return res;
}

vector<int> maxNumber(const vector<int>& nums1, const vector<int>& nums2, const int k)
{
    vector<int> res;

    int m = nums1.size(), n = nums2.size();

    for (int i = max(0, k-n); i <= min(m, k); i++)
        res = maximum(res, merge(maxNum(nums1, i), maxNum(nums2, k-i), k));

    return res;
}

int main()
{
    const vector<int> nums1 = {2,5,6,4,4,0};
    const vector<int> nums2 = {7,3,8,0,6,5,7,6,2};
    int k = 15;

    /*const vector<int> nums1 = {6,7};
    const vector<int> nums1 = {6,0,4};
    const int k = 5;        */

    vector<int> res = maxNumber(nums1, nums2, k);

    for (int i=0; i<res.size(); i++)
        cout << res[i] << ", ";
    cout << endl;

    return 0;
}
