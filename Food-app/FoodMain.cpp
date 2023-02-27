#include <iostream>

#ifndef INTER_HPP
#include "FoodInterface.hpp"
#endif

int main() {
    FoodManager food_manager;
    Interface inter;
    inter.help();
    while (1) {
        inter.loop();
    }
    return 0;
}