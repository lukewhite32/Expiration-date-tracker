#include <iostream>

#ifndef INTER_HPP
#include "FoodInterface.hpp"
#endif

int main() {
    Interface inter;
    inter.help();
    while (1) {
        inter.loop();
    }
    return 0;
}