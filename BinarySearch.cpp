#include <iostream>
using namespace std;

//http://www.geeksforgeeks.org/the-ubiquitous-binary-search-set-1/

int ceil (const int a[], int len, const int x)  // smallest integer greater than x
{
    if (x>a[len-1]) return -1;

    int l = -1, r = len-1, m;

    while (r-l > 1)
    {
        m = l+(r-l)/2;

        if (a[m] >= x)
            r = m;
        else
            l = m;
    }

    return a[r];
}

int floor(const int a[], int len, const int x)  // largest integer less than x
{
    if (x<a[0]) return -1;  // error

    int l = 0, r = len, m;

    while (r-l > 1)
    {
        m = l+(r-l)/2;

        if (a[m] <= x)
            l = m;
        else
            r = m;
    }

    return a[l];
}

bool BSearch(const int a[], int len, const int x)
{
    int l = 0, r = len-1, m;

    while (r-l > 1)
    {
        m = l+(r-l)/2;

        if (a[m] <= x)
            l = m;
        else
            r = m;
    }

    return (a[l] == x);
}

int Search_Rotated_Array (const int a[], int len, const int x)
{
    int l = 0, r = len-1, m;

    while (l<r)
    {
        m = l+(r-l)/2;

        if (a[m] == x)  return m;

        if (a[m] > a[r])
        {
            if (a[l] <= x && x < a[m])
                r = m-1;
            else
                l = m+1;
        }
        else if (a[m] < a[r])
        {
            if (a[m] < x && x <= a[r])
                l = m+1;
            else
                r = m-1;
        }
        else                        // if most of the elements are equal
            r--;
    }

    return (a[l] == x) ? l : -1;
}

int smallest_rotated_array (const int a[], int len)
{
    int l = 0, r = len-1, m;

    while (l<r)
    {
        m = l+(r-l)/2;

        if (a[m]<=a[r])
            r = m;
        else
            l = m+1;
    }

    return min(a[l], a[r]);
}

int main()
{
    int target[] = {4, 17, 25};

    const int a[] = { 1, 3, 4, 7, 9, 13, 18, 23 };

    for (int i=0; i<sizeof(target)/sizeof(target[0]); i++)
        cout << ( BSearch(a, sizeof(a)/sizeof(a[0]), target[i]) ? "Target found" : "Target not found") << endl;

    int x[] = {0, 7, 14, 29};

    for (int i=0; i<sizeof(x)/sizeof(x[0]); i++)    {
        printf("\nFloor value for %d is %d\n", x[i], floor(a, sizeof(a)/sizeof(a[0]), x[i]));
        printf("Ceil value for %d is %d\n",    x[i], ceil (a, sizeof(a)/sizeof(a[0]), x[i]));
    }

    const int ra[] = { 13, 18, 23, 1, 3, 4, 7, 9 };
    cout << (Search_Rotated_Array(ra, sizeof(ra)/sizeof(ra[0]), 7) ? "\nElement found" : "\nElement not found") << " in the rotated array" << endl;
    cout << "\nMinimum element in the rotated array is " << smallest_rotated_array(ra, sizeof(ra)/sizeof(ra[0])) << endl;
    return 0;
}
