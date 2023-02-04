#pragma once

#include "FoodManager.hpp"
#include <ctime>
#include <unistd.h>

class Interface {
    FoodManager manager;

    time_t curr = time(0);
    tm* times = localtime(&curr);

    double year = times -> tm_year + 1900;            // tm_year returns the year starting from 1900
    double mon = times -> tm_mon + 1;           // Indexed at 0
    double day = times -> tm_mday;

    std::string strYear = std::to_string(year).substr(2);
    std::string strMon = std::to_string(mon);
    std::string strDay = std::to_string(day);

    void listItems(bool inOrder = false) {
        std::cout << "\nName                    Expiration Date                    Group" << std::endl;
        std::cout << " ----------------------------------------------------------------" << std::endl;

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

                tmpDate = d.substr(0, 2) + d.substr(2, 2) + d.substr(4);
                
                while ((theItems[parse] != '/')) {
                    g += theItems[parse];
                    parse ++;
                }
                
                tmpGroup = std::stoi(g);

                std::cout << tmpName;
                
                int len = 24-tmpName.length();
                for (int y = 0; y < len; y ++) {
                    std::cout << " ";
                }


                parse ++;
                std::cout << tmpDate << "                           " << manager.location(tmpGroup) << std::endl;
            }
        }
        else {
            for (int x = 0; x < manager.length; x ++) {
                std::cout << manager.names[x];
                int len = 24-manager.names[x].length();
                for (int y = 0; y < len; y ++) {
                    std::cout << " ";
                }
                std::cout << manager.stringize(std::to_string(manager.dates[x][0])) << "/" << manager.stringize(std::to_string(manager.dates[x][1]))
                   << "/" << manager.stringize(std::to_string(manager.dates[x][2]));
            
                std::cout << "                           "  << manager.location(manager.loc[x]) << std::endl;
            }
        }
    }

    void listExpired() {

    }

    void remove() {
        std::string name;
        std::cout << "Enter the name for the item being deleted: ";
        std::getline(std::cin, name);
        manager.removeItem(name);
        manager.writeToFile();
        std::cout << "Item '" << name << "' has been deleted!" << std::endl;
    }

    void add() {
        std::string name, mon, day, year, group;
        short g;

        std::cout << "Enter in the name (no '~' or '-):  ";
        std::getline(std::cin, name);
        std::cout << "Enter in the month:  ";
        std::getline(std::cin, mon);
        std::cout << "Enter in the day:  ";
        std::getline(std::cin, day);
        std::cout << "Enter in the year:  ";
        std::getline(std::cin, year);
        std::cout << "Enter in the group (i.e. A1, B3):  ";
        std::getline(std::cin, group);

        g = manager.locId(group);
        mon = manager.stringize(mon);
        day = manager.stringize(day);
        year = manager.stringize(year);

        manager.addItem(name, mon, day, year.substr(year.length()-2), g);
        std::cout << "Item added!" << std::endl;
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

    bool isExpired(std::string date) {
        return manager._dateGreaterThan(date, strMon + "/" + strDay + "~" + strYear) == 1;            // If the current date is greater than the "expired" date
    }

    void help() {
        std::cout << "---------------------------------\n";
        std::cout << "\tList of commands:" << std::endl;
        std::cout << "\nadd item: Brings up a menu for you\nto add an item.\n\nlist items: Prints out all items in the file." << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }

    std::string listen() {
        std::string ret;   
        std::cout << "-> ";
        std::getline(std::cin, ret);
        return ret;
    }

    void loop() {
        std::string command = listen();
        
        if (command == "help") {
            help();
        }
        else if (command == "add item") {
            add();
        }
        else if (command == "list expired") {
            listExpired();
        }
        else if (command == "list items") {
            char ans;
            std::cout << "Would you like the dates in order?  ";
            std::cin >> ans;
            if (ans == 'y' || ans == 'Y') {
                listItems(true);
            }
            else {
                listItems();
            }
        }
        else if (command == "remove item") {
            remove();
        }
        else if (command == "clear") {
            system("clear");
        }
        else {
            std::cout << "Command not recognized!\n" << std::endl;
            sleep(1);
            help();
        }
    }
};