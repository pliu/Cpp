// https://leetcode.com/problems/letter-combinations-of-a-phone-number/

#include <iostream>
#include <vector>
#include <map>


class Solution {
public:
    std::vector<std::string> letterCombinations(std::string digits) {
        recursiveGenerateStrings("", digits);
        return strings;
    }

    void print(const std::vector<std::string>& str) {
        for (std::string s : str) {
            std::cout << s << std::endl;
        }
    }

private:
    void recursiveGenerateStrings(const std::string& current_str, const std::string& digits) {
        if (digits.size() == 0) {
            if (current_str.size() > 0) {
                strings.push_back(current_str);
            }
            return;
        }

        std::string options = mapping[digits.at(0)];
        for (char option : options) {
            recursiveGenerateStrings(current_str + option, digits.substr(1, std::string::npos));
        }
    }

    std::vector<std::string> strings;

    std::map<char, std::string> mapping = {
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wyxz"}};
};

int main() {
    Solution sol;
    sol.print(sol.letterCombinations("23"));
}
