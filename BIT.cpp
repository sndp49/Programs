#include <iostream>
#include <vector>
using namespace std;

/*  Fenwick Tree or Binary Indexed Tree         Used for pefix sum
    https://www.youtube.com/watch?v=CWDQJGaN1gY
Complexity  Space: O(N)     Sum & Update: O(logN)       Initial building the Fenwick tree O(NlogN)                                                          */


class BITree
{
    vector<int> BIT;

    int getParent(int index)    { return index - (index & -index); }    // 1. 2's complement 2. AND it with original index 3. Subtract from original index  (flip the right most set bit)
    int getNext(int index)      { return index + (index & -index); }    // 1. 2's complement 2. AND it with original index 3. add from original index

public:

    BITree(const vector<int>&);

    int getSum(int index);
    void updateTree(int index, int val);
    void update(int index, int val);
};

BITree::BITree(const vector<int>& nums)
{
    BIT.assign(nums.size()+1, 0);

    for (int i=0; i<nums.size(); i++)
        updateTree(i, nums[i]);
}

int BITree::getSum(int index)       // Prefix sum of the array from 0...index
{
    index = index+1;

    int sum = 0;

    while (index > 0)
    {
        sum += BIT[index];
        index = getParent(index);
    }

    return sum;
}

void BITree::updateTree(int index, int d)
{
    index = index+1;

    while (index < BIT.size())
    {
        BIT[index] += d;
        index       = getNext(index);
    }
}

void BITree::update(int index, int val)
{
    int sum_index   = getSum(index);                        // current sum at index
    int sum_index_1 = (index>0) ? getSum(index-1) : 0;      // current sum at index-1

    int val_indx = sum_index - sum_index_1;                 // nums[index]
    int diff = val - val_indx;                              // difference

    updateTree(index, diff);
}


int main(int argc, char *argv[])
{
    const vector<int> nums = {3,2,-1,6,5,4,-3,3,7,2,3};

    BITree *ft = new BITree(nums);

    int index = 6;
    if (argc == 2)
        index = atoi(argv[1]);

    printf("\nPrefix sum from 0 to %d is %d\n", index, ft->getSum(index));

    ft->update(6, 3);
    printf("\nUpdated Prefix sum from 0 to %d is %d\n", index, ft->getSum(index));

    return 0;
}
