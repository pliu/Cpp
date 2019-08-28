// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        // Dummy node inserted before the actual head to enable generalization of the subsequent logic without having
        // a special edge case for when the node to be removed is the head
        auto* dummy = new ListNode(-1);

        dummy->next = head;
        ListNode* leader = head;
        ListNode* nth = head;
        ListNode* prev = dummy;
        for (int i = 0; i < n; i ++) {
            leader = leader->next;
        }
        while(leader != NULL) {
            leader = leader->next;
            nth = nth->next;
            prev = prev->next;
        }
        prev->next = nth->next;
        return dummy->next;
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
    sol.printList(sol.removeNthFromEnd(head, 5));
}


