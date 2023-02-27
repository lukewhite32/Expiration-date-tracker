#include <iostream>
#include <algorithm>
#include <string.h>
#include <unistd.h>
#include <chrono>
std::string strSplit(std::string str, std::string splitPoint, int s) {           // Splits a string and returns whatever index you want it to be
    int total = -1;
    std::string curr = "";
    for (int x = 0; x < str.length(); x ++) {
        for (int y = 0; y < splitPoint.length(); y ++) {
            if (str[x+y] != splitPoint[y]) {
                break;
            }
            if (y == splitPoint.length()-1) {
                total ++;
                x += splitPoint.length();
                if (total == s) {
                    return curr;
                }
                curr = "";
            }
        }
        curr += str[x];
    }
    return curr;
}

int splitAmt(std::string str, std::string splitPoint) {
    int total = 1;
    for (int x = 0; x < str.length(); x ++) {
        for (int y = 0; y < splitPoint.length(); y ++) {
            if (str[x+y] != splitPoint[y]) {
                break;
            }
            if (y == splitPoint.length()-1) {
                total ++;
            }
        }
    }
    return total;
}

int main() {
    //std::string str1, str2;
    int in = 36;
    std::string s, st;
    std::cout << "enter str: ";
    std::getline(std::cin, s);
    std::cout << "enter spl: ";
    std::getline(std::cin, st);
    std::cout << splitAmt(s, st) << std::endl;
    /*std::cout << "Enter a string; ";
    std::getline(std::cin, str1);
    std::cout << "Enter in nother string: ";
    std::getline(std::cin, str2);
    std::cout << "Index: ";std::cin >> in;
    std::cout << "\n\nThis is it: '" << strSplit(str1, str2, in) << "'" << std::endl;*/
    return 0;
}