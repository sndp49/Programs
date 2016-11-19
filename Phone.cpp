#include <iostream>
#include <array>
#include <string>
using namespace std;

// Complexity : O(4^N)  where N is the number of digits in the number

const string mnemonics[10] = { "0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ" };

void phoneMnemonicHelper(const string ph, string out, const int len, int pos)
{
    if (pos == len)
    {
        printf ("\n Phone number for %s is %s", ph.c_str(), out.c_str());
        return;
    }

    int no_of_chars_within  = ( ph[pos] == '7' || ph[pos] == '9') ? 4 : 3;

    for (int i=0; i<no_of_chars_within; i++)
    {
        out[pos] = mnemonics[ph[pos] - '0'][i];
        phoneMnemonicHelper(ph, out, len, pos+1);

        if(ph[pos] == '0' || ph[pos] == '1')
            return;
    }
}

int main()
{
    string ph("3003239");
    string out(ph.length(), '\0');

    phoneMnemonicHelper(ph, out, ph.length(), 0);
    return 0;
}
