/* Manages the files and all the food in it */

#include <fstream>         // For file management
#include <string.h>

class FoodManager {
    std::string names[10000];
    unsigned short dates[10000][3];                   // Nested array time!      
    short loc[10000];                              // 1 = A1, 2 = A2,... 5 = B1, 6 = B2, etc.

    unsigned int length;              // The known length of the file

    int _lengthOfFile() {
        std::ifstream file {"Food-file.txt"};
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

    void _loadFile() {
        std::ifstream file {"Food-file.txt"};
        unsigned long curLine = 0;
        std::string line, dateLine;

        if ( file.is_open() ) {
            for (int x = 0; x < _lengthOfFile(); x ++) {
                std::getline(file, line);
                if (line == "") {               // If it's a blank line, it must be the end
                    break;
                }  
                names[curLine] = line.substr(0, line.find("-"));
                dateLine = line.substr(line.find("-")+1, line.find("/"));          // Where there's a hyphen, the rest is the dateline.
                loc[curLine] = std::stoi(line.substr(line.find("/")+1));

                if (dateLine == "??????") {                // This means that the expiration date is unknown
                    for (int x = 0; x < 3; x ++) {
                        for (int y = 0; y < 2; y ++) {
                            dates[curLine][x] = 99;
                        }
                    }
                }
                else {
                    short parse = 0;
                    for (int x = 0; x < 3; x ++) {
                        int tmpDate = std::stoi(dateLine.substr(parse, 2));
                        dates[curLine][x] = tmpDate;
                        parse += 2;
                    }
                }
                curLine ++;
            }
            length = curLine;
        }
        file.close();                  // If the file doesn't close properly, you can't pipe data to the file (I found this out the hard way)
    }

    int _findItem(std::string name, int startPoint = 0) {
        for (int i = startPoint; i < length; i ++) {
            if (names[i] == name) {
                return i;
            }
        }
        return -1;
    }

public:
    FoodManager() {
        _loadFile();
    }

    short locId(std::string num) {
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

    std::string location(short num) {
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

    short _dateGreaterThan(std::string date1, std::string date2) {            // 0 = both equal, 1 = date2 bigger, -1 = date1 bigger.
        int d1[] = { std::stoi(date1.substr(0, date1.find("/"))), std::stoi(date1.substr(date1.find("/")+1, date1.find("~"))), std::stoi(date1.substr(date1.find("~")+1)) };
        int d2[] = { std::stoi(date2.substr(0, date2.find("/"))), std::stoi(date2.substr(date2.find("/")+1, date2.find("~"))), std::stoi(date2.substr(date2.find("~")+1)) };

        short order[3] {2, 0, 1};
        for (int x : order) {
            if (d1[x] > d2[x]) {
                return -1;
            }
            else if (d1[x] < d2[x]) {
                return 1;
            }
        }
        return 0;
    }

    void addItem(std::string name, std::string month, std::string day, std::string year, short group) {
        std::ofstream piper;
        piper.open("Food-file.txt", std::ios::app);

        piper << name << "-" << month.substr(0, 1) << month.substr(1, 1) << day.substr(0, 1) << day.substr(1, 1) << year.substr(0, 1) << year.substr(1, 1) << "/" << group << "\n"; 
        piper.close();

        names[length] = name;
        dates[length][0] = std::stoi(month);
        dates[length][1] = std::stoi(day);
        dates[length][2] = std::stoi(year);
        loc[length] = group;

        length += 1;
    }

    bool removeItem(std::string name, int index = 0) {
        /*int loc = _findItem(name);
        if (loc == -1) {
            std::cout << "Couldn't find an item with this name!" << std::endl;
        }
        else {
            if (_findItem(name, loc) == -1) {
                return false;
            }
            //std::copy(names + loc + 1, names + length, name);
        }
	return true;*/
    }

    std::string sortDates() {                   // Returns a string of all the dates sorted, seperated by '/'
        bool over = false;
        int tmpDates[length][3];
        short tmpLocs[length];
        std::string theDates;

        for (int x = 0; x < length; x ++) {
            for (int y = 0; y < 3; y ++) {
                tmpDates[x][y] = dates[x][y];
            }
            tmpLocs[x] = loc[x];
        }

        while (!over) {
            for (int x = 0; x < length-1; x ++) {
                std::string compare1, compare2;

                //std::cout << "compare 1: " << tmpDates[x][0] << ", " << tmpDates[x][1] << ", " << tmpDates[x][2] << std::endl;
                compare1 = std::to_string(tmpDates[x][0]) + "/" + std::to_string(tmpDates[x][1]) + "~" + std::to_string(tmpDates[x][2]);
                compare2 = std::to_string(tmpDates[x+1][0]) + "/" + std::to_string(tmpDates[x+1][1]) + "~" + std::to_string(tmpDates[x+1][2]);

                if (_dateGreaterThan(compare1, compare2) == -1) {
                    int tmp[3];
                    for (int i = 0; i < 3; i ++) {
                        tmp[i] = tmpDates[x][i];
                    }
                    for (int i = 0; i < 3; i ++) {
                        tmpDates[x][i] = tmpDates[x+1][i];
                        tmpDates[x+1][i] = tmp[i];
                    }
                }
            }
            for (int x = 0; x < length-1; x ++) {
                if (_dateGreaterThan(std::to_string(tmpDates[x][0]) + "/" + std::to_string(tmpDates[x][1]) + "~" + std::to_string(tmpDates[x][2]), std::to_string(tmpDates[x+1][0]) + "/" + std::to_string(tmpDates[x+1][1]) + "~" + std::to_string(tmpDates[x+1][2])) == -1) {
                    break;
                }
                if (x == length-2) {
                    over = true;
                }
            }
        }
        for (int i = 0; i < length; i ++) {
            theDates += std::to_string(tmpDates[i][0]); 
            theDates += std::to_string(tmpDates[i][1]);
            theDates += std::to_string(tmpDates[i][2]);
            theDates += "`";
            theDates += std::to_string(tmpLocs[i]);
            if (length > 2 && i < length-1) {
                theDates += "/";
            }

        }
        return theDates;
    }
};