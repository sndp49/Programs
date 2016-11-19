#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int heapSize;

void print(int a[])
{
    for (int i = 0; i < heapSize; i++)
        cout << a[i] << "-";

    cout << "\n" << endl;
}

int parent(int i)
{
    if(i<=2)        // 0, 1 or 2
        return 0;

    return floor((i-1)/2);
}

int left(int i) { return (2 * i) + 1; }

int right(int i) { return (2 * i) + 2; }

void heapify(int a[], int i)
{
    int l = left(i), great;
    int r = right(i);
    if ((l < heapSize) && (a[l] > a[i]))
        great = l;
    else
        great = i;

    if ((r < heapSize) && (a[r] > a[great]))
        great = r;

    if (great != i)
    {
        swap(a[i], a[great]);
        heapify(a, great);
    }
}

void BuildMaxHeap(int a[])
{
    for (int i = (heapSize - 1) / 2; i >= 0; i--)
        heapify(a, i);
}

void HeapSort(int a[])
{
    BuildMaxHeap(a);
    for (int i = heapSize; i > 0; i--)
    {
        swap(a[0], a[heapSize-1]);
        heapSize--;
        heapify(a, 0);
    }
}

int main()
{
    int arr[] =  {2, 9, 3, 6, 1, 4, 5, 7, 0, 8};
	heapSize = sizeof(arr)/sizeof(int); int tmp = heapSize;
	cout << "\nInitial given array => "; print(arr);
    HeapSort(arr);

    heapSize = tmp; cout << "\nFinal sorted array => "; print(arr);
    reverse(arr, arr+heapSize);
    cout << "\nDescending sorted array => "; print(arr);

    return 0;
}

/* Working C++ style
void printAll(const vector<int> nums)
{
    cout << endl;
    for (int num : nums)
        cout << num << ", ";
    cout << endl;
}

int HeapSize;

void heapify(vector<int>& nums, int i)
{
    int l = (2*i)+1, r = (2*i)+2, g;

    if ( l<HeapSize && nums[l] > nums[i] )
        g = l;
    else
        g = i;

    if ( r<HeapSize && nums[r] > nums[g] )
        g = r;

    if (i!=g)
    {
        swap(nums[i], nums[g]);
        heapify(nums, g);
    }
}

void buildMaxHeap(vector<int>& nums)
{
    for (int i=(nums.size()-1)/2; i>=0; i--)
        heapify(nums, i);
}

void heapSort(vector<int>& nums)
{
    buildMaxHeap(nums);

    for (int i=HeapSize-1; i>=0; i--)
    {
        swap(nums[0], nums[i]);
        --HeapSize;
        heapify(nums, 0);
    }
}

int main()
{
    char *str = new char[256];
    memset(str, '\0', 256);
    fgets(str, 256, stdin);

    vector<int> nums;

    char *pch = NULL;
    pch = strtok(str, ", ");

    while (pch != NULL)
    {
        nums.push_back(atoi(pch));
        pch = strtok(NULL, ", ");
    }

    HeapSize = nums.size();
    heapSort(nums); printAll(nums);

    return 0;
}
*/
