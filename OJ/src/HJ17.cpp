#include "dbg.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct Point {
    int x, y;

    Point()
        : x(0)
        , y(0) {}

    Point(int x, int y)
        : x(x)
        , y(y) {}
};

bool isValidCmd(const std::string &command) {
    if (command.length() <= 1 || !isalpha(command[0])) {
        return false;
    }

    for (int i = 1; i < command.length(); ++i) {
        if (!std::isdigit(command[i])) {
            return false;
        }
    }
    return true;
}

void process(const std::string &input, Point &result) {
    std::istringstream iss(input);
    std::string        cmd;
    while (std::getline(iss, cmd, ';')) {  
        if (isValidCmd(cmd)) {
            dbg(cmd);
            switch (cmd[0]) {
            case 'A':
                result.x -= std::stoi(cmd.substr(1));
                break;
            case 'D':
                result.x += std::stoi(cmd.substr(1));
                break;
            case 'W':
                result.y += std::stoi(cmd.substr(1));
                break;
            case 'S':
                result.y -= std::stoi(cmd.substr(1));
                break;
            default:
                break;
            }
        }
    }
}
int main() {
    std::string input;
    Point       finalPosition;
    while (std::cin >> input) {
        process(input, finalPosition);
        std::cout << finalPosition.x << "," << finalPosition.y << "\n";
    }

    return 0;
}