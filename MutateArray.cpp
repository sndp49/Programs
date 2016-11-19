#include <iostream>
#include <vector>
using namespace std;

/*  Given an input array and another array that describes a new index for each element, mutate the input array so that each element ends up in their new index.
    Discuss the runtime of the algorithm and how you can be sure there won't be any infinite loops.                 */

void mutate(vector<int>& nums, const vector<int> move)
{
    vector<int> visited(nums.size(), 0);

    for (int i=0; i<nums.size(); i++)
    {
        if (!visited[i])
        {
            int j = move[i];
            int tmp = nums[i];

            while (!visited[j])
            {
                swap(nums[j], tmp);
                visited[j] = 1;

                j = move[j];
            }
        }
    }
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6 ,7};
    const vector<int> move = {3, 2, 4, 1, 0, 6, 5};

    mutate(nums, move);

    cout << "Mutated array : " << endl;
    for (int i=0; i<nums.size(); i++)
        cout << nums[i];
    cout << endl;
}
