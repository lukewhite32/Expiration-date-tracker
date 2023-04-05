/* Manages the files and all the food in it */

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <fstream>         // For file management
#include <string.h>
#include <vector>

#include "Helper.hpp"

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
                if (std::stoi(strSplit(line, "r=", 1)) > 0) {
                    names.push_back(strSplit(line, "  ", 0));
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
        }
        file.close();
    }

    FoodManager() {
        _loadFile();
    }

    int _amountOf(std::string name) {
        int ret = 0;
        for (unsigned int x = 0; x < names.size(); x ++) {
            if (names[x] == name) {
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

    void removeItem(Info info) {
        for (unsigned long i = 0; i < names.size(); i ++) {
            if ((info.name == names[i]) && (info.date == dates[i]) && (info.loc == loc[i]) && (info.amt == rAmtOf[i])) {
                removeFromVector(names, i);
                removeFromVector(dates, i);
                removeFromVector(loc, i);
                removeFromVector(rAmtOf, i);
                writeToFile();
            }
        }
        //std::cout << "Item '" << name << "' could not be found!" << std::endl;
    }

    std::vector<Info> getUniqueItems(std::string name) {
        std::vector<Info> ret;
        for (unsigned int i = 0; i < names.size(); i ++) {
            if (names[i] == name) {
                ret.push_back({name, dates[i], loc[i], rAmtOf[i]});
            }
        }
        return ret;
    }

    void removeAmtOfItem(Info info, int amt) {
        for (unsigned int x = 0; x < names.size(); x ++) {
            if ((info.name == names[x]) && (info.date == dates[x]) && (info.loc == loc[x]) && (info.amt == rAmtOf[x])) {
                rAmtOf[x] -= amt;
                if (rAmtOf[x] <= 0) {
                    debugPrint("less than");
                    removeItem({info});
                }
            }
        }
        writeToFile();
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
        }

        while (!over) {
            for (unsigned long x = 0; x < names.size()-1; x ++) {
                Date compare1 = tmpDates[x];
                Date compare2 = tmpDates[x+1];
            
                if (compare1 > compare2) {
                    Date tmp1, tmp2;
                    short tmpG1, tmpG2;
                    std::string tmpN1, tmpN2;
                    int tmpR1, tmpR2;
                    tmp1 = tmpDates[x];                
                    tmp2 = tmpDates[x+1];
                    tmpDates[x+1] = tmp1;
                    tmpDates[x] = tmp2;
                    tmpN1 = tmpNames[x];
                    tmpN2 = tmpNames[x+1];
                    tmpNames[x] = tmpN2;
                    tmpNames[x+1] = tmpN1;
                    tmpG1 = tmpLocs[x];
                    tmpG2 = tmpLocs[x+1];
                    tmpLocs[x] = tmpG2;
                    tmpLocs[x+1] = tmpG1;
                    tmpR1 = tmpAmts[x];
                    tmpR2 = tmpAmts[x+1];
                    tmpAmts[x+1] = tmpR1;
                    tmpAmts[x] = tmpR2;
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
