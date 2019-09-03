// https://leetcode.com/problems/remove-duplicates-from-sorted-array/

#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        int lastSeenInt = INT32_MIN;
        int fillIndex = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums.at(i) > lastSeenInt) {
                lastSeenInt = nums.at(i);
                nums.at(fillIndex) = nums.at(i);
                fillIndex++;
            }
        }
        return fillIndex;
    }
};

int main() {
    Solution sol;
    std::vector<int> input = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    std::cout<< sol.removeDuplicates(input) << std::endl;
}
