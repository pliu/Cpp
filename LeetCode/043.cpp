// https://leetcode.com/problems/multiply-strings/

#include <iostream>
#include <string>

class Solution {
   public:
    std::string multiply(std::string num1, std::string num2) {
        short positionsLength = num1.size() + num2.size();
        short positions[positionsLength];
        for (short i = 0; i < positionsLength; i++) {
            positions[i] = 0;
        }
        short num1Array[num1.length()];
        short num2Array[num2.length()];
        for (short i = 0; i < num1.length(); i++) {
            num1Array[i] = Solution::charToShort(num1[i]);
        }
        for (short i = 0; i < num2.length(); i++) {
            num2Array[i] = Solution::charToShort(num2[i]);
        }

        for (short i = 0; i < num1.length(); i++) {
            for (short j = 0; j < num2.length(); j++) {
                short product = num1Array[num1.length() - 1 - i] * num2Array[num2.length() - 1 - j];
                positions[positionsLength - 1 - i - j] += product;
            }
        }

        std::string result = "";
        for (short i = 0; i < positionsLength; i++) {
            short unit = positions[positionsLength - 1 - i] % 10;
            short tens = positions[positionsLength - 1 - i] / 10;
            result.insert(result.begin(), 1, Solution::shortToChar(unit));
            if (tens > 0) {
                positions[positionsLength - 2 - i] += (tens);
            }
        }

        short i = 0;
        for (; i < result.length() - 1; i++) {
            if (result[i] != '0') {
                break;
            }
        }
        result = result.substr(i);

        return result;
    }

    static char shortToChar(short i) {
        switch (i) {
            case 1:
                return '1';
            case 2:
                return '2';
            case 3:
                return '3';
            case 4:
                return '4';
            case 5:
                return '5';
            case 6:
                return '6';
            case 7:
                return '7';
            case 8:
                return '8';
            case 9:
                return '9';
            default:
                return '0';
        }
    }

    static short charToShort(char c) {
        switch (c) {
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            case '5':
                return 5;
            case '6':
                return 6;
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            default:
                return 0;
        }
    }
};

int main() {
    Solution sol;
    std::cout << sol.multiply("12345", "54321") << std::endl;
}
