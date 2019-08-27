// https://leetcode.com/problems/reverse-nodes-in-k-group/

#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        bool kRemaining = true;

        // Synthetic head node inserted in front of the real head
        ListNode syntheticHead(-1);

        // The last and first nodes of the previous and next blocks, respectively
        ListNode* lastBlock = &syntheticHead;
        ListNode* nextBlock = head;

        // The three pointers used for reversing a singly-linked list
        ListNode* prev;
        ListNode* current;
        ListNode* next;

        // Having the synthetic head allows every iteration to be the same case as
        // opposed to having the first iteration be an edge case
        while (true) {
            prev = nextBlock;
            current = nextBlock;
            ListNode* walker = nextBlock;

            // Walk k steps down to find the first node of the next block or mark
            // kRemaining as false if there aren't k nodes remaining
            for (int i = 0; i < k; i++) {
                if (walker == NULL) {
                    kRemaining = false;
                    break;
                }
                walker = walker->next;
            }

            // Reversal of block followed by linking the reversed block to the
            // previous block
            if (kRemaining) {
                next = current->next;
                nextBlock = walker;
                ListNode* newLastBlock = current;
                while (next != nextBlock) {
                    current = next;
                    next = next->next;
                    current->next = prev;
                    prev = current;
                }
                lastBlock->next = current;
                newLastBlock->next = NULL;
                lastBlock = newLastBlock;

            // If there is no final block, link the end of the last block to the
            // remaining nodes
            } else {
                lastBlock->next = nextBlock;
                break;
            }
        }
        return syntheticHead.next;
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
    Solution sol;
    ListNode* head = new ListNode(1);
    ListNode* current = head;
    current->next = new ListNode(2);
    current = current->next;
    current->next = new ListNode(3);
    current = current->next;
    current->next = new ListNode(4);
    current = current->next;
    current->next = new ListNode(5);
    sol.printList(sol.reverseKGroup(head, 2));
}
