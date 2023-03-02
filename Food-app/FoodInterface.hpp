#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtrigraphs"

#include <unistd.h>
#include <ctime>

#ifndef MANAGER_HPP
#include "FoodManager.hpp"
#endif

#ifndef INTER_HPP
#define INTER_HPP

class Interface {
    FoodManager manager;

    time_t curr = time(0);
    tm* times = localtime(&curr);

    int year = times -> tm_year + 1900;            // tm_year returns the year starting from 1900
    int mon = times -> tm_mon + 1;           // Indexed at 0
    int day = times -> tm_mday;

    Date currentDate {mon, day, year};

    bool isExpired(Date date) {
        return manager._dateGreaterThan(date, currentDate) == 1;            // If the current date is greater than the "expired" date
    }

    void resetDates() {
        year = times -> tm_year + 1900;
        mon = times -> tm_mon + 1;
        day = times -> tm_mday;
    }

    void addToDate(int days, int months, int years) {
        currentDate = Date {mon + months, day + days, year + years};
    }

    void listItems(bool inOrder = false, bool expired = false) {
        unsigned int amtOItems = 0;
        std::cout << std::endl << "Name                                       Expiration Date                                 Group" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
        if (manager.length == 1) {
            printItem(manager.names[0], manager.dates[0], manager.loc[0]);
            amtOItems ++;
            std::cout << std::endl << "Listing 1 item." << std::endl;
            return;
        }
        if (manager.length == 0) {
            std::cout << "No items in list!!!" << std::endl << std::endl;
            return;
        } 

        if (inOrder) {
            int currSplit = 0;
            std::string tmpName, tmpDate;
            int tmpGroup;
            std::string theItems = manager.sortDates();
            for (int x = 0; x < manager.length; x ++) { 
                tmpName = strSplit(theItems, "  ", currSplit);
                currSplit ++;
                tmpDate = strSplit(theItems, "  ", currSplit);
                currSplit ++;
                tmpGroup = std::stoi(strSplit(theItems, "  ", currSplit));
                currSplit ++;

                int pm = std::stoi(strSplit(tmpDate, "/", 0));
                int pd = std::stoi(strSplit(tmpDate, "/", 1));
                int py = std::stoi(strSplit(tmpDate, "/", 2));
                if (!expired) {
                    amtOItems ++;
                    printItem(tmpName, {pm, pd, py, false}, tmpGroup);
                }
                else {
                    if (tmpDate != "99/99/99") {
                        if (isExpired({pm, pd, py})) {
                            amtOItems ++;
                            std::cout << tmpName;

                            int len = 43-(int)tmpName.length();
                            for (int y = 0; y < len; y ++) {
                                std::cout << " ";
                            }

                            std::cout << tmpDate << "                                        " << locationStr(tmpGroup) << std::endl;
                            std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
                        }
                    }
                }
            }
            std::cout << std::endl << "Listing " << amtOItems << " items" << std::endl;
        }
        else {
            for (int x = 0; x < manager.length; x ++) {
                std::cout << manager.names[x];
                int len = 40-(int)manager.names[x].length();
                for (int y = 0; y < len; y ++) {
                    std::cout << " ";
                }
                std::cout << manager.dates[x].getStrDate();
            
                std::cout << "                                        "  << locationStr(manager.loc[x]) << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void remove() {
        std::string name = getLine("Enter the name for the item to delete: ");
        std::string q = getLine("Enter the amount of items to delete: ");

        if (manager.getAmtUniqueTypes(name) > 1) {
            Date uniqueDates[manager.getAmtUniqueTypes(name)];
            std::cout << std::endl << "There are multiple kinds of that item. Select which item to delete." << std::endl << std::endl;
            for (int i = 0; i < manager.getAmtUniqueTypes(name); i ++) {
                uniqueDates[i] = manager.getUniqueDatesFromName(name, i);
                std::cout << "(" << i << ")" << "  " << name << " (" << manager._amountOf(name, uniqueDates[i]) << ") : " << manager.getUniqueDatesFromName(name, i).getStrDate() << std::endl;
            }
            std::cout << std::endl;
            int resp = std::stoi(getLine("Enter in the one to edit: "));
            while (resp > manager.getAmtUniqueTypes(name) || resp < 0) {
                std::cout << "Invalid option!" << std::endl;
                resp = std::stoi(getLine("Enter in the one to edit: "));
            }
            for (int x = 0; x < std::stoi(q); x ++) {
                manager.removeItem(name, uniqueDates[resp]);
            }
        }
        else {
            for (int x = 0; x < std::stoi(q); x ++) {
                manager.removeItem(name, manager.getUniqueDatesFromName(name, 0));
            }
        }
        std::cout << "Removed item(s) '" << name << "'!" << std::endl;
    }

    void add() {
        std::string name, group;
        int mon, day, year, quan, g;
        
        std::cout << std::endl;
        name =  getLine("Enter in the name:  ");
        quan =  getInt("Enter in the quantity:  ");
        mon =   getInt("Enter in the month: ");
        day =   getInt("Enter in the day: ");
        year =  getInt("Enter in the year: ");
        group = getLine("Enter in the group (i.e. A1, B3):  ");
        
        Date addDate {mon, day, year, false};
        
        g = locationId(group);
        for (int x = 0; x < quan; x ++) {
            manager.addItem(name, addDate, g);
        }
        std::cout << "Item(s) added!" << std::endl;
    }

    void search() {
        std::string r;
        r = getLine("Enter in a keyword: ");
        int total = 0;
        system("clear");
        std::cout << std::endl;
        std::cout << "Name                                       Expiration Date                                 Group" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
        for (int l = 0; l < manager.length; l ++) {
            if (manager.checkForKeyword(r, l)) {
                total ++;
                printItem(manager.names[l], manager.dates[l], manager.loc[1]);
            }
        }
        if (total == 0) {
            std::cout << "No items to show!" << std::endl;
        }
        else {
            std::cout << std::endl << "Listing " << total << " item(s)" << std::endl << std::endl;
        }
    }
public:
    Interface() {

    }

    void help() {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "\tList of commands:" << std::endl;
        std::cout << std::endl << "add item: Adds an item." <<
        std::endl << std::endl << "list items: Sorts and prints out all items in the file." <<
        std::endl << std::endl << "remove item: Removes an item from the file." << 
        std::endl << std::endl << "list expired: Lists all expired items." << 
        std::endl << std::endl << "will expire: Shows items expiring in a certain" << std::endl << "amount of time." << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
    }

    void loop() {
        std::string command = getLine("-> ");

        if (command == "help") {
            system("clear");
            help();
        }
        else if (command == "add item") {
            manager._loadFile();
            add();
        }
        else if (command == "list expired") {
            manager._loadFile();
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
            remove();
        }
        else if (command == "will expire") {
            int d, m, y;
            d = getInt("Enter in a timespan (in days): ");
            m = getInt("Enter in a timespan (in months): ");
            y = getInt("Enter a timespan (in years): ");
            std::cout << year << std::endl;
            addToDate(d, m, y);

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
            std::cout << "Command not recognized!" << std::endl << std::endl;
            sleep(1);
            system("clear");
            help();
        }
    }
};
#pragma GCC diagnostic pop
#endif