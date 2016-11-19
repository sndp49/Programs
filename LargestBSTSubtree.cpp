#include <iostream>
#include <cstdlib>
using namespace std;

class node
{
public:
    int size, lower, upper;
    node(int sz, int mini, int maxi) : size(sz), lower(mini), upper(maxi) {}
};

node* checkBST(TreeNode* cur)
{
    if (!cur)
        return new node(0, numeric_limits<int>::max(), numeric_limits<int>::min());

    node* l = checkBST(cur->left);
    node* r = checkBST(cur->right);

    if (l->size < 0 || r->size < 0 || l->upper > cur->val || cur->val > r->lower)
        return new node(-1 * max(abs(l->size), abs(r->size)), 0, 0);
    else
        return new node(l->size + r->size + 1, min(l->lower, cur->val), max(cur->val, r->upper));
}

int largestBSTSubtree(TreeNode* root)
{
    if (!root)  return 0;

    if (!root->left && !root->right)    return 1;

    node* res = checkBST(root);

    return (res->size > 0) ? res->size : -res->size;
}
