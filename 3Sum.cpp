#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*For example, given array S = {-1 0 1 2 -1 -4},

    A solution set is:
    (-1, 0, 1)
    (-1, -1, 2)                                                                                             */

void printResult(vector<vector<int>>);

vector<vector<int>> threeSum(vector<int>& nums)
{
    int len = nums.size();
    vector<vector<int> > res;

    if (len<3)  return res;

    int l, r, sum;

    sort(nums.begin(), nums.end());

    for (int i=0; i<len-2; i++)
    {
        if (i>0 && nums[i] == nums[i-1])    continue;

        l = i+1; r = len-1;

        while (l<r)
        {
            sum = nums[l]+nums[r];

            if ( sum == -nums[i])
            {
                res.push_back({nums[i], nums[l], nums[r]});
                l++;
                r--;
                while(l<r && nums[l] == nums[l-1])  l++;
                while(l<r && nums[r] == nums[r+1])  r--;
            }
            else if (sum > -nums[i])
                r--;
            else                                // nums[l]+nums[r] < x
                l++;
        }
    }

    return res;
}


int threeSumClosest(vector<int>& nums, int target)
{
    sort(nums.begin(), nums.end());

    int sum, res, diff, min_diff = numeric_limits<int>::max();

    for (int i=0; i<nums.size()-2; i++)
    {
        sum = nums[i] + nums[i+1] + nums[i+2];

        if (sum > target && (sum-target) > final_diff)
            continue;

        sum = nums[i] + nums[nums.size()-2] + nums[nums.size()-1];

        if (sum < target && (target-sum) > final_diff)
            continue;

        int l = i+1, r = nums.size()-1;

        while (l < r)
        {
            sum = nums[i] + nums[l] + nums[r];

            if (target - sum == 0)
                return target;
            if (target - sum < 0)
            {
                diff = abs(target - sum);
                r--;
            }
            else // target-sum > 0
            {
                diff = abs(target - sum);
                l++;
            }

            if (min_diff > diff)
            {
                min_diff = diff;
                res = sum;
            }
        }
    }

    return res;
}


vector<vector<int>> fourSum(vector<int>& nums, int target)
{
    vector<vector<int>> res;

    if (nums.empty())   return res;

    sort(nums.begin(), nums.end());

    int n = nums.size();

    for (int i=0; i<nums.size(); i++)
    {
        int target3 = target-nums[i];

        if (target3 < nums[n-3] + nums[n-2] + nums[n-1])    break;
        if (target3 > nums[n-3] + nums[n-2] + nums[n-1])    continue;

        for (int j=i+1; j<nums.size(); j++)
        {
            int target2 = target3-nums[j];

            if (target2 < nums[n-2] + nums[n-1])    break;
            if (target2 > nums[n-2] + nums[n-1])    continue;

            int l = j+1, r = nums.size()-1;

            while (l<r)
            {
                int sum = nums[l]+nums[r];

                if (sum == target2)
                {
                    vector<int> p = {nums[i], nums[j], nums[l], nums[r]};
                    res.push_back(p);

                    while (p[2] == nums[l])
                        l++;

                    while (p[3] == nums[r])
                        r--;
                }
                else if (sum > target2)
                    r--;
                else
                    l++;
            }

            while (j+1<n && nums[j] == nums[j+1])
                j++;
        }

        while (i+1<n && nums[i] == nums[i+1])
            i++;
    }

    return res;
}

// 4sum with map

vector<vector<int>> fourSum_HashMap(vector<int>& nums, int target)
{
    vector<vector<int>> res;

    int i, j, sum;

    if (nums.size() < 4)
        return res;

    unordered_map<int, vector<vector<int>>> sums;   // sum, {index1, index2}

    sort(nums.begin(), nums.end());

    for (i=0; i<nums.size()-1; i++)
    {
        for (j=i+1; j<nums.size(); j++)
        {
            sum = nums[i] + nums[j];
            sums[sum].push_back({i, j});
        }
    }

    for (i=0; i<nums.size()-1; i++)
    {
        if (i>0 && nums[i-1] == nums[i])    continue;

        for (j=i+1; j<nums.size(); j++)
        {
            if (j>i+1 && nums[j-1] == nums[j])    continue;

            int target2 = target - nums[i] - nums[j];

            auto fit = sums.find(target2);

            if (fit != sums.end())
            {
                for (vector<int> v : fit->second)
                {
                    int x = v[0], y = v[1];

                    if (x > j)   // second pair's first index should be bigger first pair's last index
                    {
                        if (!res.empty() && res.back()[0] == nums[i] && res.back()[1] == nums[j] && res.back()[2] == nums[x] && res.back()[3] == nums[y])
                            continue;

                        res.push_back({nums[i], nums[j], nums[x], nums[y]});
                    }
                }
            }
        }
    }

    return res;
}

int main()
{
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    printResult(threeSum(nums));

    vector<int> nums2 = {1, 0, -1, 0, -2, 2};  // {-5,5,4,-3,0,0,4,-2}   4
    printResult(fourSum(nums2, 0));

    return 0;
}


void printResult(vector<vector<int>> res)
{
    cout << endl;
    for (int i=0; i<res.size(); i++)
    {
        for (int j=0; j<res[i].size(); j++)
            cout << res[i][j] << ", ";
        cout << endl;
    }
    cout << endl;
}
