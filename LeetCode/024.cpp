// https://leetcode.com/problems/swap-nodes-in-pairs/

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:

    // See 025.cpp for a more general solution
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            return head;
        }

        ListNode* syntheticHead = new ListNode(-1);
        syntheticHead->next = head;
        ListNode* previousBlock = syntheticHead;
        ListNode* current = head;
        ListNode* next = head->next;
        ListNode* nextBlock;

        while (current != NULL) {
            if (next == NULL) {
                break;
            }
            nextBlock = next->next;
            previousBlock->next = next;
            current->next = nextBlock;
            next->next = current;
            previousBlock = current;
            current = nextBlock;
            if (current != NULL) {
                next = current->next;
            }
        }

        return syntheticHead->next;
    }

    void printList(ListNode* head) {
        ListNode* current = head;
        while(current !=  NULL) {
            std::cout << current->val << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    ListNode* head = new ListNode(1);
    ListNode* current = head;
    current->next = new ListNode(2);
    current = current->next;
    current->next = new ListNode(3);
    current = current->next;
    current->next = new ListNode(4);
    Solution sol;
    sol.printList(sol.swapPairs(head));
}
