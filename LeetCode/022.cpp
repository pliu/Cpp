// https://leetcode.com/problems/generate-parentheses/

#include <iostream>
#include <string>
#include <vector>
#include <set>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> results = recursiveGenerateParenthesis(0, 0, n);
        return results;
    }

    // The logic is a bit counterintuitive as the recursion goes from left to right but the string generation goes from
    // right to left during the unwinding of the recursive stack
    std::vector<std::string> recursiveGenerateParenthesis(int open, int completed, int target) {
        std::vector<std::string> newStrings;

        // Base case: If the number of matching parens is the desired quantity, return a vector consisting of an empty
        // string
        if (completed == target) {
            newStrings.push_back("");
            return newStrings;
        }

        // If the sum of matching parens and open parens is the desired quantity, the only option is to close a paren
        if (open + completed == target) {
            std::vector<std::string> results = recursiveGenerateParenthesis(open - 1, completed + 1, target);
            for (std::vector<std::string>::iterator it = results.begin(); it != results.end(); it ++) {
                newStrings.push_back(")" + *it);
            }
        }

        // If the sum of matching parens and open parens is less than the desired quantity, one can open a paren or
        // close a paren
        if (open + completed < target) {

            // If there are open parens, then closing a paren is possible
            if (open > 0) {
                std::vector<std::string> results = recursiveGenerateParenthesis(open - 1, completed + 1, target);
                for (std::vector<std::string>::iterator it = results.begin(); it != results.end(); it ++) {
                    newStrings.push_back(")" + *it);
                }
            }

            // Opening a new paren is always possible
            std::vector<std::string> results = recursiveGenerateParenthesis(open + 1, completed, target);
            for (std::vector<std::string>::iterator it = results.begin(); it != results.end(); it ++) {
                newStrings.push_back("(" + *it);
            }
        }

        return newStrings;
    }
};

int main() {
    Solution sol;
    std::vector<std::string> strs = sol.generateParenthesis(10);
    for (std::vector<std::string>::iterator it = strs.begin(); it != strs.end(); it ++) {
        std::cout << *it << std::endl;
    }
}
