// https://leetcode.com/problems/merge-k-sorted-lists/

#include <iostream>
#include <queue>
#include <cstdlib>

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

struct MinComparator {
    bool operator() (ListNode* i, ListNode* j) {
        return i->val > j->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        ListNode* new_list = NULL;
        ListNode* ptr;
        std::priority_queue<ListNode*, std::vector<ListNode*>, MinComparator> heap;
        for (std::vector<ListNode*>::iterator it = lists.begin(); it != lists.end(); it ++) {
            if (*it != NULL) {
                heap.push(*it);
            }
        }
        while (!heap.empty()) {
            ListNode* current = heap.top();
            heap.pop();
            if (new_list == NULL) {
        		ptr = new ListNode(current->val);
        		new_list = ptr;
        	}
        	else {
        		ptr->next = new ListNode(current->val);
        		ptr = ptr->next;
        	}
            if (current->next != NULL) {
                current = current->next;
                heap.push(current);
            }
        }
        return new_list;
    }
};

int main() {
    std::vector<ListNode*> lists;

    ListNode* start = new ListNode(1);
    start->next = new ListNode(3);
    ListNode* next = start->next;
    next->next = new ListNode(5);
    lists.push_back(start);

    start = new ListNode(2);
    start->next = new ListNode(4);
    next = start->next;
    next->next = new ListNode(6);
    lists.push_back(start);

    Solution sol;
    start = sol.mergeKLists(lists);
    while (start != NULL) {
        std::cout << start->val << std::endl;
        start = start->next;
    }
}
