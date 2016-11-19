#include <iostream>
#include <vector>
#include <string>
using namespace std;


int wordsTyping(vector<string>& sentence, int rows, int cols) {

    int n = sentence.size();

    vector<int> len(n, 1);    // no. of words written in the row starting with word[i];

    for (int i=0; i<n; i++)
    {
        if (sentence[i].length() > cols)    return 0;   // Ex: {"hello"} rows = 10000 cols = 1

        int empty_space = cols - sentence[i].length();

        for (int j=i+1; empty_space >= 1 + sentence[j%n].length(); j++)
        {
            empty_space -= (1 + sentence[j%n].length());
            len[i]++;
        }
    }

    int cnt = 0;    // total no. of words written
    int start = 0;  // starting word index in the current row

    for (int i=0; i<rows; i++)
    {
        cnt   += len[start];
        start  = (start + len[start]) % n;
    }

    return cnt / sentence.size();
}


int main()
{
    vector<string> sentence = {"hello"};
    int rows = 10000, cols = 1;

    //int rows = 3, cols = 6;

    //vector<string> sentence = {"a", "bcd", "e"};
    //int rows = 3, cols = 6;

    int ret = wordsTyping(sentence, rows, cols);

    cout << "No. of times the given sentence can be fitted on the screen: " << ret << endl;

    return 0;
}
