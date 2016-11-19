#include <iostream>
#include <vector>
using namespace std;

// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// Complexity: O(n log log n)

int main(int argc, char *argv[])
{
    int i, j, n = 79;

    if (argc == 2)
        n = atoi(argv[1]);

    vector<bool> isPrime(n+1, true);

    for (i=2; i*i<n; i++)   // note: even though we r checking till sqrt(n), there are primes after sqrt(n). If they ask u to count primes, it differes slightly    https://leetcode.com/problems/count-primes/
    {
        if (!isPrime[i])    continue;

        for (j=i*i; j<=n; j+=i)
            isPrime[j] = false;
    }

    cout << "\nPrimes: ";
    for (i=2; i<=n; i++)
    {
        if (isPrime[i])
            cout << i << ", ";
    }
    cout << endl;

    return 0;
}
