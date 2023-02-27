/* Manages the files and all the food in it */

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <fstream>         // For file management
#include <string.h>
#include "Helper.hpp"

struct FoodManager {
    unsigned int length;              // The known length of the file
    std::string names[10000];
    int dates[10000][3];
    short loc[10000];

    int _lengthOfFile() {
        std::ifstream file {"Food-file.txt"};
        std::string line;
        int len = 0;
        if (file.is_open()) {
            while (file.peek() != EOF) {
                std::getline(file, line);
                len ++;
            }
        }
        return len;
    }

    void _loadFile() {                             // 1 = A1, 2 = A2,... 5 = B1, 6 = B2, etc.
        std::ifstream file {"Food-file.txt"};
        unsigned long curLine = 0;
        std::string line, dateLine;

        if ( file.is_open() ) {
            for (int x = 0; x < _lengthOfFile(); x ++) {
                std::getline(file, line);
                if (line == "") {               // If it's a blank line, it must be the end
                    break;
                }
                names[curLine] = strSplit(line, "  ", 0);
                dateLine = strSplit(line, "  ", 1);
                loc[curLine] = std::stoi(strSplit(line, "  ", 2));

                if (dateLine == "??????") {                // This means that the expiration date is unknown
                    for (int x = 0; x < 3; x ++) {
                        for (int y = 0; y < 2; y ++) {
                            dates[curLine][x] = 99;
                        }
                    }
                }
                else {
                    short parse = 0;
                    for (int y = 0; y < 3; y ++) {
                        int tmpDate = std::stoi(dateLine.substr(parse, 2));
                        dates[curLine][y] = tmpDate;
                        parse += 2;
                    }
                }
                curLine ++;
            }
            length = curLine;
        }
        file.close();                  // Memory stuff
    }

    int _findItem(std::string name, int startPoint = 0) {
        for (int i = startPoint; i < length; i ++) {
            if (names[i] == name) {
                return i;
            }
        }
        return -1;
    }

    FoodManager() {
        _loadFile();
    }

    int _amoumtOf(std::string name) {
        int ret;
        for (int x = 0; x < length; x ++) {
            if (names[x] == name) {
                ret ++;
            }
        }
        return ret;
    }

    short _dateGreaterThan(std::string date1, std::string date2) {            // 0 = both equal, 1 = date2 bigger, -1 = date1 bigger.
        int d1[] = {std::stoi(strSplit(date1, "  ", 0)), std::stoi(strSplit(date1, "  ", 1)), std::stoi(strSplit(date1, "  ", 2))};
        int d2[] = {std::stoi(strSplit(date2, "  ", 0)), std::stoi(strSplit(date2, "  ", 1)), std::stoi(strSplit(date2, "  ", 2))};
        
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

    void writeToFile() {
        std::ofstream file {"Food-file.txt"};

        for (int x = 0; x < length; x ++) {
            file << names[x] << "  " << zeroize(dates[x][0]) << zeroize(dates[x][1]) << zeroize(dates[x][2]) << "  " << loc[x] << std::endl; 
        }
        file.close();
    }

    void addItem(std::string name, int month, int day, int year, short group) {
        std::ofstream piper;
        piper.open("Food-file.txt", std::ios::app);

        piper << name << "  " << zeroize(month) << zeroize(day) << zeroize(year) << "  " << group << "\n"; 
        piper.close();

        names[length] = name;

        dates[length][0] = month;
        dates[length][1] = day;
        dates[length][2] = year;
        loc[length] = group;

        length += 1;

        _loadFile();
    }

    void removeItem(std::string name) {
        for (int i = 0; i < length; i ++) {
            if (names[i] == name) {
                for (int x = i; x < length - i-1; x ++) {
                    if (length == 1) {
                        writeToFile();
                        return;
                    }
                    names[x] = names[x+1];
                    dates[x][0] = dates[x+1][0];
                    dates[x][1] = dates[x+1][1];
                    dates[x][2] = dates[x+1][2];
                    loc[x] = loc[x+1];
                }
                length -= 1;
                writeToFile();
                return;
            }
        }
        std::cout << "Item '" << name << "' could not be found!" << std::endl;
    }

    std::string sortDates() {                   // Returns a string of all the dates sorted, seperated by '/'
        bool over = false;
        std::string tmpNames[length];
        int tmpDates[length][3];
        short tmpLocs[length];
        std::string theDates = "";

        for (int x = 0; x < length; x ++) {
            for (int y = 0; y < 3; y ++) {
                tmpDates[x][y] = dates[x][y];
            }
            tmpLocs[x] = loc[x];
            tmpNames[x] = names[x];
        }

        while (!over) {
            for (int x = 0; x < length-1; x ++) {
                std::string compare1, compare2;              // Compare 2 date; the one at the index, and the one above it.

                compare1 = toStr(tmpDates[x][0]) + "  " + toStr(tmpDates[x][1]) + "  " + toStr(tmpDates[x][2]);
                compare2 = toStr(tmpDates[x+1][0]) + "  " + toStr(tmpDates[x+1][1]) + "  " + toStr(tmpDates[x+1][2]);
            
                if (_dateGreaterThan(compare1, compare2) == -1) {
                    int tmp[3];
                    short tl;
                    std::string tn;
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
                    tmpLocs[x+1] = tl;
                }
            }
            for (int x = 0; x < length-1; x ++) {
                if (_dateGreaterThan(toStr(tmpDates[x][0])  +  "  " + toStr(tmpDates[x][1])  +  "  " + toStr(tmpDates[x][2]), 
                                     toStr(tmpDates[x+1][0]) + "  " + toStr(tmpDates[x+1][1]) + "  " + toStr(tmpDates[x+1][2])) == -1) {
                    break;
                }
                if (x == length-2) {
                    over = true;
                }
            }
        }
        for (int i = 0; i < length; i ++) {
            theDates += tmpNames[i];
            theDates += "  ";
            theDates += zeroize(tmpDates[i][0]); 
            theDates += "/";
            theDates += zeroize(tmpDates[i][1]);
            theDates += "/";
            theDates += zeroize(tmpDates[i][2]);
            theDates += "  ";
            theDates += toStr(tmpLocs[i]);
            if (length >= 2) {
                theDates += "  ";
            }

        }
        return theDates;
    }

    bool checkForKeyword(std::string name, int index) {          // Checks for a keyword in a name
        std::string tmps[splitAmt(name, " ")];               
        int curTmp = 0;
        std::string tt = "";
        for (int i = 0; i < names[index].length(); i ++) {
            if (names[index][i] == ' ') {
                tmps[curTmp] = tt;
                curTmp ++;
                tt = "";
            }
            else {
                tt += names[index][i];
            }
        }
        tmps[curTmp] = tt;
        curTmp ++;
        for (int i = 0; i < curTmp; i ++) {
            std::string comp;
            comp = capitalize(tmps[i][0]) + tmps[i].substr(1);
            if (name == comp) {
                return true;
            }
            comp = lowercase(tmps[i][0]) + tmps[i].substr(1);
            
            if (name == comp) {
                return true;
            }
        }
        return false;
    }
};
#endif
