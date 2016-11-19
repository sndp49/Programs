#include <iostream>
#include <queue>
#include <stack>
using namespace std;

typedef struct node_t
{
    int data;
    node_t *left;
    node_t *right;
} node;

void insert(node **root, int val)
{
    node *newNode = new node;
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;

    if (*root == NULL)
    {
        cout << "\nCreating Tree" << endl;
        *root = newNode;
    }
    else
    {
        node *cur = *root;
        node *prev = NULL;

        while(cur)
        {
            prev = cur;

            if(val <= cur->data)
                cur = cur->left;
            else
                cur = cur->right;
        }

        if (val <= prev->data)
            prev->left = newNode;
        else
            prev->right = newNode;
    }
}

void del(node **root, int val)
{
    if(*root == NULL)
    {
        cout << "Error: Trying to delete an empty tree" << endl;
        return;
    }

    node *cur = *root;
    node *parent = NULL;
    while(cur)
    {
        if (val < cur->data)
        {
            parent = cur;
            cur = cur->left;
        }
        else if (val > cur->data)
        {
            parent = cur;
            cur = cur->right;
        }
        else    // val == cur->data
            break;
    }

    if (cur == NULL)
    {
        printf("\nElement with value %d not found in the tree\n", val);
        return;
    }

    node *psuc, *suc;                   // Pointers to find inorder successor and parent of the inorder successor

    if (!cur->left && !cur->right)
        suc = NULL;
    else if (!cur->left)                // One child or no childs
        suc = cur->right;
    else if (!cur->right)               // One child or no childs
        suc = cur->left;
    else                                // Two childs exist
    {                                   // Find inorder successor : Go to the right subtree of cur and find the min key value within the right subtree (Basically find the left most child of the right subtree)
        psuc = cur;
        suc = cur->right;

        while(suc->left)
        {
            psuc = suc;
            suc = suc->left;
        }

        if (psuc == cur)                // If it didnt enter the above while loop, then inorder succesor of cur is the right child (The Right subtree doesnt have a left branch)
        {
            psuc->right = NULL;         // Deleting the link between the parent of the inorder successor
            suc->left = cur->left;
        }
        else
        {
            psuc->left = suc->right;
            suc->left = cur->left;
            suc->right = cur->right;
        }
    }

    if (parent == NULL)
        *root = suc;
    else if(parent->left == cur)
        parent->left = suc;
    else if(parent->right == cur)
        parent->right = suc;

    delete cur;
}

void printTree(node *root)      // Level Order Traversal
{
    queue<node*> Q;

    if (!root)
    {
        cout << "\nError: Trying to printout an empty tree" << endl;
        return;
    }

    Q.push(root);
    node* n = NULL;

    while(!Q.empty())
    {
        n = Q.front();
        Q.pop();

        cout << n->data << ", ";

        if(n->left)
            Q.push(n->left);

        if (n->right)
            Q.push(n->right);
    }
}

void delAll(node **root)
{
    if (!*root)
        return;

    node *cur = *root;

    if (cur->left)
        delAll(&cur->left);

    if (cur->right)
        delAll(&cur->right);

    delete cur;
    cur = NULL;
}

void createTree(node **root)
{
    if(*root)
    {
        cout << "\nError: Tree exists add branch/child instead" << endl;
        return;
    }

    insert(root, 10); insert(root, 6); insert(root, 20); insert(root, 4); insert(root, 8); insert(root, 5); insert(root, 7); insert(root, 9); insert(root, 15); insert(root, 25); insert(root, 13); insert(root, 21); insert(root, 18); insert(root, 26);
}

bool isBST(node *cur, int prev = numeric_limits<int>::min())
{
    if (!cur)   return true;

    if (cur->left)
    {
        if (!isBST(cur->left, prev))
            return false;
    }

    if (prev > cur->data)
        return false;

    prev = cur->data;

    if (cur->right)
        return isBST(cur->right, prev);

    return true;
}

//https://discuss.leetcode.com/topic/21217/java-o-n-and-o-1-extra-space
bool verifyPreorder(vector<int>& preorder)
{
    stack<int> s;

    int lower = numeric_limits<int>::min();

    for (int p : preorder)
    {
        if (lower > p)
            return false;

        while (!s.empty() && p > s.top())
        {
            lower = s.top();
            s.pop();
        }

        s.push(p);
    }

    return true;
}

void preorder(node *root, vector<int> &pre)
{
    pre.push_back(root->data);

    if (root->left)
        preorder(root->left, pre);

    if (root->right)
        preorder(root->right, pre);
}

void inorder(node *root, vector<int> &in)
{
    if (root->left)
        inorder(root->left, in);

    in.push_back(root->data);

    if (root->right)
        inorder(root->right, in);
}

void postorder(node *root, vector<int> &pos)
{
    if (root->left)
        postorder(root->left, pos);

    if (root->right)
        postorder(root->right, pos);

    pos.push_back(root->data);
}
