// https://leetcode.com/problems/two-sum/

#include <unordered_map>
#include <vector>
#include <iostream>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
    	std::vector<int> answer;
        std::unordered_map<int, int> index;
        int i = 0;
        for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); it ++) {
        	index[*it] = i;
        	i ++;
        }
        i = 0;
        for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); it ++) {
        	int diff = target - *it;
        	std::unordered_map<int, int>::iterator result = index.find(diff);
        	if (result != index.end() && i != result->second) {
        		answer.push_back(i);
        		answer.push_back(result->second);
        		break;
        	}
        	i ++;
        }
        return answer;
    }
};

int main() {
	std::vector<int> test;
	for (int i = 0; i < 10; i ++) {
		test.push_back(i*2);
	}
	Solution sol;
	test = sol.twoSum(test, 36);
	for (int i : test) {
		std::cout << i << std::endl;
	}
	return 0;
}