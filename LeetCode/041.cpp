// https://leetcode.com/problems/first-missing-positive/

#include <iostream>
#include <vector>

class Solution {
public:
    int firstMissingPositive(std::vector<int>& nums) {
    	/*
        This method works if there is only one missing integer between [1, max] and no duplicates
        It works by xor-ing all positive integers while keeping track of the largest integer seen so far. It then
        xors in the positive integers in [1, max]. Everything will cancel out except the missing integer.
    	int max = 0;
    	int aggregator = 0;
        for (int current : nums) {
        	if (current > max) {
        		max = current;
        	}
        	if (current > 0) {
        		aggregator = aggregator ^ current;
        	}
        }
        for (int i = 1; i <= max; i ++) {
        	aggregator = aggregator ^ i;
        }
        if (aggregator == 0) {
        	return max + 1;
        }
        else {
        	return aggregator;
        }
        */

        /*
        The set of elements present in nums, A, is a union of the set X, the set of integers that form the consecutive
        run of positive integers, [1, |X|], and the set Y, the set of non-positive integers, duplicates, or positive
        integers that do not participate in the run, [1, |X|]. As |X| <= |A|, the elements of X can be placed at their
        respective indices (i.e.: ∀x ∈ X: array[x-1] = x). Since we do not know |X|, we assume that |X| = |A| (i.e.:
        ∀a ∈ A, 1 <= a <= |A|: array[a-1] = a; ∀a ∈ A, a <= 0 or a > |A|: ignore a). Duplicates are implicitly handled
        as the corresponding index already contains the correct value from the first duplicate encountered.
        This works even if there are multiple gaps in [1, max] or duplicates
        */
        for (int i = 0; i < nums.size(); i ++) {

            /*
            At each index, if 1 <= array[i] <= |A| and array[i] != i + 1, continue swapping the value at the given index
            to its corresponding index. Once a value has been swapped to its corresponding index, it is never moved
            again, resulting in a O(n) runtime.
            To prevent infinite loops, the swap must swap two distinct values.
            */
        	while (nums[i] != i + 1 && nums[i] > 0 && nums[i] <= nums.size() && nums[nums[i] - 1] != nums[i]) {
        		int tmp = nums[nums[i] - 1];
        		nums[nums[i] - 1] = nums[i];
        		nums[i] = tmp;
        	}
        }

        /*
        Iterate through the array, looking for the first index such that array[i] != i + 1. Since every valid element in
        the array has been moved to its respective index, i + 1 must be the first missing positive integer (the
        delimitation between X and positive integers that do not participate in the run, which were assumed to be in X).
        */
        for (int i = 0; i < nums.size(); i ++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return nums.size() + 1;
    }
};

int main() {
	std::vector<int> nums;
    nums.push_back(1);
    nums.push_back(-2);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(6);
	Solution sol;
	std::cout << sol.firstMissingPositive(nums) << std::endl;
}
