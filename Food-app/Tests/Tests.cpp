#include <iostream>
#include <algorithm>
#include <string.h>
#include <unistd.h>
#include <chrono>

bool notSorted() {return false;}
void sort() {std::cout << "Sorting." << std::endl;}

struct Tests {
    int tests[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    short _dateGreaterThan(std::string date1, std::string date2) {            // 0 = both equal, 1 = date2 bigger, -1 = date1 bigger.

        int d1[] = { std::stoi(date1.substr(0, date1.find("/"))), std::stoi(date1.substr(date1.find("/")+1, date1.find("~"))), std::stoi(date1.substr(date1.find("~")+1)) };
        int d2[] = { std::stoi(date2.substr(0, date2.find("/"))), std::stoi(date2.substr(date2.find("/")+1, date2.find("~"))), std::stoi(date2.substr(date2.find("~")+1)) };
        
        short order[3] {2, 0, 1};
        for (int x : order) {
            if (d1[x] > d2[x]) {
                return -1;
            }
            else if (d1[x] < d2[x]) {
                return 1;
            }
        }
        return 0;
    }
    int dates[20][3] = {{12, 34, 21}, {32, 23, 22}, {53, 21, 20}};
    std::string names[20] = {"Unsweetened Corn", "Coconut Balls", "Help me"};
    short locs[20] = {3, 5, 1};
    int length = 3;

    std::string sortDates() {                   // Returns a string of all the dates sorted, seperated by '/'
        bool over = false;
        int tmpDates[length][3];
        std::string tmpNames[length];
        short tmpLocs[length];
        std::string theDates;

        for (int x = 0; x < length; x ++) {
            for (int y = 0; y < 3; y ++) {
                tmpDates[x][y] = dates[x][y];
            }
            tmpNames[x] = names[x];
            tmpLocs[x] = locs[x];

        }

        while (!over) {
            for (int x = 0; x < length-1; x ++) {
                std::string compare1, compare2;

                //std::cout << "compare 1: " << tmpDates[x][0] << ", " << tmpDates[x][1] << ", " << tmpDates[x][2] << std::endl;
                compare1 = std::to_string(tmpDates[x][0]) + "/" + std::to_string(tmpDates[x][1]) + "~" + std::to_string(tmpDates[x][2]);
                compare2 = std::to_string(tmpDates[x+1][0]) + "/" + std::to_string(tmpDates[x+1][1]) + "~" + std::to_string(tmpDates[x+1][2]);

                if (_dateGreaterThan(compare1, compare2) == -1) {
                    int tmp[3];
                    std::string tn;
                    short tl;
                    for (int i = 0; i < 3; i ++) {
                        tmp[i] = tmpDates[x][i];
                    }
                    for (int i = 0; i < 3; i ++) {
                        tmpDates[x][i] = tmpDates[x+1][i];
                        tmpDates[x+1][i] = tmp[i];
                    }
                    tn = tmpNames[x];
                    tmpNames[x] = tmpNames[x+1];
                    tmpNames[x+1] = tn;
                    tl = tmpLocs[x];
                    tmpLocs[x] = tmpLocs[x+1];
                    tmpLocs[x] = tl;   
                }
            }
            for (int x = 0; x < length-1; x ++) {
                if (_dateGreaterThan(std::to_string(tmpDates[x][0]) + "/" + std::to_string(tmpDates[x][1]) + "~" + std::to_string(tmpDates[x][2]), std::to_string(tmpDates[x+1][0]) + "/" + std::to_string(tmpDates[x+1][1]) + "~" + std::to_string(tmpDates[x+1][2])) == -1) {
                    break;
                }
                if (x == length-2) {
                    over = true;
                }
            }
        }
        for (int i = 0; i < length; i ++) {
            theDates += tmpNames[i];
            theDates += "%";
            theDates += std::to_string(tmpDates[i][0]); 
            theDates += std::to_string(tmpDates[i][1]);
            theDates += std::to_string(tmpDates[i][2]);
            theDates += std::to_string(tmpLocs[i]);
            if (length > 2 && i < length-1) {
                theDates += "/";
            }
        }
        return theDates;
    }

    void del(int index) {

    }
    int getLength() {
    std::string s = "Mac 'n' cheese";
    return s.length();
    }
};

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

std::string strSplit(std::string str, std::string stopPoint, int s) {                // Splits a string and returns whichever item in the list
    std::string ret = "";
    std::string tmp = "";
    std::string comps[20];      
    int current 0;
    while (1) {          
        for (int x = current; x < str.length(); x ++) {
            for (int y = 0; y < stopPoint.length(); y ++) {
                if (!(str[x+y] == stopPoint[y])) {        // check if reached stop point
                    comps[y] == 
                }
                if (y == stopPoint.length()-1) {
                    return ret;
                }
            }
            tmp += str[x];
        }
    }
    return ret;
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

int main() {
    Tests tests;

    std::cout << "enter str: ";
    std::string r;
    std::getline(std::cin, r);
    std::cout << "trimmed is '" << strCut(r) << "'." << std::endl;


    //std::string dateNums[2][3];
    //std::string date1, date2;

    //std::cout << "Enter in 2 dates: ";
    //std::cin >> dateNums[0][0] >> dateNums[0][1] >> dateNums[0][2] >> dateNums[1][0] >> dateNums[1][1] >> dateNums[1][2];

//while (1) {
  //  std::cout << "Enter string: ";
    //std::string s;
    //std::cin >> s;
    //std::cout << tests.getLength(s) << std::endl;
//}
    return 0;
}
