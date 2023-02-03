#include <iostream>
#include "FoodInterface.hpp"

using namespace std;

int main() {
    string what;
    cout << "Enter something: ";
    cin >> what;
    cout << "This is what you typed: " << what << std::endl;
    return 0;
}