#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// http://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/

void rotate(vector<vector<int>>& mat)
{
    int n = mat.size();

    int cycles = floor(n/2);

    for (int i=0; i<cycles; i++)
    {
        for (int j=i; j<n-i-1; j++)
        {
            int tmp = mat[i][j];

            swap(tmp, mat[j][n-1-i]);
            swap(tmp, mat[n-1-i][n-1-j]);
            swap(tmp, mat[n-1-j][i]);
            swap(tmp, mat[i][j]);
        }
    }

}

int main()
{
    // Square matrix
    vector<vector<int>> mat = { { 1,  2,  3,  4},
                                { 5,  6,  7,  8},
                                { 9, 10, 11, 12},
                                {13, 14, 15, 16} };

    /*vector<vector<int>> mat = { { 1, 2, 3},
                                { 4, 5, 6},
                                { 7, 8, 9} };    */

    rotate(mat);

    for (int i=0; i<mat.size(); i++)
    {
        for (int j=0; j<mat[0].size(); j++)
            cout << mat[i][j] << ",  ";
        cout << endl;
    }

    return 0;
}
