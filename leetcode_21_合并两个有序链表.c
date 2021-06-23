struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    if (l1 == NULL) {
        return l2;
    }
    if (l2 == NULL) {
        return l1;
    }
    struct ListNode *ret = (l1->val < l2->val) ? l1 : l2;
    struct ListNode *l1Last = NULL;
    struct ListNode *l2Last = NULL;
    while (l1 != NULL && l2 != NULL) {
        if (l1->val < l2->val) {
            while (l1 != NULL && l1->val < l2->val) {
                l1Last = l1;
                l1 = l1->next;
            }
            l1Last->next = l2;
        } else {
            while (l2 != NULL && l1->val >= l2->val) {
                l2Last = l2;
                l2 = l2->next;
            }
            l2Last->next = l1;
        }
    }

    return ret;
}