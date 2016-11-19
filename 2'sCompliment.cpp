#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Algorithm for 2's compliment:
        Traverse the bits from right to left. Once you find the first 1, swap all bits to the left of the first 1 (excluding 1) */

void convert(int &x)
{
    if (x == 0) return;

    int count = 0;
    while (x)
    {
        if (x&1) break;

        x = x>>1;
        count++;
    }

    x = x ^ 0xfffffffe;

    for (;count; count--)
        x = x<<1;
}

int main(int argc, char* argv[])
{
    int x = 23;

    if (argc==2)
        x = atoi(argv[1]);

    printf("\n2's compliment of %d is ", x); convert(x); cout << x << endl;

    cout << endl; printf("%#02x", x); cout << endl;
    return 0;
}
