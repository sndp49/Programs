#include <iostream>
#include <vector>
using namespace std;

// Pb: 15.15    Pg. 122

void printVector(const vector<int>& v)
{
    for (int i=0; i<v.size(); i++)
    {
        if (i<10)
            cout << i << ", ";
        else
            printf("%c, ", 'A' + (i-10));
    }

    cout << endl;

    for (int x : v)
        cout << x << ", ";
    cout << endl;
}

int getCombinations(const vector<int>& scores, const int k)
{
    vector<int> dp(k+1, 0);
    dp[0] = 1;

    for (int score : scores)
    {
        for (int i = 1; i<=k; i++)
        {
            if (i>=score)
                dp[i] += dp[i-score];
        }
    }

    printVector(dp);
    return dp.back();
}

int getPermutations(const vector<int>& scores, const int k)
{
    vector<int> dp(k+1, 0);
    dp[0] = 1;

    for (int i = 1; i<=k; i++)
    {
        for (int score : scores)
        {
            if (i>=score)
                dp[i] += dp[i-score];
        }
    }

    printVector(dp);
    return dp.back();
}

int main()
{
    const vector<int> scores = {2,3,7};
    const int k = 12;

    int ret = getCombinations(scores, k);
    cout << "Total no. of combinations => " << ret << endl;

    cout << endl;

    ret = getPermutations(scores, k);
    cout << "Total no. of permutations => " << ret << endl;

    return 0;
}
