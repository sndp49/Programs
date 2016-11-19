#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

// http://www.geeksforgeeks.org/find-water-in-a-glass/

float findWater(int r, int c, const float water)
{
    if (c > r)
    {
        cout << "Error: Invalid input" << endl;
        assert(0);
    }

    vector<float> glass( r*(r+1)/2 , 0 );  // total no. of glass including all the glasses in the current row

    int index = 0;  // glass index

    glass[0] = water;

    for (int i=1; i<=r; i++)
    {
        for (int j=1; j<=i; j++, index++)   // since the no. of glasses in a given row = row
        {
            float x = glass[index];

            glass[index] = (x >= 1.0f) ? 1.0f : x;

            if (x > 1.0f)                   // Distribute the remaining amount to the down two glasses
            {
                glass[index + r]     += (x-1.0f)/2.0f;
                glass[index + r + 1] += (x-1.0f)/2.0f;
            }
        }
    }

    int idx = ((r-1)*r/2) + (c - 1);    // the index of the cth glass on thr rth row is (r-1)*r/2 + (c - 1)


    cout << "\n" << endl; int k = 0;
    for (int i=1; i<=r; i++)
    {
        for (int j=1; j<=i; j++)
            cout << glass[k++] << ", ";

        cout << endl;
    }
    cout << endl;


    return glass[idx];
}


int main()
{
    int r = 3, c = 1;

    float water = 5;      // total water poured

    printf("\n Water is present in glass at row %d and column %d is %f \n", r, c, findWater(r, c, water));

    return 0;
}
