// https://leetcode.com/problems/add-two-numbers/

#include <cstddef>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = NULL;
        ListNode* current;
        int carry = 0;
        while (l1 != NULL || l2 != NULL) {
        	int sum = carry;
        	if (l1 != NULL) {
        		sum += l1->val;;
        		l1 = l1->next;
        	}
        	if (l2 != NULL) {
        		sum += l2->val;;
        		l2 = l2->next;
        	}
        	carry = sum / 10;
        	if (head == NULL) {
        		current = new ListNode(sum % 10);
        		head = current;
        	}
        	else {
        		current->next = new ListNode(sum % 10);
        		current = current->next;
        	}
        }
        if (carry > 0) {
        	current->next = new ListNode(carry);
        }
        return head;
    }
};

int main() {
	ListNode* l1 = new ListNode(2);
	ListNode* current = l1;
	current->next = new ListNode(4);
	current = current->next;
	current->next = new ListNode(3);
	ListNode* l2 = new ListNode(3);
	current = l2;
	current->next = new ListNode(6);
	Solution sol;
	current = sol.addTwoNumbers(l1, l2);
	while (current != NULL) {
		std::cout << current->val << std::endl;
		current = current->next;
	}
}