#include <iostream>
#include <vector>
using namespace std;

// https://www.youtube.com/watch?v=siKFOI8PNKM

// You go about printing the outermost row and columns
/*
TR ->   1 2 3 4 5 6
        7 8 9 1 2 3
        4 5 6 7 8 1
BR ->   3 2 3 4 6 7
        ^         ^
        FC        LC
*/

void printMat(const vector<int> res, int m, int n)
{
    for (int i=0; i<res.size(); i++)
        cout << res[i] << ", ";
    cout << endl;
}

vector<vector<int>> createMatrix(int m, int n)
{
    vector<vector<int>> mat(m, vector<int>(n, 0));

    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
            mat[i][j] = i*n+j;
    }

    return mat;
}

vector<int> printSpiral(const vector<vector<int>> A)
{
    int i, m = A.size(), n = A[0].size();

    int tr = 0;     // Top-row
    int br = m-1;   // Bottom-row
    int fc = 0;     // first-column
    int lc = n-1;   // last-column

    int dir = 0;    // direction    0 => moving right   1 => moving down    2 => moving left    3 => moving up

    vector<int> res;

    while(tr<=br && fc<=lc)
    {
        switch(dir)
        {
            case 0:
                for (i=fc; i<=lc; i++)
                    res.push_back(tr*n+i);

                tr++;
                dir = 1;
                break;
            case 1:
                for (i=tr; i<=br; i++)
                    res.push_back(i*n+lc);

                lc--;
                dir = 2;
                break;
            case 2:
                for (i=lc; i>=fc; i--)
                    res.push_back(br*n+i);

                br--;
                dir = 3;
                break;
            case 3:
                for (i=br; i>=tr; i--)
                    res.push_back(i*n+fc);

                fc++;
                dir = 0;
                break;
            default:
                break;
        }
    }

    return res;
}

int main()
{
    int m = 4, n = 5;

    vector<vector<int>> mat = createMatrix(m, n);

    vector<int> res = printSpiral(mat);

    printMat(res, m, n);

    return 0;
}
