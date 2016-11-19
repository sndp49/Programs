#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* https://www.youtube.com/watch?v=V-sEwsca1ak  Manacher's Algorithm    http://articles.leetcode.com/longest-palindromic-substring-part-ii

    Things to take as the next center:
    ✘  1. Palindrome totaly contained under the current palindrome
    ✔  2. If the current palindrome expands till the right edge of the string , then break while
    ✔  3. Palindrome expands till the right edge of the current palindrome, and its mirror expands till the prefix/left-edge. Then, this is the next center.
    ✘  4. Palindrome expands till the right edge of the current palindrome, and its mirror expands beyond the prefix/left-edge.
    ✔  5. If all the above cases fail, then pick the next letter outside the current palindrome right edge                                     */

// Transform S into T.  For example, S = "abba", T = "^#a#b#b#a#$". ^ and $ signs are sentinels appended to each end to avoid bounds checking

string preProcess(const string s)
{
    int n = s.length();
    if (n==0)   return "^$";
    string ret(2*n+3, '#');

    ret[0] = '^';
    for (int i=0, j=2; i<n; i++, j=j+2)
        ret[j] = s[i];
    ret.back() = '$';

    return ret;
}

string longestPalindrome(const string s)
{
    string T = preProcess(s);

    vector<int> L(T.length());              // Length

    int C = 0, R = 0;                       // center, right-edge/suffix

    for (int i=1; i<T.length(); i++)
    {
        int i_mirror = 2*C-i;               // equals to i' = C-(i-C)

        L[i] = (R > i) ? min(R-i, L[i_mirror]) : 0;

        while (T[i+1+L[i]] == T[i-1-L[i]])  // Attempt to expand palindrome at i
            L[i]++;

        if (i+L[i] > R)                     // If palindrome centered at i expands past R, adjust center based on expanded palindrome
        {
            C = i;
            R = i+L[i];
        }
    }

    int maxLen = 0, centerIndex = 0;

    for (int i=1; i<T.length()-1; i++)
    {
        if (L[i] > maxLen)
        {
            maxLen = L[i];
            centerIndex = i;
        }
    }

    return s.substr((centerIndex - (maxLen + 1))/2, maxLen);
}

int main()
{
    const string s = "abaxabaxabybaxabyb";  // odd length palindrome
    //const string s = "abba";              // even length palindrome

    printf("\nLongest Palindrome for the given string %s is %s\n", s.c_str(), longestPalindrome(s).c_str());
    return 0;
}
