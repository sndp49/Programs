#include <iostream>
#include <vector>
using namespace std;

// http://www.geeksforgeeks.org/interval-tree/

class node_t
{
public:
    int l, u;
    int maxi;

    node_t *left, *right;

    node_t(int low, int high) : l(low), u(high), maxi(high)
    {   left = right = NULL;    }
};

node_t* insert(node_t* i, node_t* root)
{
    if (!root)
        return i;

    if (i->l < root->l)
        root->left = insert(i, root->left);
    else
        root->right = insert(i, root->right);

    root->maxi = max(root->maxi, i->maxi);

    return root;
}


bool doOverlap(const node_t* i1, const node_t* i2)
{   return (   i1->l <= i2->u
            && i2->l <= i1->u);  }

node_t* overlapSearch(node_t *root, const node_t* i)
{
    if (!root)
        return NULL;

    if (doOverlap(root, i))
        return root;

    if (root->left && root->left->maxi >= i->l)
        return overlapSearch(root->left, i);

    return overlapSearch(root->right, i);
}

int main()
{
    vector<vector<int>> ranges = {{15, 20}, {10, 30}, {17, 19}, {5, 20}, {12, 15}, {30, 40}};

    node_t* root = NULL;

    for (vector<int> range : ranges)
        root = insert(new node_t(range[0], range[1]), root);

    node_t x(6, 7);

    cout << "Searching for interval [" << x.l << "," << x.u << "]" << endl;
    node_t *res = overlapSearch(root, &x);

    if (!res)
        cout << "No Overlapping Interval" << endl;
    else
        cout << "Overlaps with [" << res->l << ", " << res->u << "]" << endl;

    return 0;
}
