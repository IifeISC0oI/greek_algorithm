struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    struct ListNode head = {0};
    struct ListNode *pre = &head;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            pre->next = list1;
            list1 = list1->next;
        } else {
            pre->next = list2;
            list2 = list2->next;
        }
        pre = pre->next;
    }

    pre->next = (list1 != NULL) ? list1 : list2;
    return head.next;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    if (listsSize == 0) {
        return NULL;
    }
    if (listsSize == 1) {
        return lists[0];
    }
    if (listsSize == 2) {
        return mergeTwoLists(lists[0], lists[1]);
    }
    int list1Size = listsSize >> 1;
    struct ListNode *list1 = mergeKLists(lists, list1Size);
    struct ListNode *list2 = mergeKLists(&lists[list1Size], listsSize - list1Size);

    return mergeTwoLists(list1, list2);
}
