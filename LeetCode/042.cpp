// https://leetcode.com/problems/trapping-rain-water/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

class Solution {
public:
    int trap(std::vector<int>& height) {
        std::vector<std::pair<int, int>> peaks;
    	int sum = 0;
    	int last_max_index = -1;
    	bool increasing = true;
        for (int i = 0; i < height.size(); i ++) {
        	int next_value = i + 1 == height.size() ? 0 : height[i + 1];
        	if (increasing && next_value < height[i]) {
        		peaks.push_back(std::pair<int, int>(height[i], i));
        		increasing = false;
        	}
        	if (!increasing && next_value > height[i]) {
        		increasing = true;
        	}
        }
        if (peaks.size() >= 2) {
            std::make_heap(peaks.begin(), peaks.end());
            std::pair<int, int> check = pop_heap(peaks);
            int left = check.second, right;
            check = pop_heap(peaks);
            if (check.second < left) {
                right = left;
                left = check.second;
            }
            else {
                right = check.second;
            }
            sum += get_capacity(height, left, right, check.first);
            while (!peaks.empty()) {
                check = pop_heap(peaks);
                if (check.second > right) {
                    sum += get_capacity(height, right, check.second, check.first);
                    right = check.second;
                }
                else if (check.second < left) {
                    sum += get_capacity(height, check.second, left, check.first);
                    left = check.second;
                }
            }
        }
        return sum;
    }

    std::pair<int, int> pop_heap(std::vector<std::pair<int, int>>& vec) {
        std::pair<int, int> ret = vec.front();
        std::pop_heap(vec.begin(), vec.end());
        vec.pop_back();
        return ret;
    }

    int get_capacity(std::vector<int>& height, int left, int right, int highest) {
        int sum = 0;
        for (int i = left + 1; i < right; i ++) {
            sum += highest - height[i] <= 0 ? 0 : highest - height[i];
        }
        return sum;
    }
};

int main() {
	std::vector<int> height;
    /*
	height.push_back(0); //  0
	height.push_back(1); //  1 *
	height.push_back(0); //  2
	height.push_back(2); //  3 *
	height.push_back(1); //  4
	height.push_back(0); //  5
	height.push_back(1); //  6
	height.push_back(3); //  7 *
	height.push_back(2); //  8
	height.push_back(1); //  9
	height.push_back(2); // 10 *
	height.push_back(1); // 11
    */
    height.push_back(5);
    height.push_back(4);
    height.push_back(1);
    height.push_back(2);
	Solution sol;
	std::cout << sol.trap(height) << std::endl;
}