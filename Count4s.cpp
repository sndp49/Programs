#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/* Count numbers from 1 to n that have 4 as a digit
http://www.geeksforgeeks.org/count-numbers-from-1-to-n-that-have-4-as-a-a-digit/        */

int countDigit(int n)
{
    if (n<4)    return 0;

    int i, j, p, msd, count = 0;

    i = log10(n);
    p = pow(10, i);
    msd = n/p;

    int *dp = new int[i+1];
    dp[0] = 0;
    dp[1] = 1;

    for (j=2; j<=i; j++)
        dp[j] = 9*dp[j-1]+pow(10, j-1);

    if (msd == 4)                                           //  If MSD is 4. For example if n = 428, then count of numbers is sum of following. 1) Count of numbers from 1 to 399   2) Count of numbers from 400 to 428 which is 29.
        count = msd*dp[i] + n%p + 1;
    else if (msd > 4)                                       // IF MSD > 4. For example if n is 728, then count of numbers is sum of following.  1) Count of numbers from 1 to 399 and count of numbers from 500 to 699, i.e., "a[2] * 6"    2) Count of numbers from 400 to 499, i.e. 100   3) Count of numbers from 700 to 728, recur for 28
        count = msd-1*dp[i] + p + countDigit(n%p);
    else                                                    // IF MSD < 4. For example if n is 328, then count of numbers is sum of following.  1) Count of numbers from 1 to 299 a 2) Count of numbers from 300 to 328, recur for 28
        count = msd*dp[i] + countDigit(n%p);

    return count;
}

int main(int argc, char* argv[])
{
    int n = 774;

    if (argc==2)
        n = atoi(argv[1]);

    printf("\n Number of 4's between 0 and %d is %d\n\n", n, countDigit(n));
    return 0;
}
