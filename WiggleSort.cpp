#include <iostream>
#include <vector>
using namespace std;

// Given an array A of n number. Rearrange A's elements to get a new array B having the property B[0]<=B[1]>=B[2]<=B[3]>=B[4]<=B[5]>=...

void printvec(vector<int> a)
{
	for (int i=0; i<a.size(); i++)
        	cout << a[i] << " ";
	cout << endl;
}

int main()
{
	int arr[] = {1,10,6,5,7,8,3,4,2,9};
	vector<int> a(arr, arr+(sizeof(arr)/sizeof(int)));

	printvec(a);

	for (int i=0; i<a.size()-1; i++)
	{
		if ( ( (i&1) && a[i]<a[i+1] ) || ( (!(i&1)) && a[i]>a[i+1] ) )
			swap(a[i], a[i+1]);
	}

	printvec(a);

	return 0;
}

// https://leetcode.com/problems/wiggle-sort-ii/	https://discuss.leetcode.com/topic/32929/o-n-o-1-after-median-virtual-indexing

#ifdef 0	// nums[0] < nums[1] > nums[2] < nums[3]....

void dutchsort(vector<int>& nums, int pivot)
{
    int sm = 0, cur = 0, lg = nums.size()-1;

    for (int i=0; i<nums.size(); i++)
    {
        if (nums[cur] < pivot)
            swap(nums[sm++], nums[cur++]);
        else if (nums[cur] > pivot)
            swap(nums[cur], nums[lg--]);
        else // (nums[cur] == pivot)
            cur++;
    }
}

void wiggleSort(vector<int>& nums) {
    int m = nums.size()/2, n = nums.size();

    nth_element(nums.begin(), nums.begin()+m, nums.end());  // got the middle element to be used as pivot for ducth algo. Partitions such that all the small and eq elements move to the left and larger elements move to the right

    dutchsort(nums, nums[m]);   // partitions such that all the elements less are to the left, equal elements are together and larger elements to the right

    vector<int> res(n, 0);

    int sm = (n%2) ? n/2 : (n/2)-1;
    int lg = n-1;

    for (int i=0; i<n; i++)
    {
        if (i%2)    // odd
            res[i] = nums[lg--];
        else        // even
            res[i] = nums[sm--];
    }

    nums = res;
}


// More efficient way with O(1) space

void wiggleSort(vector<int>& nums)
{
	int n = nums.size();

	// Find a median.
	int m = nums.size()/2, mid = nums[m];
	nth_element(nums.begin(), nums.begin()+m, nums.end());

	// Index-rewiring.
	#define A(i) nums[(2*i+1) % (n|1)]

	// 3-way-partition-to-wiggly in O(n) time with O(1) space.
	int sm = 0, cur = 0, lg = nums.size()-1;

	while (cur <= lg)
	{
		if (A[cur] > mid)
			swap(A[cur], A[lg--]);
		else if	(A[cur] < mid)
			swap(A[sm++], A[cur++]);
		else
			cur++;
	}

	for (int i=0; i<nums.size(); i++)
	    cout << nums[i] << ", ";
	cout << endl;
}

/*	Ex:	[1,5,1,1,6,4] [4,6,1,5,1,4]

		[1,3,2,2,3,1] [2,2,1,3,1,3]

		[1,1,2,1,2,2,1] [1,1,1,2,1,2,1]			*/
#endif
