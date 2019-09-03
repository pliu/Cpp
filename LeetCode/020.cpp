// https://leetcode.com/problems/valid-parentheses/

#include <iostream>
#include <string>
#include <map>
#include <stack>

class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> seen;
        for (char c : s) {
            if (parenMatches.find(c) == parenMatches.end()) {
                seen.push(c);
            } else {
                if (seen.empty() || parenMatches[c] != seen.top()) {
                    return false;
                }
                seen.pop();
            }
        }
        return seen.empty();
    }

private:
    std::map<char, char> parenMatches = {
            {')', '('},
            {'}', '{'},
            {']', '['},
    };
};

int main() {
    Solution sol;
    std::cout << sol.isValid("()[]{}") << std::endl;
}
