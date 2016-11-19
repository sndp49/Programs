/*

You are given a graph with no cycles, each node representing different cities and there are stadiums for baseball games in all cities.

Each node contains a value representing the population of the city, and a list of neighbors. (feel free to extend data structure)

Every time there is a baseball game at a city, everyone from all the different cities will go to the city with the baseball game.

Return the maximum traffic between a city and its neighbours when there is a game at that city, for all cities. (Does not have to be sorted)

The total run-time after returning everything should be O(n).

Examples:


Input:
        1   2
        \  /
         5
       /  \
      4   3

Output:
1 14
2 13
3 12
4 11
5 4


Input:
                 38
                 /
                8
               /
              7
             /
       1    2
        \  / \
         5   15
       /  \
      4    3

Output:
1 82
2 53
3 80
4 79
5 70
7 46
15 68
8 38
38 45

https://www.careercup.com/question?id=5695046734053376                                                                                                          */


class node
{
    int id;                 // node id
    int population;         // population

    unordered_set<int> edges;    // neighbors of current node
};

unordered_map<int, node*> G;

void preprocess(node *root)
{
    int n     = G.size();   // total number of nodes
    int t_pop = 0;          // total population of all cities

    vector<int> leaves;

    for (auto it = G.begin(); it != G.end(); it++)
    {
        if (it->second->edges.size() == 1)
            leaves.push_back(it->first);

        t_pop += it->second->population;
    }

    int i = 0;

    vector<int> sum(n, 0);  // amount of traffic going to that city on game day
    vector<int> max(n, 0);

    while (i < leaves.size())
    {
        int leaf = leaves[i++];

        cout << leaf << " : " << max( max[leaf], t_pop - G[leaf]->population - sum[leaf] ) << endl; //  t_pop - G[leaf]->population - sum[leaf] = traffic comming from 2 -> 5 in the second example

        if (G[nei]->edges.size() == 0)  continue;

        int nei  = *(G[leaf]->edges.begin());  // since it's a leaf node, it'll have only one neighbor

        G[nei]->edges.erase(leaf);

        if (G[nei]->edges.size() == 1)
            leaves.push_back(nei);

        sum[nei] += G[leaf]->population + sum[leaf];
        max[nei]  = max(max[nei], G[leaf]->population + sum[leaf]);
    }
}
