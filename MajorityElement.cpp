/* Boyer–Moore majority vote algorithm is used to find the majority vote in linear time O(n) and logarithmic space O(logN)
    https://leetcode.com/problems/majority-element/                                                                                                             */

int majorityElement(vector<int> nums)
{
    int candidate, counter = 0;

    for (int x : nums)
    {
        if (counter == 0)
        {
            candidate = x;
            counter = 1;
        }
        else if (candidate == x)
            counter++;
        else // (candidate != x)
            counter--;
    }

    counter = 0;

    for (int x : nums)
    {
        if (candidate == x)
            counter++;
    }

    if (counter > nums.size()/2)
        return candidate;

    return -1;
}


/* Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.
    https://leetcode.com/problems/majority-element-ii/                                                                                                                          */

vector<int> majorityElement(vector<int>& nums)
{
    vector<int> res;

    if (nums.empty())   return res;

    int candidate1, cnt1 = 0;
    int candidate2, cnt2 = 0;

    for (int x : nums)
    {
        if (candidate1 == x)
            cnt1++;
        else if (candidate2 == x)
            cnt2++;
        else if(cnt1 == 0)
        {
            candidate1 = x;
            cnt1 = 1;
        }
        else if (cnt2 == 0)
        {
            candidate2 = x;
            cnt2 = 1;
        }
        else
        {
            cnt1--;
            cnt2--;
        }
    }

    cnt1 = cnt2 = 0;

    for (int x : nums)
    {
        if (candidate1 == x)
            cnt1++;
        else if (candidate2 == x)
            cnt2++;
    }

    if (cnt1 > nums.size()/3)
        res.push_back(candidate1);

    if (cnt2 > nums.size()/3)
        res.push_back(candidate2);

    return res;
}
