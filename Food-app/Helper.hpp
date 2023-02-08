/*  Helper functions used globally  */

#pragma once

bool _isANumber(char c) {
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 10; i ++) {
        if (c != digits[i]) {
            return false;
        }
    }
    return true;
}

double toInt(std::string num) {                         // This makes sure that the string can be turned into an integer. No support for negative numbers yet.
    char dec = '.';
    short periodCount = 0;

    for (int x = 0; x < num.length(); x ++) {
        if (num[x] == dec) {
            periodCount ++;
            if (periodCount > 2) {
                return -1;
            }
        }
        else if (!_isANumber(num[x])) {
            return -1;
        }
    }
    return std::stoi(num);
}

std::string toStr(double num) {
    return std::to_string(num);
}