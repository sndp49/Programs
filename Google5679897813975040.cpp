#include <iostream>
#include <unordered_map>
using namespace std;

//  https://www.careercup.com/question?id=5679897813975040

unordered_map<char, pair<char, int>> edges;   // vertex1, vertex2, weight

unordered_map<char, int> nodes_cnt;           // no. of nodes in the subtree rooted using char (including char)


int doDFS(char cur, char parent, const int n, int& sum)
{
    for (pair<char, int> edge : edges[cur])
    {
        if (edge.first == parent)   continue;

        int subtree_cnt = doDFS(edge.first, cur, n, sum);

        nodes_cnt[cur] += subtree_cnt;

        sum += subtree_cnt * (n - subtree_cnt) * edges[cur][edge.first];
    }

    return nodes_cnt[cur] + 1;
}

int SumAllPairWeight(int n)
{
    int sum = 0;

    traverseTree('A', '#', n, sum);

    return sum;
}

int main()
{
    edges['A']['B'] = edges['B']['A'] = 1;
    edges['B']['C'] = edges['C']['B'] = 2;
    edges['E']['A'] = edges['A']['E'] = 4;
    edges['A']['F'] = edges['F']['A'] = 5;
    edges['B']['D'] = edges['D']['B'] = 3;

    int n = 6;  // total no. of vertices

    for (int i=0; i<n; i++)
        nodes_cnt['A' + i] = 0;

    cout << "Sum of all edge pair weight: " << SumAllPairWeight(n) << endl;

    return 0;
}
