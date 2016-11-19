#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

// Dutch algo does three-way partitioning with smaller elements to the left, larger elements to the right of the pivot and same elements remaining intact with the pivot element
void qsortDutch(vector<int>& a, int pivot)
{
    int sm = 0, cur = 0, lg = a.size()-1;

    while (cur <= lg)
    {
        if (a[cur] < pivot)
            swap(a[sm++], a[cur++]);
        else if(a[cur] == pivot)
            cur++;
        else
            swap(a[cur], a[lg--]);
    }
}

void qsort(vector<int>& a, int left, int right)
{
    int l = left, r = right;
    int pivot = a[l+(r-l)/2];

    while (l<=r)                        // partition
    {
        while(a[l] < pivot)
            l++;

        while(a[r] > pivot)
            r--;

        if (l<=r)
            swap(a[l++], a[r--]);
    }

    if (left < r)
        qsort(a, left, r);

    if (l < right)
        qsort(a, l, right);
}

void print(int a[], int n)
{
    for (int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main()
{
    int arr[] = { 5, 4, 1, 2, 5, 3, 2, 2, 5, 4 };
    //int arr[] = {1,2,3,2,2,1,3};
    //int arr[] = { 3, 4, 2, 1, 3, 1, 4, 5, 1, 2, 3, 5 };
    int len = sizeof(arr)/sizeof(int);

    vector<int> array (arr, arr+len);

    srand(time(NULL));
    int pivot = array[rand()%len];

    qsortDutch(array, pivot);   cout << "\nDutch sort where pivot element is " << pivot << endl;  print(array.data(), len);

    //qsort(array, 0, array.size()-1);    cout << "\nQuickSort" << endl; print(array.data(), array.size());

    return 0;
}
