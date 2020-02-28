// https://leetcode.com/problems/multiply-strings/

#include <iostream>
#include <string>

class Solution {
   public:
    std::string multiply(std::string num1, std::string num2) {
        return std::to_string(recursiveMultiply(num1, num2));
    }

    // Uses Karatsuba's algorithm
    int recursiveMultiply(std::string num1, std::string num2) {
    }

    int stringMultiply(std::string num1, std::string num2) {
    }
};

int main() {
    Solution sol;
    std::cout << sol.multiply("12345", "54321") << std::endl;
}
