/* The interface and TUI for the app */
#pragma once

#include <unistd.h>
#include <ctime>
#include "FoodManager.hpp"

class Interface {
    FoodManager manager;

    time_t curr = time(0);
    tm* times = localtime(&curr);

    int year = times -> tm_year + 1900;            // tm_year returns the year starting from 1900
    int mon = times -> tm_mon + 1;           // Indexed at 0
    int day = times -> tm_mday;

    Date currentDate {mon, day, year};

    bool isExpired(Date date) {
        return currentDate > date;            // If the current date is greater than the "expired" date
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
        manager.loadFile();
        unsigned int amtOItems = 0;
        std::cout << std::endl << "Name                                       Expiration Date                                  Group                                       Amount" << std::endl;
        std::cout <<              "-----------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        if (manager.names.size() == 1) {
            printItem(manager.names[0], manager.dates[0], manager.loc[0], manager.rAmtOf[0]);
            amtOItems ++;
            std::cout << std::endl << "Listing 1 item." << std::endl;
            return;
        }
        if (manager.names.size() == 0) {
            std::cout << "No items in list!!!" << std::endl << std::endl;
            return;
        } 

        if (inOrder) {
            std::string tmpName, tmpDate;
            int tmpGroup, tmpAmt;
            std::string theItems = manager.sortDates();
            for (unsigned long x = 0; x < manager.names.size(); x ++) { 
                tmpName = strSplit(theItems, "  ", x * 4);
                tmpDate = strSplit(theItems, "  ", x * 4 + 1);
                tmpGroup = std::stoi(strSplit(theItems, "  ", x * 4 + 2));
                tmpAmt = std::stoi(strSplit(strSplit(theItems, "r=", x + 1), "  ", 0));

                int pm = std::stoi(strSplit(tmpDate, "/", 0));
                int pd = std::stoi(strSplit(tmpDate, "/", 1));
                int py = std::stoi(strSplit(tmpDate, "/", 2));
    
                if (!expired) {
                    amtOItems ++;
                    printItem(tmpName, {pm, pd, py}, tmpGroup, tmpAmt);
                }
                else {
                    if (tmpDate != "99/99/99") {
                        if (isExpired({pm, pd, py})) {
                            amtOItems ++;
                            printItem(tmpName, {pm, pd, py}, tmpGroup, tmpAmt);
                        }
                    }
                }
            }
            std::cout << std::endl << "Listing " << amtOItems << " items" << std::endl;
        }
        else {
            for (unsigned long x = 0; x < manager.names.size(); x ++) {
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
        int q = getInt("Enter the amount of items to delete: ");

        if (manager.amountOf(name) > 1) {
            std::vector<Date> uniqueDates;
            std::cout << std::endl << "There are multiple kinds of that item. Select which item to delete." << std::endl << std::endl;
            std::vector<Info> items = manager.getUniqueItems(name);
            for (int i = 0; i < manager.amountOf(name); i ++) {
                uniqueDates.push_back(items[i].date);
                std::cout << "(" << i << ")" << "  " << name << " (" << items[i].amt << ") : " << items[i].date.getStrDate() << std::endl;
            }
            std::cout << std::endl;
            unsigned int resp = getInt("Enter in the one to edit: ");
            while (resp > items.size() || resp < 0) {
                std::cout << "Invalid option!" << std::endl;
                resp = getInt("Enter in the one to edit: ");
            }
            
            manager.removeAmtOfItem({name, items[resp].date, items[resp].loc, items[resp].amt}, q, resp);
        }
        else {
            //for (int x = 0; x < std::stoi(q); x ++) {
                //manager.removeItem(name, manager.getUniqueDatesFromName(name, 0));
            //}
        }
        std::cout << "Removed item(s) '" << name << "'!" << std::endl;
    }

    void add() {
        std::string name, group;
        int mon, day, year, quan, g, amt;
        
        std::cout << std::endl;
        name =  getLine("Enter in the name:  ");
        quan =  getInt("Enter in the quantity:  ");
        mon =   getInt("Enter in the month: ");
        day =   getInt("Enter in the day: ");
        year =  getInt("Enter in the year: ");
        amt = getInt("Enter in the amount of items: ");
        group = getLine("Enter in the group (i.e. A1, B3):  ");
        
        Date addDate {mon, day, year, false};
        
        g = locationId(group);
        for (int x = 0; x < quan; x ++) {
            manager.addItem(name, addDate, g, amt);
        }
        std::cout << "Item(s) added!" << std::endl;
    }

    void search() {
        std::string r;
        r = getLine("Enter in a keyword: ");
        int total = 0;
        system("clear");
        std::cout << std::endl;
        std::cout << "Name                                       Expiration Date                                  Group                                       Amount" << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        for (unsigned long l = 0; l < manager.names.size(); l ++) {
            if (manager.checkForKeyword(r, l)) {
                total ++;
                printItem(manager.names[l], manager.dates[l], manager.loc[1], manager.rAmtOf[l]);
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
            manager.loadFile();
            add();
        }
        else if (command == "list expired") {
            manager.loadFile();
            resetDates();
            listItems(true, true);
        }
        else if (command == "list items") {
            manager.loadFile();
            system("clear");
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

            resetDates();
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