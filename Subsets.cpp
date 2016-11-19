#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
using namespace std;

/* Given a number n . Generate all combination subsets formed between 1...n

    Ex: n = 3

        Empty set
        3,
        2,
        2, 3,
        1,
        1, 3,
        1, 2,
        1, 2, 3,                                                                                                                                                                                                                        */


void print(vector<int>& v)      // print all elements in the vector
{
    for (int i=v.size()-1; i>=0; i--)
        cout << v[i] << ", ";
}

void generateSubsets(int n)
{
    vector<int> nums(n);
    iota(nums.begin(), nums.end(), 1);

    double total = pow(2, n);   // total no. of subsets

    for (double i=0; i<total; i++)
    {
        vector<int> res;

        for (int j=i, idx = n-1; j; j>>=1, idx--)
        {
            if (j&1)
                res.push_back(nums[idx]);
        }

        print(res); cout << endl;
    }
}

int main(int argc, char* argv[])
{
    int n = 3;

    if (argc == 2)
        n = atoi(argv[1]);

    generateSubsets(n);

    return 0;
}
