// https://leetcode.com/problems/remove-element/

#include <iostream>
#include <vector>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        int fillIndex = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums.at(i) != val) {
                nums.at(fillIndex) = nums.at(i);
                fillIndex++;
            }
        }
        return fillIndex;
    }
};

int main() {
    Solution sol;
    std::vector<int> input = {0, 1, 2, 2, 3, 0, 4, 2};
    std::cout<< sol.removeElement(input, 2) << std::endl;
}
