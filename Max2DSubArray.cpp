#include <iostream>
#include <vector>
using namespace std;

/*
 1  2 -1 -4 -20
-8 -3  4  2  1
 3  8 10  1  3
-4 -1  1  7 -6

Complexity: O(n^2 * m)

http://www.geeksforgeeks.org/dynamic-programming-set-27-max-sum-rectangle-in-a-2d-matrix/       */


void printSubArray(const vector<vector<int> > &mat, int, int, int, int);

int kadane(int rowSum[], const int m, int &s, int &e)
{
    int cur_sum = rowSum[0], max_sum = rowSum[0], cur_s = 0;

    for (int i=1; i<m; i++)
    {
        if (rowSum[i] > cur_sum+rowSum[i])
        {
            cur_sum = rowSum[i];
            cur_s   = i;
        }
        else
            cur_sum += rowSum[i];

        if (cur_sum>max_sum)
        {
            s = cur_s;
            e = i;
            max_sum = cur_sum;
        }
    }

    return max_sum;
}

int maxSubArray(const vector<vector<int> > &mat, const int m, const int n)
{
    int i, maxSum = numeric_limits<int>::min(), tr, br, fc, lc;    // top-row  bottom-row front-col last-col

    int lCol, rCol, cur_sum, s, e;

    int rowSum[n];

    for (lCol=0; lCol<n; lCol++)
    {
        memset(rowSum, 0, sizeof(rowSum));
        for (rCol=lCol; rCol<n; rCol++)
        {
            for (i=0; i<m; i++)
                rowSum[i] += mat[i][rCol];

            cur_sum =  kadane(rowSum, m, s, e);

            if (cur_sum > maxSum)
            {
                maxSum = cur_sum;
                tr = s;
                br = e;
                fc = lCol;
                lc = rCol;
            }
        }
    }

    printSubArray(mat, tr, br, fc, lc);

    return maxSum;
}

int main()
{
    const vector<vector<int> > mat = {  { 1, 2,-1,-4,-20},
                                        {-8,-3, 4, 2, 1},
                                        { 3, 8,10, 1, 3},
                                        {-4,-1, 1, 7,-6}  };

    int maxSum = maxSubArray(mat, mat.size(), mat[0].size());

    cout << "\nMaximum rectangle sum => " << maxSum << endl;
    return 0;
}

void printSubArray(const vector<vector<int> > &mat, int tr, int br, int fc, int lc)
{
    cout << "\nMax rectangle in the matrix..." << endl;

    for (int i=tr; i<=br; i++)
    {
        cout << endl;
        for (int j=fc; j<=lc; j++)
            cout << mat[i][j] << ", ";
    }
    cout << endl;
}
