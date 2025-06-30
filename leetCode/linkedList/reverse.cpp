/**
Reverse Linked List
Given the beginning of a singly linked list head, reverse the list, and return the new beginning of the list.

Example 1:

Input: head = [0,1,2,3]

Output: [3,2,1,0]
Example 2:

Input: head = []

Output: []
Constraints:

0 <= The length of the list <= 1000.
-1000 <= Node.val <= 1000

 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (!head || !head->next)
            return;
        ListNode *prev = nullptr;
        ListNode *cur = head;

        while (cur->next)
        {
            ListNode *temp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = temp;
        }

        cur->next = prev;
        return cur;
    }
};

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (!head)
        {
            return nullptr;
        }

        ListNode *newHead = head;
        if (head->next)
        {
            newHead = reverseList(head->next);
            head->next->next = head;
        }
        head->next = nullptr;

        return newHead;
    }
};