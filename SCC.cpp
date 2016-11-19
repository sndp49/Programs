/*  Kosaraju's algo to find strongly connected components in Graph (SCC)
    https://www.youtube.com/watch?v=RpgcYiky7uw       */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void printMat(const vector<vector<int>>& mat);

void transpose(vector<vector<int>>& TransposeGraph, const vector<vector<int>>& G);

void assemble(int i, vector<bool>& visited, const vector<vector<int>>& TG, vector<int>& path)
{
    if (visited[i])
        return;

    visited[i] = true;
    path.push_back(i);

    for (int j=0; j<TG[i].size(); j++)
    {
        if (TG[i][j] && !visited[j])
            assemble(j, visited, TG, path);
    }
}

void doDFS(int i, vector<bool>& visited, stack<int>& st, const vector<vector<int>>& G)
{
    if (visited[i])
        return;

    visited[i] = true;

    for (int j=0; j<G[i].size(); j++)
    {
        if (G[i][j] && !visited[j])
            doDFS(j, visited, st, G);
    }

    st.push(i);
}

void SCC(const vector<vector<int>>& G)
{
    vector<vector<int>> res;

    vector<bool> visited(G.size(), false);
    stack<int> st;

    for (int i=0; i<G.size(); i++)
    {
        if (!visited[i])
            doDFS(i, visited, st, G);
    }

    vector<vector<int>> TransposeG(G.size(), vector<int>(G[0].size(), 0));
    transpose(TransposeG, G);

    visited.clear();
    visited.assign(TransposeG.size(), false);
    vector<int> path;   // strongly connected components

    while (!st.empty())
    {
        if (!visited[st.top()])
        {
            assemble(st.top(), visited, TransposeG, path);   // assemble connected component together
            res.push_back(path);
            path.clear();
        }
        else
            st.pop();
    }

    cout << "Strongly connected components in the Graph are:" << endl; printMat(res);
}

int main()
{
    int m, n;
    m = n = 11;

    vector<vector<int>> G(m, vector<int>(n, 0));

    // Create directed connections
    for (int i=0; i<m; i++)
        G[i][i] = 1;
    G[0][1] = G[1][2] = G[1][3] = G[2][0] = G[3][4] = G[4][5] = G[5][3] = G[6][5] = G[6][7] = G[7][8] = G[8][9] = G[9][6] = G[9][10] = 1;

    SCC(G);

    return 0;
}

void printMat(const vector<vector<int>>& mat)
{
    for (int i=0; i<mat.size(); i++)
    {
        for (int j=0; j<mat[i].size(); j++)
            cout << mat[i][j] << ", ";
        cout << endl;
    }
}

void transpose(vector<vector<int>>& TransposeGraph, const vector<vector<int>>& G)
{
    int m = G.size(), n = G[0].size();

    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
            TransposeGraph[j][i] = G[i][j];
    }
}
