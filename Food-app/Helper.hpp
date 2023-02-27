/*  Helper functions used globally  */

#pragma once

char lets[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

bool isInt(std::string num) {               // Checks if a string is a number or not
    int counter;
    for (int i = 0; i < num.length(); i ++) {
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

std::string zeroize(int num) {           // Turns '7' into '07'
    if (num < 10){
        return "0" + std::to_string(num);
    }
    return std::to_string(num);
}

char lowercase(char let) {
    int letloc;
    for (int i = 0; i < 52; i ++) {
        if (lets[i] == let) {
            letloc = i;
            break;
        }
    }

    if (letloc < 26) {
        return lets[letloc];
    }
    return lets[letloc-26];
}

char capitalize(char let) {
    int letloc;
    for (int i = 0; i < 52; i ++) {
        if (lets[i] == let) {
            letloc = i;
            break;
        }
    }

    if (letloc > 25) {
        return lets[letloc];
    }
    return lets[letloc+26];
}

short locationId(std::string num) {
    char ids[4] = {'A', 'B', 'C', 'D'};
    short ret;

    for (int i = 0; i < 4; i ++) {
        if (num[0] == ids[i]) {
            ret = (i*4);
            break;
        }
    }

    ret += std::stoi(num.substr(1));
    return ret;
}

std::string locationStr(short num) {
    if (num < 5) {
        return "A" + std::to_string(num);
    }
    else if (num < 9) {
        return "B" + std::to_string(num-4);
    }
    else if (num < 13) {
        return "C" + std::to_string(num-8);
    }
    else {
        return "D" + std::to_string(num-12);
    }
    return "";
}

std::string strCut(std::string str) {               // Makes "    Hello, world! " == "Hello, world! "
    std::string ret;
    int blankChars = 0; 
    for (int x = 0; x < str.length(); x ++) {
        if (str[x] != ' ') {
            break;
        }
        blankChars ++; 
    }
    for (int x = blankChars; x < str.length(); x ++) {
        ret += str[x];
    }
    return ret;
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

void printItem(std::string name, int m, int d, int y, int loc) {
    std::cout << name;
    for (int x = name.length(); x < 43; x ++) {
        std::cout << " ";
    }
    if (m == 99) {
        std::cout << "?????????";
    }
    else {
        std::cout << zeroize(m) << "/" << zeroize(d) << "/" << zeroize(y);
    }
    std::cout << "                                          " << locationStr(loc) << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
}