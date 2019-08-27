// https://leetcode.com/problems/integer-to-roman/

#include <iostream>


class Solution {
public:
    std::string intToRoman(int num) {
        int remaining = num;
        int index = 0;
        std::string output;

        while (remaining > 0) {
            while (remaining >= values[index]) {
                output = output + symbols[index];
                remaining -= values[index];
            }
            index++;
        }

        return output;
    }

private:
    std::string symbols[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
};

int main() {
    Solution sol;
    std::cout << sol.intToRoman(13) << std::endl;
}
