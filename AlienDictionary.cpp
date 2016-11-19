#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_map<char, unordered_set<char>> G;

bool toposort(char ch, vector<bool>& visited, vector<bool>& path, string& res)
{
    if (path[ch-'a'])
        return false;

    path[ch-'a'] = true;

    for (char c :  G[ch])
    {
        if (!visited[c-'a'] && !toposort(c, visited, path, res))
            return false;
    }

    visited[ch-'a'] = true;
    res += ch;
    return true;
}

string alienOrder(vector<string>& words)
{
    string res;

    if (words.empty())          return res;
    else if (words.size() == 1) return words[0];

    int i, j;

    unordered_set<char> alpha;  // set containing all alphabets in words

    for (i=0; i<words.size()-1; i++)
    {
        for (j=0; j < min(words[i].length(), words[i+1].length()) && words[i][j] == words[i+1][j]; j++)
            alpha.insert(words[i][j]);

        if ( j < min(words[i].length(), words[i+1].length()) )
        {
            if (G.find(words[i+1][j]) != G.end() && G[words[i+1][j]].find(words[i][j]) != G[words[i+1][j]].end())     // deadlock (a->b && b->a case)
                return string();

            G[words[i][j]].insert(words[i+1][j]);
            alpha.insert(words[i][j]);
            alpha.insert(words[i+1][j]);
        }

        for (int k = j+1; k < words[i].length(); k++)
            alpha.insert(words[i][k]);
    }

    for (int k = j+1; k < words[i].length(); k++)
        alpha.insert(words[i][k]);

    vector<bool> visited(26, false);
    vector<bool> path(26, false);

    for (char ch : alpha)
    {
        if (!visited[ch-'a'])
        {
            if (!toposort(ch, visited, path, res))
                return string();    // found cycle
        }
    }

    if (res.empty())
        return res;

    reverse(res.begin(), res.end());
    return res;
}
