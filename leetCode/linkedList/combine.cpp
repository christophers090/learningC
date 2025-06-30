/**
Merge Two Sorted Linked Lists
You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists into one sorted linked list and return the head of the new sorted linked list.

The new list should be made up of nodes from list1 and list2.

Example 1:

Input: list1 = [1,2,4], list2 = [1,3,5]

Output: [1,1,2,3,4,5]
Example 2:

Input: list1 = [], list2 = [1,2]

Output: [1,2]
Example 3:

Input: list1 = [], list2 = []

Output: []
Constraints:

0 <= The length of the each list <= 100.
-100 <= Node.val <= 100

 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(!list1) return list2;
        if(!list2) return list1;

        ListNode* newHead = compare(&list1, &list2);

        ListNode* curr = newHead;
        while(list1 && list2){
            curr->next = compare(&list1, &list2);
            curr = curr->next;
        }

        if(!list1){
            curr->next = list2;
        } else {
            curr->next = list1;
        }

        return newHead;
    }

    ListNode* compare(ListNode** list1, ListNode** list2) {
        if((*list1)->val > (*list2)->val){
            ListNode* result = *list2;
            *list2 = (*list2)->next;
            return result;
        } else {
            ListNode* result = *list1;
            *list1 = (*list1)->next;
            return result;
        }
    }
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1) {
            return list2;
        }
        if (!list2) {
            return list1;
        }
        if (list1->val <= list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};