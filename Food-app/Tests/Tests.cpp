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
    int length = 3;

    std::string sortDates() {                   // Returns a string of all the dates sorted, seperated by '/'
        bool over = false;
        int tmpDates[length][3];
        std::string theDates;

        for(int x = 0; x < length; x ++) {
            for (int y = 0; y < 3; y ++) {
                tmpDates[x][y] = dates[x][y];
            }
        }

        while (!over) {
            for (int x = 0; x < length-1; x ++) {
                std::string compare1, compare2;

                //std::cout << "compare 1: " << tmpDates[x][0] << ", " << tmpDates[x][1] << ", " << tmpDates[x][2] << std::endl;
                compare1 = std::to_string(tmpDates[x][0]) + "/" + std::to_string(tmpDates[x][1]) + "~" + std::to_string(tmpDates[x][2]);
                compare2 = std::to_string(tmpDates[x+1][0]) + "/" + std::to_string(tmpDates[x+1][1]) + "~" + std::to_string(tmpDates[x+1][2]);

                if (_dateGreaterThan(compare1, compare2) == -1) {
                    int tmp[3];
                    for (int i = 0; i < 3; i ++) {
                        tmp[i] = tmpDates[x][i];
                    }
                    for (int i = 0; i < 3; i ++) {
                        tmpDates[x][i] = tmpDates[x+1][i];
                        tmpDates[x+1][i] = tmp[i];
                    }   
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
            theDates += std::to_string(tmpDates[i][0]); 
            theDates += std::to_string(tmpDates[i][1]);
            theDates += std::to_string(tmpDates[i][2]);
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

int main() {
    Tests tests;
    //std::string dateNums[2][3];
    //std::string date1, date2;

    //std::cout << "Enter in 2 dates: ";
    //std::cin >> dateNums[0][0] >> dateNums[0][1] >> dateNums[0][2] >> dateNums[1][0] >> dateNums[1][1] >> dateNums[1][2];

    std::cout << tests.sortDates() << std::endl;
//while (1) {
  //  std::cout << "Enter string: ";
    //std::string s;
    //std::cin >> s;
    //std::cout << tests.getLength(s) << std::endl;
//}
    return 0;
}
