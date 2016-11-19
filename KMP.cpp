#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* Try with example:
    string =>   abxabxabc
    pattern =>  abxabc                                                                                          */


bool strstr(const string& T, const string& P)
{
    vector<int> prefix(P.length(), 0);

    int l = 0, r = 1;

    while (r < P.length())
    {
        if (P[l] == P[r])
        {
            prefix[r] = l+1;
            l++;
            r++;
        }
        else // (P[l] != P[r])
        {
            if (l == 0)
                prefix[r++] = 0;
            else
                l = prefix[l-1];
        }
    }

    int i = 0, j = 0;

    while (i < T.length() && j < P.length())
    {
        if (T[i] == P[j])
        {
            i++;
            j++;
        }
        else
        {
            if (j==0)
                i++;
            else
                j = prefix[j-1];
        }
    }

    return (j==P.length());
}

int main()
{
    const string T("abcxabcdabxabcdabcdabcy");
    const string P("abcdabcy");
    //const string P("aacecaaa");

    if (strstr(T, P))
        cout << "Match found" << endl;
    else
        cout << "No match" << endl;

    return 0;
}
