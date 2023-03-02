#include <iostream>
#include <algorithm>
#include <string.h>
#include <unistd.h>
#include <chrono>
/*std::string strSplit(std::string str, std::string splitPoint, int s) {           // Splits a string and returns whatever index you want it to be
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
    std::cout << "\n\nThis is it: '" << strSplit(str1, str2, in) << "'" << std::endl;
    return 0;
}*/
char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
bool isInt(std::string num) {               // Checks if a string is a number or not
    int counter;
    for (int i = 0; i < (int)num.length(); i ++) {
        counter = 0;
        for (int z = 0; z < 10; z ++) {
            if (num[i] != nums[z]) {
                counter ++;
            }
            else {
                break;
            }
        }
        if (!(counter < 10)) {
            return false;
        }
    }
    return true;
}
std::string getLine(std::string printout = "") {
    std::string ret;
    std::cout << printout;
    std::getline(std::cin, ret);
    return ret;
}
int getInt(std::string message) {
    std::string s = getLine(message);
    while (!isInt(s)) {
        if (s == "??") {
            return 99;
        }
        std::cout << "Invalid number!" << std::endl;
        sleep(1);
        s = getLine(message);
    }
    return std::stoi(s);
}
int main() {
    int num = getInt("Enter in an int: ");
    std::cout << num << std::endl;
    return 0;
}