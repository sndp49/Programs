#include <iostream>
using namespace std;

// http://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/

enum color { red, black };

class node_t
{
public:
    int val;
    node_t *left, *right;
    node_t *parent;
    color c;

    node_t(int v, node_t *p, color colour = color::red)
    {
        c = colour;
        left = right = NULL;
        parent = p;
    }
};

node_t* insert(node_t* root, int x, node_t *p)
{
    if (!root)
    {
        if (!p)
            return new node_t(x, NULL, black);
        else
        {
            if (p->c == black)
                return new node_t(x, p);

            if (p->c == red)
            {
                node_t* gp = p->parent;

                if (gp->right && gp->right->c == color::red)
                {
                    while (gp != NULL)
                    {
                        gp->left->c = gp->right->c = color::black;
                        gp->c = red;

                        if (gp->parent && gp->parent)
                            gp = gp->parent->parent;
                        else
                            gp = NULL;
                    }
                }
                else
            }
            else
            {

            }
        }


    }



    if (x->val < root->val)
        root->left = (root->left, x);
    else
        root->right = (root->right, x);

    return root;
}

int main()
{
    node_t *root = NULL;

    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, -10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, -15);
    root = insert(root, 25);
    root = insert(root, 17);
    root = insert(root, 21);
    root = insert(root, 24);
    root = insert(root, 28);
    root = insert(root, 34);
    root = insert(root, 32);
    root = insert(root, 26);
    root = insert(root, 35);
    root = insert(root, 19);

    printRBT(root);
}
