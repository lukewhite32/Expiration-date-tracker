#pragma once

#include "FoodManager.hpp"
#include <ctime>

class Interface {
    FoodManager manager;

    time_t curr = time(0);
    tm* times = localtime(&curr);

    double year = times -> tm_year + 1900;            // tm_year returns the year starting from 1900
    double mon = times -> tm_mon + 1;           // Indexed at 0
    double day = times -> tm_mday;

    std::string strYear, strMon, strDay;

    strYear = std::to_string(year).substr(2);
    strMon = std::to_string(mon);
    strDay = std::to_string(day);

    std::string stringize(std::string num) {           // Turns '7' into '07'
        if (std::stoi(num) < 10){
            return "0" + num;
        }
        return num;
    }

    void help() {
        std::cout << "---------------------------------"
        std::cout << "\tList of commands:" << std::endl;
        std::cout << "\nadd item: Brings up a menu for you\nto add an item.\nexp <days>: Prints out items that expire within that\ntime period." << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }

    void listItems() {
        std::cout << "Name                    Expiration Date                    Group" << std::endl;
        for (int x = 0; x < food_manager.length; x ++) {
            std::cout << food_manager.names[x];
            for (int x = 0; x < food_manager.names[x].length(); x ++) {
                std::cout << " ";
            }
            std::cout << food_manager.stringize(std::to_string(food_manager.dates[x][0])) << "/" << food_manager.stringize(std::to_string(food_manager.dates[x][1]))
               << "/" << food_manager.stringize(std::to_string(food_manager.dates[x][2]));
            
            std::cout << "            "  food_manager.location(food_manager.loc[x]) << std::endl;
        }
    }

    void listItemsInOrder() {

    }

    void listExpired() {

    }

    void add() {
        std::string name, mon, day, year, group;
        short g;

        std::cout << "Enter in the name (no '~' or '-):  ";
        std::cin >> name;
        std::cout << "Enter in the month:  ";
        std::cin >> mon;
        std::cout << "Enter in the day:  ";
        std::cin >> day;
        std::cout << "Enter in the year:  ";
        std::cin >> year;
        std::cout << "Enter in the group (i.e. A1, B3):  ";
        std::cin >> group;

        g = locId(group);
        mon = stringize(mon);
        day = stringize(day);
        year = stringize(year);

        manager.addItem(name, mon, day, year.substr(2), g);
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

    std::string listen() {
        std::string ret;   
        std::cout << "-> ";
        std::cin >> ret;
        return ret;
    }

    void listExpired() {

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
            listItems();
        }
        else if (command == "remove item") {

        }
        else {
            std::cout << "Command not recognized!" << std::endl;
            help();
        }
    }
};