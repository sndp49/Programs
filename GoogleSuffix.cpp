#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string reverse(const string& s)
{
    string str;

    for (int i=s.length()-1; i>=0; i--)
        str += s[i];

    return str;
}

int LS(const string& s)
{
    int maxLen = 0;
    string str = reverse(s);

    vector<int> prefix(str.length(), 0);

    int l = 0, r = 1;

    while (r < str.length())
    {
        if (str[l] == str[r])
        {
            prefix[r] = l+1;
            l++;
            maxLen = max(maxLen, prefix[r++]);
        }
        else
        {
            if (l==0)
                prefix[r++] = 0;
            else
                l = prefix[l-1];
        }
    }

    return maxLen;
}


int main()
{
    //const string s = "banana";
    const string s = "anaanaana";

    cout << "\nLongest suffix in the given string: " << LS(s) << endl;

    return 0;
}
