#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*  Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.


Soln: http://www.geeksforgeeks.org/dynamic-programming-set-17-palindrome-partitioning/                                                                      */


int mincut(string str)
{
    int i, j, k, n = str.length();

    vector<vector<bool>> P(n, vector<bool>(n, false));                      //true if substring str[i..j] is palindrome, else false
    vector<vector<int>> dp(n, vector<int>(n, numeric_limits<int>::max()));  // dp[i][j] = Minimum number of cuts needed for palindrome partitioning of substring str[i..j] . Note that dp[i][j] is 0 if P[i][j] is true

    // Every substring of length 1 is a palindrome
    for (i=0; i<n; i++)
    {
        dp[i][i] = 0;
        P[i][i]  = true;
    }

    for (int len = 2; len <= n; len++)
    {
        for (i=0; i<n-len+1; i++)
        {
            j = i+len-1;

            if (str[i] == str[j] && (len<=3 || P[i+1][j-1]))
            {
                P[i][j]  = true;
                dp[i][j] = 0;
            }
            else
            {
                for (k=i; k<j; k++)
                    dp[i][j] = min(dp[i][j], 1+dp[i][k]+dp[k+1][j]);
            }
        }
    }

    return dp[0][n-1];
}

int main()
{
    string str ("ababbbabbababa");

    cout << "Min cuts needed for Palindrome Partitioning is " << mincut(str) << endl;

    return 0;
}

/* More optimization

// Dynamic Programming Solution for Palindrome Partitioning Problem
#include <stdio.h>
#include <string.h>
#include <limits.h>

// A utility function to get minimum of two integers
int min (int a, int b) { return (a < b)? a : b; }

// Returns the minimum number of cuts needed to partition a string such that every part is a palindrome
int minPalPartion(char *str)
{
    // Get the length of the string
    int n = strlen(str);

    /* Create two arrays to build the solution in bottom up manner
       C[i] = Minimum number of cuts needed for palindrome partitioning of substring str[0..i]
       P[i][j] = true if substring str[i..j] is palindrome, else false
       Note that C[i] is 0 if P[0][i] is true

    int C[n];
    bool P[n][n];

    int i, j, k, L; // different looping variables

    // Every substring of length 1 is a palindrome
    for (i=0; i<n; i++)
    {
        P[i][i] = true;
    }

    // L is substring length. Build the solution in bottom up manner by considering all substrings of length starting from 2 to n. //
    for (L=2; L<=n; L++)
    {
        // For substring of length L, set different possible starting indexes
        for (i=0; i<n-L+1; i++)
        {
            j = i+L-1; // Set ending index

            // If L is 2, then we just need to compare two characters. Else
            // need to check two corner characters and value of P[i+1][j-1]
            if (L == 2)
                P[i][j] = (str[i] == str[j]);
            else
                P[i][j] = (str[i] == str[j]) && P[i+1][j-1];
        }
    }

    for (i=0; i<n; i++)
    {
        if (P[0][i] == true)
            C[i] = 0;
        else
        {
            C[i] = INT_MAX;
            for(j=0;j<i;j++)
            {
                if(P[j+1][i] == true && 1+C[j]<C[i])
                    C[i]=1+C[j];
            }
        }
    }

    // Return the min cut value for complete string. i.e., str[0..n-1]
    return C[n-1];
}

*/
