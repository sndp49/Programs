#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// https://www.youtube.com/watch?v=RORuwHiblPc

void TextJustification (const vector<string>& words, const int L)
{
    int i, j, n = words.size(), int_max = pow(L,4);

    vector<vector<int>> espace(n, vector<int>(n, L+1));     // empty spaces
    vector<vector<int>> cost(n, vector<int>(n, int_max));   // cost of empty spaces

    for (i=0; i<n; i++)
        espace[i][i] = L-words[i].length();     // always positive because a single word is always less than L

    for (i=0; i<espace.size(); i++)
    {
        for (j=i+1; j<espace[i].size(); j++)
        {
            int sp = espace[i][j-1] - (1 + words[j].length());

            if (sp >= 0)
                espace[i][j] = sp;
            else
                break;
        }
    }

    for (i=0; i<espace.size(); i++)
    {
        for (j=i; j<espace[i].size(); j++)
        {
            if (espace[i][j]<L)
                cost[i][j] = pow(espace[i][j], 2);
            else
                break;
        }
    }

    vector<int> c(n);                     // Minimum cost
    vector<int> out(n);                   // final result

    for (i=n-1; i>=0; i--)               // i represents the lines
    {
        c[i] = cost[i][n-1];
        out[i] = n;

        for (j=n-2; j>=i; j--)           // j represents ending words. [i][j] means words starting at index i and ending at index j (including word at j)
        {
            if (cost[i][j] != int_max && c[i] > cost[i][j]+c[j+1])
            {
                c[i] = cost[i][j]+c[j+1];
                out[i] = j+1;
            }
        }
    }

    // Printing
    for (i=0; i<out.size(); i = out[i])
    {
        for (j=i; j<out[i]; j++)
            cout << words[j] << " ";
        cout << endl;
    }
}

int main()
{
    vector<string> words = {"aaa", "bb", "cc", "ddddd"};
    const int L = 6;

    //vector<string> words = {"Tushar","likes","to","write","code","at", "free", "time"};   const int L = 12;

    //const vector<string> words = {"I", "have", "inserted", "a", "large", "number", "of", "new", "examples", "from", "the", "papers", "for", "the", "mathematical", "tripos", "during", "the", "last", "twenty", "years,", "which", "should", "be", "useful", "to", "cambridge", "students."};
    //const int L = 36;

    TextJustification(words, L);
    return 0;
}
