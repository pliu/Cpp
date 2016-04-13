// https://leetcode.com/problems/palindrome-number/

#include <iostream>
#include <cmath>

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        int length;
        for (length = 0; x/(int)pow(10, length) > 0; length ++) {}
        length --;
        while (length > 0) {
            int right = x % 10;
            int left = (x / (int)pow(10, length)) % 10;
            std::cout << x << " " << left << " " << right << " " << length << std::endl;
            if (right != left) {
                return false;
            }
            x %= (int)pow(10, length);
            x /= 10;
            length -= 2;
        }
        return true;
    }
};

int main() {
    Solution sol;
    std::cout << sol.isPalindrome(5335) << std::endl;
}
