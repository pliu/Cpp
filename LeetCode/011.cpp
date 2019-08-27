// https://leetcode.com/problems/container-with-most-water/

#include <vector>
#include <iostream>
#include <algorithm>


class Solution {
public:
    int maxArea(std::vector<int>& height) {
        int left_index = 0;
        int right_index = height.size() - 1;
        int max_volume = 0;

        while(left_index != right_index) {
            int check_volume = (right_index - left_index) * std::min(height[left_index], height[right_index]);
            if (check_volume > max_volume) {
                max_volume = check_volume;
            }

            // The water contained between two points is their separation * min(their heights). If we start from the
            // left- and right-most sides and move in, separation strictly decreases. As such the only way for the
            // contained water to increase is for min(their height) to increase. This only occurs when the current min
            // rises, as such we move the index of the current min in search of a higher point.
            if (leftIsMax(height, left_index, right_index)) {
                right_index--;
            } else {
                left_index ++;
            }
        }

        return max_volume;
    }

private:
    bool leftIsMax(const std::vector<int>& height, int left_index, int right_index) {
        return height[left_index] > height[right_index];
    }
};

int main() {
    Solution sol;
    std::vector<int> heights;
    heights.push_back(1);
    heights.push_back(8);
    heights.push_back(6);
    heights.push_back(2);
    heights.push_back(5);
    heights.push_back(4);
    heights.push_back(8);
    heights.push_back(3);
    heights.push_back(7);
    std::cout << sol.maxArea(heights) << std::endl;
}
