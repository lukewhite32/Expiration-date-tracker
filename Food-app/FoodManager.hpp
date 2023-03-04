/* Manages the files and all the food in it */

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <fstream>         // For file management
#include <string.h>
#include "Helper.hpp"

struct FoodManager {
    unsigned int length;              // The known length of the file
    std::string names[1000];
    Date dates[1000];
    short loc[1000];
    int rAmtOf[1000];

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
                rAmtOf[curLine] = std::stoi(strSplit(line, "r=", 1));

                if (dateLine == "??/??/??") {                // This means that the expiration date is unknown
                    dates[curLine] = {99, 99, 99, false};
                }
                else {
                    dates[curLine] = {std::stoi(strSplit(dateLine, "/", 0)), std::stoi(strSplit(dateLine, "/", 1)), std::stoi(strSplit(dateLine, "/", 2))};
                }
                curLine ++;
            }
            length = curLine;
        }
        file.close();
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

    int _amountOf(std::string name, Date date) {
        int ret = 0;
        for (int x = 0; x < length; x ++) {
            if (names[x] == name && date == dates[x]) {
                ret ++;
            }
        }
        return ret;
    }

    short _dateGreaterThan(Date date1, Date date2) {            // 0 = both equal, 1 = date2 bigger, -1 = date1 bigger.
        if (date1 > date2) {
            return -1;
        }
        else if (date1 == date2) {
            return 0;
        }
        return 1;
    }

    void writeToFile() {
        std::ofstream file {"Food-file.txt"};

        for (int x = 0; x < length; x ++) {
            file << names[x] << "  " << dates[x].getStrDate() << "  " << loc[x] << "r=" << rAmtOf[x] << std::endl; 
        }
        file.close();
    }

    void addItem(std::string name, Date date, short group, int rItems) {
        std::ofstream piper;
        piper.open("Food-file.txt", std::ios::app);

        piper << name << "  " << date.mon_str() << "/" << date.day_str() << "/" << date.year_str() << "  " << group << "  r=" << rItems << std::endl; 
        piper.close();

        names[length] = name;
        dates[length] = date;
        loc[length] = group;
        rAmtOf[length] = rItems;

        length += 1;

        _loadFile();
    }

    void removeItem(std::string name, Date date) {
        for (int i = 0; i < length; i ++) {
            if (names[i] == name && (dates[i] == date)) {
                for (int x = i; x < length - i-1; x ++) {
                    if (length == 1) {
                        writeToFile();
                        return;
                    }
                    names[x] = names[x+1];
                    dates[x] = dates[x+1];
                    loc[x] = loc[x+1];
                    rItems[x] = rItems[x+1];
                }
                length -= 1;
                writeToFile();
                return;
            }
        }
        std::cout << "Item '" << name << "' could not be found!" << std::endl;
    }

    int getAmtUniqueTypes(std::string name) {
        int uTypes = 0;
        Date tDate = {0, 0, 0};
        for (int x = 0; x < length; x ++) {
            if (name == names[x]) {
                if (!(dates[x] == tDate)) {
                    uTypes ++;
                    tDate = dates[x];
                }
            }
        }
        return uTypes;
    }

    Date getUniqueDatesFromName(std::string name, int index) {
        int curr = 0;
        Date tDate = {0, 0, 0};
        for (int x = 0; x < length; x ++) {
            if (name == names[x]) {
                if (!(dates[x] == tDate)) {
                    if (curr == index) {
                        return dates[x];
                    }
                    curr ++;
                    tDate = dates[x];
                }
            }
        }
        return tDate;
    }

    std::string sortDates() {                   // Returns a string of all the dates sorted, seperated by '/'
        bool over = false;
        std::string tmpNames[length];
        Date tmpDates[length];
        short tmpLocs[length];
        std::string theDates = "";

        for (int x = 0; x < length; x ++) {
            tmpDates[x] = dates[x];
            tmpLocs[x] = loc[x];
            tmpNames[x] = names[x];
        }

        while (!over) {
            for (int x = 0; x < length-1; x ++) {
                Date compare1 = tmpDates[x];
                Date compare2 = tmpDates[x+1];
            
                if (_dateGreaterThan(compare1, compare2) == -1) {
                    Date tmp;
                    short tmpG;
                    std::string tmpN;
                    tmp = tmpDates[x];                /*  Pretty much, swap 'em  */
                    tmpDates[x] = tmpDates[x+1];
                    tmpDates[x+1] = tmp;
                    tmpN = tmpNames[x];
                    tmpNames[x] = tmpNames[x+1];
                    tmpNames[x+1] = tmpN;
                    tmpG = tmpLocs[x];
                    tmpLocs[x] = tmpLocs[x+1];
                    tmpLocs[x+1] = tmpG;
                }
            }
            for (int x = 0; x < length-1; x ++) {
                if (_dateGreaterThan(tmpDates[x], tmpDates[x+1]) == -1) {
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
            theDates += tmpDates[i].getStrDate();
            theDates += "  ";
            theDates += std::to_string(tmpLocs[i]);
            if (length >= 2) {
                theDates += "  ";
            }
        }
        return theDates;
    }

    bool checkForKeyword(std::string name, int index) {          // Checks for a keyword in a name
        std::string tmps[splitAmt(names[index], " ")];

        for (int i = 0; i < splitAmt(names[index], " "); i ++) {
            tmps[i] = strSplit(names[index], " ", i);
        }

        for (int i = 0; i < splitAmt(names[index], " "); i ++) {
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
