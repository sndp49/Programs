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

void printSpiral(const vector<vector<int>> A)
{
    int m = A.size(), n = A[0].size();

    int tr = 0;     // Top-row
    int br = m-1;   // Bottom-row
    int fc = 0;     // first-column
    int lc = n-1;   // last-column

    int dir = 0;    // direction    0 => moving right   1 => moving down    2 => moving left    3 => moving up

    int i;  cout << endl;

    while(tr<=br && fc<=lc)
    {
        if (dir == 0)
        {
            for (i=fc; i<=lc; i++)
                cout << A[tr][i] << " ,";

            tr++;
            dir = 1;
        }
        else if(dir == 1)
        {
            for (i=tr; i<=br; i++)
                cout << A[i][lc] << " ,";

            lc--;
            dir = 2;
        }
        else if(dir == 2)
        {
            for (i=lc; i>=fc; i--)
                cout << A[br][i] << " ,";

            br--;
            dir = 3;
        }
        else                                        // (dir == 3)
        {
            for (i=br; i>=tr; i--)
                cout << A[i][fc] << " ,";

            fc++;
            dir = 0;
        }
    }

    cout << "\n" <<endl;
}

int main()
{
    /*const vector<vector<int>> mat = {{2,4,6,8},
                                       {5,9,12,16},
                                       {2,11,5,9},
                                       {3,2,1,8} };                                                     */
                                       
    const vector<vector<int>> mat = {{1,2,3,4,5},
                                     {6,7,8,9,10},
                                     {11,12,13,14,15},
                                     {16,17,18,19,20}};

    printSpiral(mat);

    return 0;
}
