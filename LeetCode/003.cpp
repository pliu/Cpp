// https://leetcode.com/problems/longest-substring-without-repeating-characters/

#include <string>
#include <iostream>
#include <unordered_map>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
    	int i = 1;
    	int last = 0;
    	int longest = 0;
        std::unordered_map<char, int> index;
        for (char& c : s) {
        	std::unordered_map<char, int>::iterator result = index.find(c);
        	if (result != index.end()) {
        		if (result->second > last) {
        			last = result->second;
        		}
        	}
        	if (i - last > longest) {
        		longest = i - last;
        	}
        	index[c] = i;
        	i ++;
        }
        return longest;
    }
};

int main() {
	Solution sol;
	std::cout << sol.lengthOfLongestSubstring("rfwcsfmoxeqmrjowrghwlkobmeahkgccnaehhsveymqpxhlrnunyfdzrhbasjeuygafoubutpnimuwfjqsjxvkqdorxxvrwct") << std::endl;
}