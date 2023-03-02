/*  Helper functions used globally  */

#pragma once

int monthDays[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

char lets[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

std::string getLine(std::string printout = "") {
    std::string ret;
    std::cout << printout;
    std::getline(std::cin, ret);
    return ret;
}

bool isInt(std::string num) {               // Checks if a string is a number or not
    int counter;
    for (int i = 0; i < (int)num.length(); i ++) {
        counter = 0;
        for (int z = 0; z < 10; z ++) {
            if (num[i] != nums[z]) {
                counter ++;
            }
            else {
                break;
            }
        }
        if (!(counter < 10)) {
            return false;
        }
    }
    return true;
}

std::string zeroize(int num) {           // Turns '7' into '07'
    if (num < 10){
        return "0" + std::to_string(num);
    }
    return std::to_string(num);
}

char lowercase(char let) {
    int letloc;
    for (int i = 0; i < 52; i ++) {
        if (lets[i] == let) {
            letloc = i;
            break;
        }
    }

    if (letloc < 26) {
        return lets[letloc];
    }
    return lets[letloc-26];
}

char capitalize(char let) {
    int letloc;
    for (int i = 0; i < 52; i ++) {
        if (lets[i] == let) {
            letloc = i;
            break;
        }
    }

    if (letloc > 25) {
        return lets[letloc];
    }
    return lets[letloc+26];
}

short locationId(std::string num) {
    char ids[4] = {'A', 'B', 'C', 'D'};
    short ret;

    for (int i = 0; i < 4; i ++) {
        if (num[0] == ids[i]) {
            ret = (i*4);
            break;
        }
    }

    ret += std::stoi(num.substr(1));
    return ret;
}

std::string locationStr(short num) {
    if (num < 5) {
        return "A" + std::to_string(num);
    }
    else if (num < 9) {
        return "B" + std::to_string(num-4);
    }
    else if (num < 13) {
        return "C" + std::to_string(num-8);
    }
    else {
        return "D" + std::to_string(num-12);
    }
    return "";
}

std::string strCut(std::string str) {               // Makes "    Hello, world! " == "Hello, world! "
    std::string ret;
    int blankChars = 0; 
    for (int x = 0; x < (int)str.length(); x ++) {
        if (str[x] != ' ') {
            break;
        }
        blankChars ++; 
    }
    for (int x = blankChars; x < (int)str.length(); x ++) {
        ret += str[x];
    }
    return ret;
}

int getInt(std::string message) {
    std::string s = getLine(message);
    while (!isInt(s)) {
        if (s == "??") {
            return 99;
        }
        std::cout << "Invalid number!" << std::endl;
        sleep(1);
        s = getLine(message);
    }
    return std::stoi(s);
}

int splitAmt(std::string str, std::string splitPoint) {
    int total = 1;
    for (int x = 0; x < (int)str.length(); x ++) {
        for (int y = 0; y < (int)splitPoint.length(); y ++) {
            if (str[x+y] != splitPoint[y]) {
                break;
            }
            if (y == (int)splitPoint.length()-1) {
                total ++;
            }
        }
    }
    return total;
}

std::string strSplit(std::string str, std::string splitPoint, int s) {           // Splits a string and returns whatever index you want it to be
    int total = -1;
    std::string curr = "";
    for (int x = 0; x < (int)str.length(); x ++) {
        for (int y = 0; y < (int)splitPoint.length(); y ++) {
            if (str[x+y] != splitPoint[y]) {
                break;
            }
            if (y == (int)splitPoint.length()-1) {
                total ++;
                x += (int)splitPoint.length();
                if (total == s) {
                    return curr;
                }
                curr = "";
            }
        }
        curr += str[x];
    }
    return curr;
}

struct Date {
    int m_m;
    int m_d;
    int m_y;  
    int m_array[3];

    Date(int m = 0, int d = 0, int y = 0, bool evenize = true) {
        m_m = m;
        m_d = d;
        m_y = y;
        m_array[0] = m_m;
        m_array[1] = m_d;
        m_array[2] = m_y;
        if (m_d > monthDays[m_m - 1] && evenize) {
            m_d -= monthDays[m_m - 1];
            m_m ++;
        }
        if (m_m > 12 && evenize) {
            m_m -= 12;
            m_y ++;
        }
    }

    Date operator +(Date date) {
        Date ret {m_d + date.m_d, m_m + date.m_m, m_y + date.m_y};
        return ret;
    }

    bool operator >(Date date) {
        short order[3] {2, 0, 1};
        for (int x : order) {
            if (m_array[x] > date.m_array[x]) {
                return true;
            }
            else if (m_array[x] < date.m_array[x]) {
                return false;
            }
        }
        return false;
    }

    bool operator ==(Date date) {
        return (m_m == date.m_m && m_d == date.m_d && m_y == date.m_y);
    }

    std::string mon_str() {
        return zeroize(m_m);
    }

    std::string day_str() {
        return zeroize(m_d);
    }

    std::string year_str() {
        return zeroize(m_y);
    }

    std::string getStrDate() {
        return mon_str() + "/" + day_str() + "/" + year_str();
    }

    void set_m(int n) {
        m_m = n;
    }

    void set_d(int n) {
        m_d = n;
    }

    void set_y(int n) {
        m_y = n;
    }
};


void printItem(std::string name, Date date, int loc) {
    std::cout << name;
    for (int x = (int)name.length(); x < 43; x ++) {
        std::cout << " ";
    }
    
    std::cout << date.getStrDate();
    std::cout << "                                          " << locationStr(loc) << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
}