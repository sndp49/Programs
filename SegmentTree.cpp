#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//https://www.youtube.com/watch?v=ZBHKZF5w4YU

void updateElem(vector<int>& st, int s, int e, const int idx, const int diff, int pos)
{
    if (idx < s || idx > e)     // If the input index lies outside the range of this segment
        return;

    st[pos] += diff;            // If the input index is in range of this node, then update the value of the node and its children

    if (s!=e)
    {
        int m = s+(e-s)/2;
        updateElem(st, s, m, idx, diff, 2*pos+1);
        updateElem(st, m+1, e, idx, diff, 2*pos+2);
    }
}

int getSum(const vector<int>& st, const int qs, const int qe, int s, int e, int pos)
{
    if (s>=qs && e<=qe)     // complete overlap
        return st[pos];
    else if (e<qs || qe<s)  // no overlap
        return 0;

    // Partial Overlap
    int m = s+(e-s)/2;
    return getSum(st, qs, qe, s, m, 2*pos+1) + getSum(st, qs, qe, m+1, e, 2*pos+2);
}

int divide(const vector<int>& arr, int l, int r, vector<int>& st, int pos)
{
    if (l == r)   // base case
    {
        st[pos] = arr[l];
        return st[pos];
    }

    int m = l+(r-l)/2;

    st[pos] = divide(arr, l, m, st, 2*pos+1) + divide(arr, m+1, r, st, 2*pos+2);
    return st[pos];
}

int main(int argc, char* argv[])
{
    vector<int> arr = {1, 3, 5, 7, 9, 11};

    // construct Tree
    int h = ceil(log2(arr.size())); // not height
    int maxSize = 2*pow(2,h) - 1;

    vector<int> st(maxSize, 0);     // Segment Tree

    divide(arr, 0, arr.size()-1, st, 0);

    int qs = 1, qe = 4;

    if (argc == 3)  {
        qs = atoi(argv[1]);
        qe = atoi(argv[2]);
    }

    printf("\nSum of elements between the range [%d, %d] is %d\n", qs, qe, getSum(st, qs, qe, 0, arr.size()-1, 0) );

    int idx = 2, x = 10, diff = x-arr[idx];    // update arr[idx] = x
    arr[idx] = x;
    updateElem(st, 0, arr.size()-1, idx, diff, 0);  printf("\nElement value @ idx %d was updated from %d to %d\n", idx, arr[idx]-diff, arr[idx]);

    printf("\nUpdated Sum of elements between the range [%d, %d] is %d\n", qs, qe, getSum(st, qs, qe, 0, arr.size()-1, 0) );
}
