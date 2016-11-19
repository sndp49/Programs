#include <iostream>
#include <vector>
using namespace std;

/*  Pg.88 Problem: 11.8     Given two sorted arrays, find the kth smallest element in Time complexity O(log K) & space complexity of O(1)

First refer Median2SortedArraysFaster.cpp . same procedure

        left_part          |        right_part
A[0], A[1], ..., A[x-1]    |  A[x], A[x+1], ..., A[m-1]
B[0], B[1], ..., B[k-x-1]  |  B[k-x], B[k-x+1], ..., B[n-1]

if (left_part < right_part) i.e. A[x-1] <= B[k-x] && B[k-x-1] <= A[x]
    done                                                                                                                                                                                                */


int find_kth_in_two_sorted_arrays(const vector<int> &A, const vector<int> &B, const int k)
{
    int m = A.size(), n = B.size();

    int l = max(0, k-B.size());     // lower bounds of elements we choose in A
    int u = min(A.size(), k);       // upper bounds of elements we choose in A

    while (l<u)
    {
        int x = l + (u-l)/2;

        int A_x_1   = (x <= 0)      ? numeric_limits<int>::min() : A[x-1];
        int A_x     = (x >= m)      ? numeric_limits<int>::max() : A[x];
        int B_k_x_1 = (k-x <= 0)    ? numeric_limits<int>::min() : B[k-x-1];
        int B_k_x   = (k-x >= n)    ? numeric_limits<int>::max() : B[k-x];

        if (B_k_x_1 > A_x)
            l = x+1;
        else if (A_x_1 > B_k_x)
            u = x-1;
        else                        // A[x-1] <= B[k-x] && B[k-x-1] <= A[x]
            return max(A_x_1, B_k_x_1);
    }

    // l == u
    int A_l_1   = (l <= 0)      ? numeric_limits<int>::min() : A[l-1];
    int B_k_l_1 = (k-l <= 0)    ? numeric_limits<int>::min() : B[k-l-1];
    return max(A_l_1, B_k_l_1);
}
