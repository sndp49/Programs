/* https://discuss.leetcode.com/category/456/facebook

Find minimum number of people to reach to spread a message across all people in twitter

Considering that I would like to spread a promotion message across all people in twitter. Assuming the ideal case, if a person tweets a message, then every follower will re-tweet the message.
You need to find the minimum number of people to reach out (for example, who doesn't follow anyone etc) so that your promotion message is spread out across entire network in twitter.
Also, we need to consider loops like, if A follows B, B follows C, C follows D, D follows A (A -> B -> C -> D -> A) then reaching only one of them is sufficient to spread your message.

Input: A 2x2 matrix like below. In this case, a follows b, b follows c, c follows a.

    a b c
a  1 1 0
b  0 1 1
c  1 0 1
Output: List of people to be reached to spread out message across everyone in the network.

Soln: Do Toposort on the Graph. Pick the top element in the stack and do a DFS and pop all elements from the stack which have been visited during DFS.                                                                                                                                            */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void DFS(int i, vector<bool>& visited, const vector<vector<int>>& G)
{
    if (visited[i])
        return;

    visited[i] = true;

    for (int j=0; j<G[i].size(); j++)
    {
        if (G[i][j] && !visited[j])
            DFS(j, visited, G);
    }
}

void doTopo(int i, vector<bool>& visited, stack<int>& st, const vector<vector<int>>& G)
{
    if (visited[i])
        return;

    visited[i] = true;

    for (int j=0; j<G[i].size(); j++)
    {
        if (G[i][j] && !visited[j])
            doTopo(j, visited, st, G);
    }

    st.push(i);
}

int GetMinNum(const vector<vector<int>>& G)
{
    vector<int> res;

    vector<bool> visited(G.size(), false);
    stack<int> st;

    for (int i=0; i<G.size(); i++)
    {
        if (!visited[i])
            doTopo(i, visited, st, G);
    }

    visited.clear();
    visited.assign(G.size(), false);

    while (!st.empty())
    {
        if (!visited[st.top()])
        {
            res.push_back(st.top());        // push the initial stack elements
            DFS(st.top(), visited, G);
        }

        st.pop();   // Pop all elements which are already visited
    }

    for (int i : res)
        printf("%c, ", i+'A');
    cout << "should start spreading the promotion" << endl;;

    return res.size();
}

int main()
{
    int m, n;
    m = n = 11;

    vector<vector<int>> G(m, vector<int>(n, 0));

    /* Given:
        A follows B
        B follows C, B follows D
        C follows A
        D follows E
        E follows F
        F follows D
        G follows F, G follows H,
        H follows I,
        I follows J,
        J follows G, J follows K,

    Ex: Since A is following B. A will re-tweet tweet's from B                  */

    // Create directed connections
    for (int i=0; i<m; i++)
        G[i][i] = 1;
    G[1][0] = G[2][1] = G[3][1] = G[0][2] = G[4][3] = G[5][4] = G[3][5] = G[5][6] = G[7][6] = G[8][7] = G[9][8] = G[6][9] = G[10][9] = 1;

    int ans = GetMinNum(G);

    cout << "\nMinimum no. of people to spread the promotion message is " << ans << endl;
    return 0;
}
