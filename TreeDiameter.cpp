#include <iostream>
#include <vector>
using namespace std;

// Pb: 15.4 Pg. 116  Elements of Programming

struct node
{
    vector<pair<node*, int>> edges;    // edge, distance between u & v
};

// Return (height, diameter) pair
pair<int, int> Helper(node* cur)
{
    int curD = numeric_limits<int>::min();  // max diamter till now with cur node as root

    vector<int> h(2, 0);    // store the max 2 heights

    for (auto it = cur->edges.begin(); it != cur->edges.end(); it++)
    {
        pair<int, int> h_d = Helper(it->first);

        if (h[0] <= h_d.first + it->second)
        {
            h[1] = h[0];
            h[0] = h_d.first + it->second;
        }
        else if (h[1] < h_d.first + it->second)
            h[1] = h_d.first + it->second;

        curD = max(curD, h_d.second);
    }

    curD = max(curD, h[0] + h[1]);

    return {h[0], curD};
}

int MaxDiameter(node* root)
{
    if (!root)  return 0;

    return Helper(root).second;
}




/* http://www.geeksforgeeks.org/diameter-of-a-binary-tree/
The diameter of a tree (sometimes called the width) is the number of nodes on the longest path between two leaves in the tree.          */

typedef struct node_t
{
    int val;
    node_t *left;
    node_t *right;
} node;

int MaxDiameter(node* root, int *h)     // RETURN DIAMETER
{
    int lh, rh, ld, rd;

    lh = rh = ld = rd = 0;

    if (!root)
    {
        *h = 0;
        return 0;
    }

    ld = MaxDiameter(root->left, &lh);
    rd = MaxDiameter(root->right, &rh);

    *h = max(lh, rh)+1;

    return max(lh+rh+1, max(ld,rd));
}
