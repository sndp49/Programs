#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/* http://www.geeksforgeeks.org/find-subarray-with-given-sum-in-array-of-integers/
    complexity: O(n)                                                                                                                                                    */

unordered_map<int, int> map;  // sum, till ending index

void subArraySum(vector<int> nums, const int sum)
{
    vector<int> sums;

    int cur_sum = 0;

    for (int i=0; i<nums.size(); i++)
    {
        cur_sum += nums[i];

        if (cur_sum == sum)
        {
            printf("Sum found between indexes [0, %d]\n", i);
            return;
        }
        else if (cur_sum > sum)
        {
            if (map.find(cur_sum - sum) != map.end())
            {
                printf("\nSum found between indexes [%d, %d]\n", map[cur_sum - sum]+1, i);
                return;
            }
        }

        map[cur_sum] = i;
    }

    cout << "There exists no subarray with the given sum" << endl;
}

int main(int argc, char *argv[])
{
    vector<int> nums = {10, 2, -2, -20, 10};
    int sum = -22;

    if (argc == 2)
        sum = atoi(argv[1]);

    subArraySum(nums, sum);

    return 0;
}
