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

std::string toStr(auto what) {
    return std::to_string(what);
}

std::string zeroize(int num) {           // Turns '7' into '07'
    if (num < 10){
        return "0" + num;
    }
    return toStr(num);
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
        return "A" + toStr(num);
    }
    else if (num < 9) {
        return "B" + toStr(num-4);
    }
    else if (num < 13) {
        return "C" + toStr(num-8);
    }
    else {
        return "D" + toStr(num-12);
    }
    return "";
}

std::string strCut(std::string str) {               // Makes "    Hello, world! " == "Hello, world! "
    std::string ret;
    int blankChars = 0; 
    for (int x = 0; x < str.length(); x ++) {
        std::cout << "xaminin '" << str[x] << "'." << std::endl;
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

std::string strUntil(std::string str, std::string stopPoint, int s) {           // Reads a string until it reaches a spot, then returns it
    std::string ret = "";
    for (int x = s; x < str.length(); x ++) {
        for (int y = 0; y < stopPoint.length(); y ++) {
            if (!(str[x+y] == stopPoint[y])) {
                break;
            }
            if (y == stopPoint.length()-1) {
                return ret;
            }
        }
        ret += str[x];
    }
    return ret;
}

void printItem(std::string name, std::string date, int loc) {

}