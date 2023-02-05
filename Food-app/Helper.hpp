/*  Helper functions used globally  */

#pragma once

int _lengthOfFile(std::string f) {
    std::ifstream file {f};
    std::string line;
    int len = 0;
    if (file.is_open()) {
        while (file.peek() != EOF) {
            std::getline(file, line);
            len ++;
        }
    }
    file.close();
    return len;
}

double toInt(std::string num) {
    /*int nums[10]

    return std::stoi(num);*/
    return 0;
}