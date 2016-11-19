#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

/*  Given word = "word", return the following list:
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]

Soln:   For every character in the word, u can either abbreviate or move on
        https://leetcode.com/discuss/75505/meet-in-google-interview-solution-with-concise-explanation                                                                                       */

void doDFS(int pos, string word, vector<string>& res)
{
    if (pos == word.length())
        return;

    string str = word.substr(0, pos-1) + to_string((word[pos-1]-'0') + 1) + word.substr(pos+1);
    res.push_back(str);

    if (word[pos-1] == '9')
        doDFS(pos+1, str, res);
    else
        doDFS(pos, str, res);

    for (int i=pos+1; i<word.length(); i++)
    {
        char ch = word[i];
        word[i] = '1';
        res.push_back(word);
        doDFS(i+1, word, res);
        word[i] = ch;
    }
}

vector<string> generateAbbreviations(string word)
{
    vector<string> res;

    res.push_back(word);

    for (int i=0; i<word.length(); i++)
    {
        char ch = word[i];
        word[i] = '1';
        res.push_back(word);
        doDFS(i+1, word, res);
        word[i] = ch;
    }

    return res;
}


int main()
{
    //string word("interaction");
    string word("word");

    vector<string> res;

    res = generateAbbreviations(word);

    /*for (string s : res)
        cout << s << ", ";
    cout << endl;*/

    return 0;
}
