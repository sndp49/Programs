#include <iostream>
#include <cassert>
using namespace std;

/*  Find the median in two sorted array of different lengths
    http://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/

    Complexity: O(logM + LogN)                                                                                                                                                                              */


double M2(int a, int b)
{   return (a + b)/2.0; }

double M3(int a, int b, int c)
{   return a + b + c - max(a, max(b,c)) - min(a, min(b,c)); }

double M4(int a, int b, int c, int d)
{
    int Max = max(a, max(b, max(c,d)));
    int Min = min(a, min(b, min(c,d)));

    return (a+b+c+d-Max-Min)/2.0;
}

double findMedianUtil(int *A, int m, int *B, int n)
{
    assert(n!=0);   // if n==0 assert

    if (m==0)
    {
        if (n==1)  return B[0];

        if (n&1)   return B[n/2];
        else       return (B[n/2-1]+B[n/2])/2.0;
    }
    else if (m==1)
    {
        if (n==1)   return M2(A[0], B[0]);

        if (n&1)    return M2(B[n/2], M3(A[0], B[n/2-1], B[n/2+1]));
        else        return M3(A[0], B[n/2-1], B[n/2]);
    }
    else if (m==2)
    {
        if (n==2)   return M4(A[0], A[1], B[0], B[1]);

        if (n&1)    return M3(B[n/2], max(A[0], B[n/2-1]), min(A[1], B[n/2+1]));
        else        return M4(B[n/2], B[n/2-1], max(A[0], B[n/2-2]), min(A[1], B[n/2+1]));
    }

    int i = (m-1)/2, j = (n-1)/2;

    if (A[i]<=B[j])
        return findMedianUtil(A+i, m/2+1, B, n-i);
    else
        return findMedianUtil(A, m/2+1, B+i, n-i);
}

double Find_Median(int A[], int m, int B[], int n)
{
    if (m>n)
        return Find_Median_Util(B[], n, A[], m);
    else
        return Find_Median_Util(A[], m, B[], n);
}
