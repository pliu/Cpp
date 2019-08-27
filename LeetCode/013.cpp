// https://leetcode.com/problems/roman-to-integer/

#include <iostream>


class Solution {
public:
    int romanToInt(std::string str) {
        int sum = 0;
        int str_index = 0;
        int symbols_index = 0;
        while (true) {
            while (str.substr(str_index, std::string::npos).rfind(symbols[symbols_index], 0) == 0) {
                str_index += symbols[symbols_index].size();
                sum += values[symbols_index];
                if (str_index >= str.size()) {
                    return sum;
                }
            }
            symbols_index++;
        }
    }

private:
    std::string symbols[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
};

int main() {
    Solution sol;
    std::cout << sol.romanToInt("MMMCIX") << std::endl;
}
