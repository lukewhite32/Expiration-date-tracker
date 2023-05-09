#include <iostream>

#include "FoodInterface.hpp"

int main() {
    Interface inter;
    inter.help();
    while (1) {
        inter.loop();
    }
    return 0;
}