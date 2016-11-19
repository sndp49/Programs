#include <iostream>
#include <vector>
using namespace std;

/*  Given a set of non-negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum.

    Ex: set[] = {3, 34, 4, 12, 5, 2}, sum = 9

    https://www.youtube.com/watch?v=s6FhG--P7z0          Complexity: O(nums.size() * sum)                                                                                                               */


bool isSubsetSum(const vector<int> nums, const int sum)
{
    int m = nums.size();

    vector<vector<bool>> dp(m, vector<bool>(sum+1, false));

    dp[0][nums[0]] = true;

    for (int i=1; i<m; i++)
    {
        for (int j=1; j<=sum; j++)
        {
            if (j < nums[i])
                dp[i][j] = dp[i-1][j];
            else if (j == nums[i])
                dp[i][j] = true;
            else // (j > nums[i])
                dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]];
        }
    }

    // printing
    if (dp[m-1][sum])
    {
        int i = m-1, j = sum;

        while (i>=0 && j>0)
        {
            while (dp[i-1][j])
                i--;

            cout << nums[i] << ", ";

            j = j-nums[i];
            i--;
        }

        cout << endl;
        return true;
    }
    else
        return false;
}

int main(int argc, char *argv[])
{
    const vector<int> nums = {3, 34, 4, 12, 5, 2};
    int sum = 9;

    if (argc == 2)
        sum = atoi(argv[1]);

    if (!isSubsetSum(nums, sum))
        cout << "No subset found" << endl;

    return 0;
}
