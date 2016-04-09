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

        /*
        Iterates over the string and for each character, keeps track of the last index that character was observed at.
        At each position, the index from which no duplicate characters have been observed up until now is moved up to
        the last index of the character at the given position. Every substring without repeating characters ends at some
        position and the longest length of a substring without repeating characters ending at any given position is
        the distance from the index from which no duplicate characters have been observed up until the given position to
        the given position. In other words, the longest substring without repeating characters is limited by the
        shortest distance between duplicate characters contained within the substring.
        */
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
