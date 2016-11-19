#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
#include <stack>
using namespace std;

/* Topological Sort can only be performed on Direct-Acyclic-Graphs (DAG). Bascially directed graphs without cycles
 https://www.youtube.com/watch?v=ddTC4Zovtbc    */

#define V 8

class GraphVertex
{
public:
    int id;
    vector<GraphVertex*> edges;

    GraphVertex(int i) : id(i) {}
};

unordered_set<int> set;
stack<int> s;

void doTopo(GraphVertex *v )                // DFS and push vertex into stack after visitng its edges
{
    set.insert(v->id);

    for (GraphVertex* edge : v->edges)
    {
        if (set.find(edge->id) == set.end())
            doTopo(edge);
    }

    s.push(v->id);
}

void TopologicalSort(vector<GraphVertex*> GV)   // Traverse through all unvisited vertices of the graph
{
    for (GraphVertex *v : GV)
    {
        if (set.find(v->id) == set.end())
            doTopo(v);
    }
}

int main()
{
    vector<GraphVertex*> GV;

    for (int i=0; i<V; i++)
        GV.emplace_back(new GraphVertex(i));

    GV[0]->edges.push_back(GV[2]);
    GV[1]->edges.push_back(GV[2]);
    GV[1]->edges.push_back(GV[3]);
    GV[1]->edges.push_back(GV[6]);
    GV[3]->edges.push_back(GV[5]);
    GV[5]->edges.push_back(GV[6]);
    GV[4]->edges.push_back(GV[6]);
    GV[4]->edges.push_back(GV[7]);

    TopologicalSort(GV);

    // printing Stack
    while (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }

    return 0;
}
