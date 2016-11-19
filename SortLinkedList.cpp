#include <iostream>
using namespace std;

ListNode* sortList(ListNode* head)
{
    if (!head || !head->next)   return head;
    else if (!head->next->next)
    {
        if (head->val > head->next->val)
            swap (head->val, head->next->val);

        return head;
    }

    ListNode *slow, *fast;
    slow = fast = head;

    while (!fast->next && !fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    fast = slow->next;
    slow->next = NULL;
    return merge(sortList(head), sortList(fast));
}

ListNode* merge (ListNode* l, ListNode* r)
{
    if (!l && !r)   return NULL;
    else if (!l)    return r;
    else if (!r)    return l;

    ListNode* head = new ListNode(numeric_limits<int>::min());
    ListNode* cur  = head;

    while (l!=NULL && r!=NULL)
    {
        if (l->val <= r->val)
        {
            cur->next = l;
            l = l->next;
        }
        else
        {
            cur->next = r;
            r = r->next;
        }

        cur = cur->next;
    }

    cur->next = (l!=NULL) ? l : r;

    return head->next;
}
