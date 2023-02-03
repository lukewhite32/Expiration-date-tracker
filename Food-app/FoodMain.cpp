#include <iostream>
#include "FoodManager.hpp"

int main() {
    FoodManager food_manager;
    Interface inter;
    food_manager.addItem("Mac 'n' cheese", "12", "22", "26", 5);
    food_manager.addItem("Deez nuts", "54", "21", "28", 12);
    food_manager.addItem("Even better", "56", "76", "27", 2);
    std::string tests = food_manager.sortDates();
    std::cout << "\n\nThese are the sorted dates:" << "\n" << tests << std::endl;
    while (1) {
        inter.loop();
    }
    return 0;
}