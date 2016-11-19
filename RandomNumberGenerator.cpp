#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

// Get random number with equal probability between [a, b]          Pb: 20.4    Pg: 156

int getRand(const int a, const int b)
{
    int l = b - a + 1, res;

    do
    {
        res = 0;

        for (int i=0; (1 << i) < l; i++)
            res = (res << 1) | (rand() % 2);
    } while (res >= l);

    return res + a;
}

/* // Easy to understand but slower
int getRand(const int a, const int b)
{
    int l = b - a + 1;

    int i = ceil(log2(l)), res = 0;

    while (res >= l)
    {
        for (int j=0; j<i; j++)
        {
            int add = (1 << j) * (rand()%2);

            if (res + add < l)
                res += add;
            else
                break;
        }
    }

    return a + res;
}   */

int main(int argc, char* argv[])
{
    int a = 3, b = 13;      //

    if (argc == 3)
    {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }

    srand(time(NULL));

    cout << "Type . to stop" << endl;

    do {
        printf("\nRandom number between bound [%d, %d] is %d\t", a, b, getRand(a, b));
    } while (getchar() != '.');

    return 0;
}
