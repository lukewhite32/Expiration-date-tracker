/* Manages the files and all the food in it */

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <fstream>         // For file management
#include <string.h>
#include <vector>
#include "Helper.hpp"
#include <algorithm>

struct FoodManager {
    std::vector<std::string> names;
    std::vector<Date> dates;
    std::vector<short> loc;
    std::vector<int> rAmtOf;

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

    void _loadFile() {
        names.clear();
        dates.clear();
        loc.clear();
        rAmtOf.clear();
        std::ifstream file {"Food-file.txt"};
        std::string line, dateLine;

        if ( file.is_open() ) {
            for (int x = 0; x < _lengthOfFile(); x ++) {
                std::getline(file, line);
                debugPrint(line, "looking at");
                names.push_back(strSplit(line, "  ", 0));
                debugPrint(strSplit(line, "  ", 0), "name");
                dateLine = strSplit(line, "  ", 1);
                loc.push_back(std::stoi(strSplit(line, "  ", 2)));
                rAmtOf.push_back(std::stoi(strSplit(line, "r=", 1)));

                if (dateLine == "??/??/??") {                // This means that the expiration date is unknown
                    dates.push_back({99, 99, 99, false});
                }
                else {
                    dates.push_back({std::stoi(strSplit(dateLine, "/", 0)), std::stoi(strSplit(dateLine, "/", 1)), std::stoi(strSplit(dateLine, "/", 2))});
                }
            }
        }
        file.close();
    }

    int _findItem(std::string name, int startPoint = 0) {
        for (unsigned int i = startPoint; i < names.size(); i ++) {
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
        for (unsigned int x = 0; x < names.size(); x ++) {
            if (names[x] == name && date == dates[x]) {
                ret ++;
            }
        }
        return ret;
    }

    void writeToFile() {
        std::ofstream file {"Food-file.txt"};

        for (unsigned long x = 0; x < names.size(); x ++) {
            file << names[x] << "  " << dates[x].getStrDate() << "  " << loc[x] << "  r=" << rAmtOf[x] << std::endl; 
        }
        file.close();
    }

    void addItem(std::string name, Date date, short group, int rItems) {
        std::ofstream piper;
        piper.open("Food-file.txt", std::ios::app);

        piper << name << "  " << date.mon_str() << "/" << date.day_str() << "/" << date.year_str() << "  " << group << "  r=" << rItems << std::endl; 
        piper.close();

        names.push_back(name);
        dates.push_back(date);
        loc.push_back(group);
        rAmtOf.push_back(rItems);

        _loadFile();
    }

    void removeItem(std::string name, Date date) {
        for (unsigned long i = 0; i < names.size(); i ++) {
            if (names[i] == name && (dates[i] == date)) {
                removeFromVector(names, i);
                removeFromVector(dates, i);
                removeFromVector(loc, i);
                removeFromVector(rAmtOf, i);
                writeToFile();
                return;
            }
        }
        std::cout << "Item '" << name << "' could not be found!" << std::endl;
    }

    int getAmtUniqueTypes(std::string name) {
        int uTypes = 0;
        Date tDate = {0, 0, 0};
        for (unsigned long x = 0; x < names.size(); x ++) {
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
        for (unsigned long x = 0; x < names.size(); x ++) {
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
        _loadFile();
        bool over = false;
        std::vector<std::string> tmpNames;
        std::vector<Date> tmpDates;
        std::vector<short> tmpLocs;
        std::vector<int> tmpAmts;
        std::string theDates = "";

        for (unsigned long x = 0; x < names.size(); x ++) {
            tmpDates.push_back(dates[x]);
            tmpLocs.push_back(loc[x]);
            tmpNames.push_back(names[x]);
            tmpAmts.push_back(rAmtOf[x]);
            std::cout << "called" << std::endl;
        }

        while (!over) {
            for (unsigned long x = 0; x < names.size()-1; x ++) {
                Date compare1 = tmpDates[x];
                Date compare2 = tmpDates[x+1];
            
                if (compare1 > compare2) {
                    Date tmp;
                    short tmpG;
                    std::string tmpN;
                    int tmpR;
                    tmp = tmpDates[x];                
                    tmpDates[x] = tmpDates[x+1];
                    tmpDates[x+1] = tmp;
                    tmpN = tmpNames[x];
                    tmpNames[x] = tmpNames[x+1];
                    tmpNames[x+1] = tmpN;
                    tmpG = tmpLocs[x];
                    tmpLocs[x] = tmpLocs[x+1];
                    tmpLocs[x+1] = tmpG;
                    tmpR = tmpAmts[x];
                    tmpAmts[x] = tmpAmts[x+1];
                    tmpAmts[x+1] = tmpR;
                    /*std::swap(tmpDates.begin() + x, tmpDates.begin() + x + 1);       // thanks stackoverflow
                    std::swap(tmpNames.begin() + x, tmpDates.begin() + x + 1);
                    std::swap(tmpLocs.begin() + x, tmpLocs.begin() + x + 1);
                    std::swap(tmpAmts.begin() + x, tmpAmts.begin() + x + 1);*/
                }
            }
            for (unsigned long x = 0; x < names.size()-1; x ++) {
                if (tmpDates[x] > tmpDates[x+1]) {
                    break;
                }
                if (x == names.size()-2) {
                    over = true;
                }
            }
        }
        for (unsigned long i = 0; i < names.size(); i ++) {
            theDates += tmpNames[i];
            theDates += "  ";
            theDates += tmpDates[i].getStrDate();
            theDates += "  ";
            theDates += std::to_string(tmpLocs[i]);
            theDates += "  r=";
            theDates += std::to_string(tmpAmts[i]);
            if (names.size() >= 2) {
                theDates += "  ";
            }
        }
        return theDates;
    }

    bool checkForKeyword(std::string name, int index) {          // Checks for a keyword in a name
        std::vector<std::string> tmps;

        for (int i = 0; i < splitAmt(names[index], " "); i ++) {
            tmps.push_back(strSplit(names[index], " ", i));
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
