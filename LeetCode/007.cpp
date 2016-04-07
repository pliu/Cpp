// https://leetcode.com/problems/reverse-integer/

#include <iostream>
#include <climits>

class Solution {
public:
    int reverse(int x) {
        int mult = x < 0 ? -1 : 1;
        if (x == INT_MIN) {
        	return 0;
        }
        x = x*mult;
        int rev = 0;
        while (x > 0) {
        	if (INT_MAX/10 < rev) {
        		return 0;
        	}
        	rev *= 10;
        	if (INT_MAX - x%10 < rev) {
        		return 0;
        	}
        	rev += x % 10;
        	x = x/10;
        }
        return rev*mult;
    }
};

int main() {
	Solution sol;
	std::cout << sol.reverse(-321) << std::endl;
}