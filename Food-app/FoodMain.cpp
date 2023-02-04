#include <iostream>
#include "FoodInterface.hpp"

int main() {
    FoodManager food_manager;
    Interface inter;
    inter.help();
    while (1) {
        inter.loop();
    }
    return 0;
}