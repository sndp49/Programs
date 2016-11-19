#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool findWords(int pos, int i, int j, vector<vector<bool>>& visited, const vector<vector<char>>& boogle, const string& word)
{
    if (pos+1 == word.length())
        return true;

    visited[i][j] = true;

    const int shift[] = {-1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1,-1,-1};

    for (int k=0; k<16; k+=2)
    {
        int x = i+shift[k], y = j+shift[k+1];

        if (x>=0 && x<boogle.size() && y>=0 && y<boogle[x].size() && !visited[x][y] && word[pos+1] == boogle[x][y])
        {
            if (findWords(pos+1, x, y, visited, boogle, word))
                return true;
        }
    }

    return false;
}

int main()
{
    vector<vector<char>> boogle = { {'G','I','Z'},
                                    {'U','E','K'},
                                    {'Q','S','E'} };

    const vector<string> dict = {"GEEKS", "FOR", "QUIZ", "GO"};

    int m = boogle.size(), n = boogle[0].size();

    cout << "\nMatching words are => ";

    for (string word : dict)
    {
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (int i=0; i<m; i++)
        {
            for (int j=0; j<n; j++)
            {
                if (boogle[i][j] == word[0] && findWords(0, i, j, visited, boogle, word))
                {
                    cout << word << ", ";
                    break;
                }
            }
        }
    }

    cout << endl;
    return 0;
}
