#pragma once

#ifndef MANAGER_HPP
#include "FoodManager.hpp"
#endif

#ifndef INTER_HPP
#define INTER_HPP

#include <ctime>
#include <unistd.h>

class Interface {
    FoodManager manager;

    time_t curr = time(0);
    tm* times = localtime(&curr);

    int monthDays[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    long year = times -> tm_year + 1900;            // tm_year returns the year starting from 1900
    int mon = times -> tm_mon + 1;           // Indexed at 0
    int day = times -> tm_mday;

    std::string strYear = std::to_string(year).substr(2);
    std::string strMon = zeroize(mon);
    std::string strDay = zeroize(day);

    bool isExpired(std::string date) {
        return manager._dateGreaterThan(date, strMon + "/" + strDay + "~" + strYear) == 1;            // If the current date is greater than the "expired" date
    }

    void resetDates() {
        year = times -> tm_year + 1900;
        mon = times -> tm_mon + 1;
        day = times -> tm_mday;

        strYear = std::to_string(year).substr(2);
        strMon = zeroize(mon);
        strDay = zeroize(day);
    }

    void addToDate(double days, int months, int years) {
        day += days;
        if (day > monthDays[mon-1]) {
            day -= monthDays[mon-1];
            mon ++;
        }
        if (mon > 12) {
            year ++;
            mon -= 12;
        }

        strYear = std::to_string(year).substr(2);
        strMon = zeroize(mon);
        strDay = zeroize(day);

        mon += months;
        if (mon > 12) {
            year ++;
            mon -= 12;
        }

        strYear = std::to_string(year).substr(2);
        strMon = zeroize(mon);
        strDay = zeroize(day);

        year += years;
    }

    void listItems(bool inOrder = false, bool expired = false) {
        unsigned int amtOItems = 0;
        std::cout << "\nName                                       Expiration Date                                 Group" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
        if (manager.length == 1) {
            std::cout << manager.names[0];
            for (int i = manager.names[0].length(); i < 45; i ++) {
                std::cout << " ";
            }
            amtOItems ++;
            std::cout << zeroize(manager.dates[0][0]) << "/" << zeroize(manager.dates[0][1]) << "/" << zeroize(manager.dates[0][2]) << "                                          " <<  locationStr(manager.loc[0]) << "\n" << std::endl;
            std::cout << "\nListing " << amtOItems << " items." << std::endl;
            return;
        }
        else if (manager.length == 0) {
            std::cout << "No items in list!!!\n" << std::endl;
            return;
        } 

        if (inOrder) {
            int parse, tmpGroup;
            std::string d, g;
            std::string tmpName, tmpDate;
            std::string theItems = manager.sortDates();
            parse = 0;
            for (int x = 0; x < manager.length; x ++) {
                d = "";
                g = "";
                tmpName = "";
                tmpDate = "";
                while (!(theItems[parse] == '*')) {
                    tmpName += theItems[parse];
                    parse ++;
                }
                parse ++;
                while ((theItems[parse] != '`')) {
                    d += theItems[parse];
                    parse ++;
                }
                parse ++;

                tmpDate = d.substr(0, 2) + "/" + d.substr(2, 2) + "/" + d.substr(4);
                
                while ((theItems[parse] != '/')) {
                    g += theItems[parse];
                    parse ++;
                }
                tmpGroup = std::stoi(g);
                parse ++;
                
                if (!expired) {
                    amtOItems ++;
                    std::cout << tmpName;

                    int len = 43-tmpName.length();
                    for (int y = 0; y < len; y ++) {
                        std::cout << " ";
                    }

                    if (tmpDate == "99/99/99") {
                        std::cout << "????????";
                    }
                    else {
                        std::cout << tmpDate;
                    }
                    std::cout << "                                        " << locationStr(tmpGroup) << std::endl;
                    std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
                }
                else {
                    if (tmpDate == "99/99/99") {

                    }
                    else {
                        if (isExpired(tmpDate.substr(0, 2) + "/" + tmpDate.substr(3, 2) + "~" + tmpDate.substr(6))) {
                            amtOItems ++;
                            std::cout << tmpName;

                            int len = 43-tmpName.length();
                            for (int y = 0; y < len; y ++) {
                                std::cout << " ";
                            }

                            std::cout << tmpDate << "                                        " << locationStr(tmpGroup) << std::endl;
                            std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
                        }
                    }
                }
            }
            std::cout << std::endl << "Listing " << amtOItems << " items." << std::endl;
        }
        else {
            for (int x = 0; x < manager.length; x ++) {
                std::cout << manager.names[x];
                int len = 40-manager.names[x].length();
                for (int y = 0; y < len; y ++) {
                    std::cout << " ";
                }
                std::cout << zeroize(manager.dates[x][0]) << "/" << zeroize(manager.dates[x][1])
                   << "/" << zeroize(manager.dates[x][2]);
            
                std::cout << "                                        "  << locationStr(manager.loc[x]) << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void remove() {
        std::string name, q;
        std::cout << "\nEnter the name for the item being deleted: ";
        std::getline(std::cin, name);
        std::cout << "Enter in the quantity of items to delete:  ";
        std::getline(std::cin, q);

        if (manager._amoumtOf(name) < std::stoi(q) ) {
            std::cout << "Not enough of that item!" << std::endl;
        }
        else {
            for (int x = 0; x < std::stoi(q); x ++) {
                manager.removeItem(name);
            }
            manager.writeToFile();
            std::cout << "Item(s) '" << name << "' has/have been deleted!\n" << std::endl;
        }
    }

    void add() {
        std::string name, quan, mon, day, year, group;
        short g;
        
        std::cout << "\nEnter in the name:  ";
        std::getline(std::cin, name);

        std::cout << "Enter in the quantity:  ";
        std::getline(std::cin, quan);
        while (!isInt(quan)) {
            std::cout << "Invalid quantity!" << std::endl;
            sleep(1);
            std::cout << "Enter in the quantity:  ";
            std::getline(std::cin, quan);
        }

        std::cout << "Enter in the month:  ";
        std::getline(std::cin, mon);
        while (!isInt(mon)) {
            std::cout << "Invalid month!" << std::endl;
            sleep(1);
            std::cout << "Enter in the month:  ";
            std::getline(std::cin, mon);
        }

        std::cout << "Enter in the day:  ";
        std::getline(std::cin, day);
        while (!isInt(day)) {
            std::cout << "Invalid day!" << std::endl;
            sleep(1);
            std::cout << "Enter in the day:  ";
            std::getline(std::cin, day);           
        }

        std::cout << "Enter in the year:  ";
        std::getline(std::cin, year);
        while (!isInt(year)) {
            std::cout << "Invalid year!" << std::endl;
            std::cout << "Enter in the year:  ";
            std::getline(std::cin, year);        
        }
        
        std::cout << "Enter in the group (i.e. A1, B3):  ";
        std::getline(std::cin, group);

        if (mon != "??") {
            g = locationId(group);
            mon = zeroize(std::stoi(mon));
            day = zeroize(std::stoi(day));
            year = zeroize(std::stoi(year));
        }
        
        for (int x = 0; x < std::stoi(quan); x ++) {
            manager.addItem(name, mon, day, year.substr(year.length()-2), g);
        }
        std::cout << "Item(s) added!" << std::endl;
    }

    void search() {
        std::string r;
        std::cout << "Enter in a keyword: ";
        std::getline(std::cin, r);
        int total = 0;
        std::cout << "\nName                                       Expiration Date                                 Group" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
        for (int l = 0; l < manager.length; l ++) {
            if (manager.checkForKeyword(r, l)) {
                //std::cout << "Keyword found" << std::endl;
                total ++;
                std::cout << manager.names[l];
                int len = 43-r.length();
                for (int y = 0; y < len; y ++) {
                    std::cout << " ";
                }
                std::string tmpDate = zeroize(manager.dates[l][0]) + "/" + zeroize(manager.dates[l][1]) + "/" + zeroize(manager.dates[l][2]);
                if (tmpDate == "99/99/99") {
                    std::cout << "????????";
                }
                else {
                    std::cout << tmpDate;
                }
                std::cout << "                                        " << locationStr(manager.loc[l]) << std::endl;
                std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
            }
        }
        if (total == 0) {
            std::cout << "No items to show!" << std::endl;
        }
    }
public:
    Interface() {
        if (mon < 10) {
            strMon = "0" + strMon;
        }
        if (day < 10) {
            strDay = "0" + strDay;
        }
    }

    void help() {
        std::cout << "--------------------------------------------------\n";
        std::cout << "\tList of commands:" << std::endl;
        std::cout << "\nadd item: Adds an item.\n\nlist items: Sorts and prints out all items in the file.\n\nremove item: Removes an item from the file.\n\nlist expired: Lists all expired items.\n\nwill expire: Shows items expiring in a certain\namount of time.\n " << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
    }

    void loop() {
        std::string command;
        std::cout << "-> ";
        std::getline(std::cin, command);

        if (command == "help") {
            system("clear");
            help();
        }
        else if (command == "add item") {
            manager._loadFile();
            system("clear");
            add();
        }
        else if (command == "list expired") {
            manager._loadFile();
            system("clear");
            resetDates();
            listItems(true, true);
        }
        else if (command == "list items") {
            manager._loadFile();
            system("clear");
            resetDates();
            listItems(true);
        }
        else if (command == "remove item") {
            system("clear");
            remove();
        }
        else if (command == "will expire") {
            std::string d, m, y;
            std::cout << "Enter a timespan (in days):  ";
            std::getline(std::cin, d);
            std::cout << "Enter a timespan (in months):  ";
            std::getline(std::cin, m);
            std::cout << "Enter a timespan (in years):  ";
            std::getline(std::cin, y);
            addToDate(std::stoi(d), std::stoi(m), std::stoi(y));

            system("clear");

            listItems(true, true);
        }
        else if (command == "clear") {
            system("clear");
        }
        else if (command == "search items") {
            search();
        }
        else {
            std::cout << "Command not recognized!\n" << std::endl;
            sleep(1);
            system("clear");
            help();
        }
    }
};
#endif
