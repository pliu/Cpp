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

        //
        ListNode syntheticHead(-1);

        //
        ListNode* lastBlock = &syntheticHead;
        ListNode* nextBlock = head;

        //
        ListNode* prev;
        ListNode* current;
        ListNode* next;

        //
        while (true) {
            prev = nextBlock;
            current = nextBlock;
            ListNode* walker = nextBlock;

            //
            for (int i = 0; i < k; i++) {
                if (walker == NULL) {
                    kRemaining = false;
                    break;
                }
                walker = walker->next;
            }

            //
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

                //
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
