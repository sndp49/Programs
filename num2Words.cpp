#include <iostream>
#include <vector>
#include <string>
using namespace std;

const vector<string> ones  = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
const vector<string> tens  = {"", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
const vector<string> mul10 = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
const vector<string> pow10 = {"", " Thousand ", " Million ", " Billion "};


string toWord(unsigned int num)
{
    string res;

    string str = to_string(num);

    for (int i=0; i<str.length(); i++)
    {
        if (str.length()-i == 3)
            res += ones[str[i]-'0'] + " Hundred ";                              // res += ones[str[i]-'0'] + " Hundred" + (str[i+1] != '0' ? " " : (str[i+2] != '0' ? " " : ""));
        else if (str.length()-i == 2)
        {
            if (str[i] > '1')
                res += mul10[str[i]-'0'] + " ";                                 // res += mul10[str[i]-'0'] + (str[i+1] == '0' ? "" : " ");
            else if (str[i] == '0')
                continue;
            else    // 11 - 19
            {
                res += tens[(str[i]-'0') + (str[i+1]-'0')];
                break;
            }
        }
        else
            res += ones[str[i]-'0'];
    }

    if (res.back() == ' ')
        res.pop_back();

    return res;
}


string numberToWords(unsigned int num)
{
    string res;

    if (num == 0)
        return string("Zero");
    else if (num < 10)
        return ones[num];

    for (int i = 0; num > 0; num/=1000, i++)
    {
        if (num%1000 != 0)
            res = toWord(num%1000) + pow10[i] + res;
    }

    if (res.back() == ' ')
        res.pop_back();

    return res;
}


int main(int argc, char *argv[])
{
    unsigned int num = 123456789;

    if (argc==2)
        num = atoi(argv[1]);

    printf("\n Number %d in word-format => %s\n", num, numberToWords(num).c_str());

    return 0;
}
