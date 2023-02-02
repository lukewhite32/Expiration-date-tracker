#include "FoodManager.hpp"

int main() {
    FoodManager food_manager;
    food_manager.addItem("Mac 'n' cheese", "12", "22", "26", 5);
    food_manager.addItem("Deez nuts", "54", "21", "28", 12);
    food_manager.addItem("Even better", "56", "76", "27", 2);
    std::cout << "These are the items:" << std::endl;
    food_manager.printDates();
    std::string tests = food_manager.sortDates();
    std::cout << "\n\nThese are the sorted dates:" << "\n" << tests << std::endl;
    return 0;
}