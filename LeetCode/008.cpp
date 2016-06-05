// https://leetcode.com/problems/string-to-integer-atoi/

#include <string>
#include <iostream>
#include <climits>

class Solution {
public:
    int myAtoi(std::string str) {
        bool neg = false;
        int sum = 0;
        int i = 0;
        while(str[i] == ' ') {
            i ++;
        }
        if (str[i] == '-') {
            neg = true;
            i ++;
        }
        else if (str[i] == '+') {
            i ++;
        }
        for (; i < str.length(); i ++) {
            if (fromChar(str[i]) == -1) {
                if (neg) {
                    return -1*sum;
                }
                return sum;
            }
            if (INT_MAX/10 < sum) {
                if (neg) {
                    return INT_MIN;
                }
                else {
                    return INT_MAX;
                }
            }
            sum *= 10;
            if (INT_MAX - fromChar(str[i]) < sum) {
                if (neg) {
                    return INT_MIN;
                }
                else {
                    return INT_MAX;
                }
            }
            sum += fromChar(str[i]);
        }
        if (neg) {
            return -1*sum;
        }
        return sum;
    }

    int fromChar(char c) {
        switch(c) {
            case '0':
                return 0;
                break;
            case '1':
                return 1;
                break;
            case '2':
                return 2;
                break;
            case '3':
                return 3;
                break;
            case '4':
                return 4;
                break;
            case '5':
                return 5;
                break;
            case '6':
                return 6;
                break;
            case '7':
                return 7;
                break;
            case '8':
                return 8;
                break;
            case '9':
                return 9;
                break;
            default:
                return -1;
        }

    }
};

int main() {
    Solution sol;
    std::cout << sol.myAtoi("2147483648") << std::endl;
}
