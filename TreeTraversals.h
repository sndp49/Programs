/*
Full Binary tree is a binary tree in which every node other than the leaves has two children
Perfect Binary tree is a full binary tree in which all leaves are at the same depth
Complete Binary tree is binary tree in which every level, except possibly the last, is completly filled, and all nodes are as far left as possible

A Perfect binary tree of height h containes exactly 2^(h-1) + 1 nodes and 2^h leaves. This means that a perfect binary tree with l leaves has n = 2l - 1 nodes.
A Complete binary tree of n nodes has height of floor(log n).
A Complete binary tree of n leaves has exactly n-1 internal nodes.

Balanced binary tree is binary tree where the difference between the height of its left and right subtree is atmost one

Binary search tree is a binary tree where left child is less than equal and right child is greater than the parent.

Height of balanced tree with n nodes is no more than h(n) = 1.4405lg(n/2+3)-0.3277

The depth of a node is the number of edges from the node to the tree's root node. A root node will have a depth of 0.
The height of a node is the number of edges on the longest path from the node to a leaf. A leaf node will have a height of 0.           */


// Pre-Order Traversal
preorder(node)
    if node == null then return
    visit(node)
    preorder(node.left)
    preorder(node.right)

iterativePreorder(node)
    parentStack = empty stack
    while (not parentStack.isEmpty())
        node = parentStack.pop()
        visit(node)

        if (node.right ≠ null)
            parentStack.push(node.right)

        if (node.left ≠ null)
            parentStack.push(node.left)


// InOrder Traversal
inorder(node)
    if node == null then return
    inorder(node.left)
    visit(node)
    inorder(node.right)

iterativeInorder(node)
    parentStack = empty stack
    while (not parentStack.isEmpty() or node ≠ null)
        if (node ≠ null)
            parentStack.push(node)
            node = node.left
        else
            node = parentStack.pop()
            visit(node)
            node = node.right

/* Morris Traversal (Inorder without stack and recursion)

    cur => root

    if (cur->left)
        prev is the right-child of the rightmost node of cur->left.
        prev->right = cur
        cur = cur->left
    else
        print cur->data
        cur = cur->right

Note: Not thread safe
*/

void inorder(node *root)
{
    if(root == NULL)
    {
        cout << "\nError: Empty Tree" << endl;
        return;
    }

    node *cur = root;
    node *prev = NULL;

    while(cur)
    {
        if(cur->left)
        {
            prev = cur->left;
            while(prev->right && (prev->right != cur))      /* Find the inorder predecessor of current */
                prev = prev->right;

            if(prev->right == NULL)                         /* Make current as right child of its inorder predecessor */
            {
                prev->right = cur;
                cur = cur->left;
            }
            else                                            /* Revert the changes made in if part to restore the original tree i.e., fix the right child of predecssor */
            {
                prev->right = NULL;
                cout << cur->data <<", ";
                cur = cur->right;
            }
        }
        else   // cur->left == NULL
        {
            cout << cur->data <<", ";
            cur = cur->right;
        }
    }

}


// PostOrder Traversal
postorder(node)
    if node == null then return
    postorder(node.left)
    postorder(node.right)
    visit(node)

iterativePostorder(node)
    parentStack = empty stack
    lastnodevisited = null
    while (not parentStack.isEmpty() or node ≠ null)
        if (node ≠ null)
            parentStack.push(node)
            node = node.left
        else
            peeknode = parentStack.peek()
            if (peeknode.right ≠ null and lastnodevisited ≠ peeknode.right)
            /* if right child exists AND traversing node from left child, move right */
                node = peeknode.right
            else
                visit(peeknode)
                lastnodevisited = parentStack.pop()

//https://leetcode.com/problems/binary-tree-postorder-traversal/
vector<int> postorderTraversal(TreeNode* root)
{
    vector<int> res;

    if (!root)
        return res;

    if (!root->left && !root->right)
    {
        res.push_back(root->val);
        return res;
    }

    stack<TreeNode*> s;
    s.push(root);

    while (!s.empty())
    {
        TreeNode* cur = s.top();
        s.pop();
        res.push_back(cur->val);

        if (cur->left)
            s.push(cur->left);

        if (cur->right)
            s.push(cur->right);
    }

    reverse(res.begin(), res.end());

    return res;
}

// Breadth-First
levelorder(root)
    q = empty queue
    q.enqueue(root)
    while not q.empty do
        node := q.dequeue()
        visit(node)
        if node.left ≠ null then
            q.enqueue(node.left)
        if node.right ≠ null then
            q.enqueue(node.right)


binaryTreePaths(root, ret, to_string(root->val));

void binaryTreePaths(TreeNode* root, vector<string> &ret, string path)
{
    if (!root->left && !root->right)
        ret.push_back(path);

    if (root->left)
        binaryTreePaths(root->left, ret, path+"->"+to_string(root->left->val));

    if (root->right)
        binaryTreePaths(root->right, ret, path+"->"+to_string(root->right->val));
}
