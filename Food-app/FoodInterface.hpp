#pragma once

#include "FoodManager.hpp"
#include <ctime>
#include <iostream>

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

    
};