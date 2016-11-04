// https://leetcode.com/problems/longest-common-prefix/

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Solution {
public:
    class TrieNode {
    public:
        void addToTrie(std::string::iterator it, const std::string& str) {
            if (it == str.end()) {
                return;
            }

            count ++;

            char check = *it;
            if (map.find(check) == map.end()) {
                map[check] = new TrieNode();
                map[check]->addToTrie(it + 1, str);
            } else {
                map[check]->addToTrie(it + 1, str);
            }
        }

        std::unordered_map<char, TrieNode*> map;
        int count = 0;
    };

    std::string longestCommonPrefix(const std::vector<std::string>& strs) {
        TrieNode root;
        for (std::string str : strs) {
            root.addToTrie(str.begin(), str);
        }
        return getLongestCommonPrefixFromTrie(&root, strs.size());
    }

    std::string getLongestCommonPrefixFromTrie(TrieNode* root, int size) {
        std::ostringstream os;
        TrieNode* current = root;
        while (current->count == size && current->map.size() == 1) {
            auto bucket = current->map.begin();
            char key = bucket->first;
            os << key;
            current = bucket->second;
        }
        return os.str();
    }
};

int main() {
    std::vector<std::string> strs;
    strs.push_back("abra");
    strs.push_back("abs");
    strs.push_back("abracadabra");
    Solution sol;
    std::cout << sol.longestCommonPrefix(strs) << std::endl;
}
