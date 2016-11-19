#include <iostream>
#include <vector>
using namespace std;

/*      Combination Sum

Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
The same repeated number may be chosen from C unlimited number of times.
Note:   All numbers (including target) will be positive integers.
        Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
        The solution set must not contain duplicate combinations.

        Ex:, given candidate set 2,3,6,7 and target 7,  A solution set is:  [7] [2, 2, 3]   */

void dfs(vector<int> candidates, int sum, vector<vector<int>> &res, vector<int> &ret, int start)
{
    if (sum>0)
    {
        for (int i=start; i<candidates.size(); i++)
        {
            ret.push_back(candidates[i]);
            dfs(candidates, sum-candidates[i], res, ret, i);
            ret.pop_back();
        }
    }
    else if (sum==0)
        res.push_back(ret);
    else    // sum<0
        return;
}


vector<vector<int> > combinationSum(vector<int> &candidates, int sum)
{
    vector<vector<int> > res;
    vector<int> ret;

    dfs(candidates, sum, res, ret, 0);

    return res;
}
