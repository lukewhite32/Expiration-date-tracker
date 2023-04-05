/* Some beta-testing for the main file */

#include <iostream>
#include <algorithm>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <vector>

void removeFromVector(std::vector<auto> &vect, unsigned int position) {
    auto it = vect.begin() + position;
    vect.erase(it);
}

int main() {
    std::vector<int> thing;
    thing.push_back(1);
    thing.push_back(2);
    thing.push_back(3);
    thing.push_back(4);
    thing.push_back(5);
    removeFromVector(thing, 1);
    for (int x = 0; x < thing.size(); x ++) {
        std::cout << thing[x] << std::endl;
    }
    return 0;
}