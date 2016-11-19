#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
using namespace std;

/* Question: http://www.geeksforgeeks.org/dynamic-programming-set-8-matrix-chain-multiplication/

    https://codemeforever.wordpress.com/2014/11/09/matrix-chain-multiplication/

    http://d1gjlxt8vb0knt.cloudfront.net//wp-content/uploads/stressen_formula_new_new.png

    Complexity:  O(n^3)                                                                                                                                                         */

int MatrixChainOrder(const vector<int>& dims)
{
    int n = dims.size()-1;  // no. of matrices

    vector<vector<int>> cost(n+1, vector<int>(n+1, numeric_limits<int>::max()));
    //  cost[i][j] = minimum number of scalar multiplications needed to computer matrix A[i]A[i+1]...A[j] = A[i..j]
    //  cost is 0 when multiplying one matrix

    for (int i=1; i<=n; i++)
        cost[i][i] = 0;

    for (int len = 2; len<=n; len++)
    {
        for (int i=1; i<=n-len+1; i++)  // i points to the 'n' (col size) of the first matrix
        {
            int j = i+len-1;            // j points to the 'n' (col size) of the last matrix

            for (int k=i; k<j; k++)
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k+1][j] + dims[i-1]*dims[k]*dims[j]);    // A[m*n] * B[n*p] => m*n*p
        }
    }

    return cost[1][n];
}

int main()
{
    //const vector<int> dims = {40, 20, 30, 10, 30};  // matrix dimensions

    const vector<int> dims = {2, 3, 6, 4, 5};  // matrix dimensions
    //cout << "Minimum number of multiplications: " << MatrixChainOrder(dims) << endl;

    cout << endl;   MatrixChainOrder(dims);
    return 0;
}


/*


// Regular matrix multiplication

void printMat(int **C, int m, int n)
{
    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
            cout << C[i][j] << ", ";
        cout << endl;
    }
}

int** matMul(const int A[][4], const int B[][6], const int m, const int n, const int p)
{
    int **C = new int*[m];
    for (int i=0; i<m; i++)
        C[i] = new int[p];

    for (int i=0; i<m; i++)
    {
        for (int k=0; k<p; k++)
        {
            C[i][k] = 0;
            for (int j=0; j<n; j++)
                C[i][k] += A[i][j] * B[j][k];
        }
    }

    return C;
}


int main()
{
    int m = 5, n = 4, p = 6;

    const int A[][4] = {{7,3,2,5},
                        {8,1,4,6},
                        {2,5,8,4},
                        {7,1,1,9},
                        {1,2,3,4}};

    const int B[][6] = {{3,5,7,2,2,1},
                        {4,6,8,9,4,2},
                        {1,3,4,5,9,3},
                        {2,5,5,6,8,1}};

    int **C = matMul(A, B, m, n, p);

    printMat(C, m, p);

    for (int i=0; i<m; i++)
        delete[] C[i];
    delete C;
    C = NULL;

    return 0;
}

*/
