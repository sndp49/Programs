// https://leetcode.com/problems/closest-binary-search-tree-value-ii/

void inorder(TreeNode *cur, const bool reverse, stack<int>& s, const double t)
{
    if (!cur)   return;

    inorder((reverse) ? cur->right : cur->left, reverse, s, t);

    if ((!reverse && cur->val > t) || (reverse && cur->val <= t))
        return;

    s.push(cur->val);

    inorder((reverse) ? cur->left : cur->right, reverse, s, t);
}


vector<int> closestKValues(TreeNode* root, double target, int k)
{
    vector<int> res;

    stack<int> pred, succ;

    inorder(root, false, pred, target);
    inorder(root, true, succ, target);

    for (int i=0; i<k; i++)
    {
        if (pred.empty())
        {
            res.push_back(succ.top());
            succ.pop();
        }
        else if (succ.empty())
        {
            res.push_back(pred.top());
            pred.pop();
        }
        else
        {
            if (succ.top()-target < target-pred.top())
            {
                res.push_back(succ.top());
                succ.pop();
            }
            else
            {
                res.push_back(pred.top());
                pred.pop();
            }
        }
    }

    return res;
}
