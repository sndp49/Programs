#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

/*  https://www.youtube.com/watch?v=KNXfSOx4eEE

    Heuristic value (H):  Distance from a node to the target node
    Movement cost   (G):  Movement cost from node to another node

    http://www.geeksforgeeks.org/a-search-algorithm/                                                                                  */

int m, n;

class node
{
public:
    int h, g, f;    // Heuristic, Movement cost, H+G

    node(int _h, int _g) : h(_h), g(_g) {}
};

unordered_map<int, node*> G;

unordered_map<int, int> parent;

const int shift[] = {-1, 0, 0, 1, 1, 0, 0, -1};
const int diags[] = {-1, 1, 1, 1, 1, -1, -1, -1};

auto cmp = [](const int& lhs, const int& rhs) -> bool { return (G[lhs]->f > G[rhs]->f); };  // minHeap
priority_queue<int, vector<int>, decltype(cmp)> Q(cmp);

bool pushNeighbors(const int cur, const int end, unordered_set<int>& openList, unordered_set<int>& closedList)
{
    int i = cur/n, j = cur%n;

    for (int k=0; k<8; k+=2)
    {
        int x = i + shift[k], y = j + shift[k+1], idx = x*n+y;

        if (x>=0 && x<m && y>=0 && y<n && closedList.find(idx) == closedList.end() && G[idx]->g > 10+G[cur]->g)
        {
            G[idx]->g = G[cur]->g + 10;               // successor.g = cur.g + distance between successor and cur
            G[idx]->f = G[idx]->h + G[idx]->g;

            parent[idx] = cur;

            Q.push(idx);
            openList.insert(idx);

            if (idx == end)
                return true;
        }

        x = i + diags[k]; y = j + diags[k+1]; idx = x*n+y;

        if (x>=0 && x<m && y>=0 && y<n && closedList.find(idx) == closedList.end() && G[idx]->g > 14+G[cur]->g)
        {
            G[idx]->g = G[cur]->g + 14;               // successor.g = cur.g + distance between successor and cur
            G[idx]->f = G[idx]->h + G[idx]->g;

            parent[idx] = cur;

            Q.push(idx);
            openList.insert(idx);

            if (idx == end)
                return true;
        }
    }

    return false;
}

void printPath(const int s, const int e);

void shortestPath(int s, int e, unordered_set<int>& obstacles)
{
    unordered_set<int> openList, closedList;

    for (int obstacle : obstacles)
        closedList.insert(obstacle);

    closedList.insert(s);
    G[s]->g = 0;
    G[s]->f = G[s]->h + G[s]->g;

    int i = s/n, j = s%n;

    if (pushNeighbors(s, e, openList, closedList))
    {
        printPath(s, e);
        return;
    }

    while (!Q.empty())
    {
        int cur = Q.top();
        Q.pop();

        openList.erase(cur);
        closedList.insert(cur);

        if (pushNeighbors(cur, e, openList, closedList))
        {
            printPath(s, e);
            return;
        }
    }

    printf("Error: No path found between %d and %d\n", s, e);
}

int main()
{
    m = 7; n = 6;

    int start = 13, end = 34;

    unordered_set<int> obstacles = {15, 25, 27, 33};

    int e_i = end/n, e_j = end%n;

    for (int i=0; i<m; i++)
    {
        for (int j=0; j<n; j++)
        {
            int idx = i*n+j;

            if (obstacles.find(idx) != obstacles.end()) continue;

            G[idx] = new node(abs(e_i - i) + abs(e_j - j), numeric_limits<int>::max());     // calculating H using Manhattan Distance
        }
    }

    shortestPath(start, end, obstacles);

    return 0;
}

void printPath(const int s, const int e)
{
    printf("\nShortest Path between %d and %d is: ", s, e);

    for (int cur = e; cur != s; cur = parent[cur])
        cout << cur << " <- ";
    cout << s << endl;
}
