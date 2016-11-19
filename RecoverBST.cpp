/*  https://leetcode.com/problems/recover-binary-search-tree/
    https://discuss.leetcode.com/topic/29161/share-my-solutions-and-detailed-explanation-with-recursive-iterative-in-order-traversal-and-morris-traversal                   */

void inorder(TreeNode* cur, TreeNode* &prev, TreeNode* &first, TreeNode* &second)
{
    if (cur->left)
        inorder(cur->left, prev, first, second);

    if (prev->val >= cur->val)
    {
        if (!first)
            first = prev;

        second = cur;
    }

    prev = cur;

    if (cur->right)
        inorder(cur->right, prev, first, second);
}

void recoverTree(TreeNode* root)
{
    if (!root || (!root->left && !root->right))
        return;

    TreeNode* first = NULL;
    TreeNode* second = NULL;

    TreeNode* prev = new TreeNode(numeric_limits<int>::min());

    inorder(root, prev, first, second);

    swap(first->val, second->val);
}
