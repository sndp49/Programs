#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


/*  Given integer k and a subset S of set {0, 1, 2, ..., 2^k - 1}
    Return the count of pairs (a, b) where a and b are from S and (a < b) and (a & b == a) & here is bit-wise and.
    Do it faster than O((2^k)^2), assume k <= 16      */

int getNumberofZeros(int x)
{
    int cnt = 0;

    while (!(x & 1))
    {
      x >>= 1;
      cnt++;
    }

    return cnt;
}

int getCount(int k)
{
    int n = pow(2, k) - 1;

    int cnt = n;  // 0 & any number = 0

    for (int i=2; i<n; i++)
    {
      int zeros = getNumberofZeros(i);
      cnt += pow(2, zeros) - 1;
    }

    return cnt;
}

int main(int argc, char* argv[])
{
    int k = 16;

    if (argc == 2)
        k = atoi(argv[1]);

    cout << "Count = " << getCount(k) << endl;
}
