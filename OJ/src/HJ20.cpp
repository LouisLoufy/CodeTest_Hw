#include "dbg.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

bool checkPassword(const std::string &password) {
    // 长度超过8位
    if (password.length() < 8) {
        return false;
    }

    // 包括大小写字母.数字.其它符号,以上四种至少三种
    int  typesCount = 0;
    auto checkType  = [&](auto condition) { typesCount += condition; };

    std::for_each(password.begin(), password.end(), [&](char c) {
        checkType(std::isupper(c));
        checkType(std::islower(c));
        checkType(std::isdigit(c));
        checkType(!std::isalnum(c));
    });

    if (typesCount < 3) {
        return false;
    }

    // 检查是否有长度大于2的包含公共元素的子串重复
    std::unordered_set<std::string> substrings;
    for (int i = 0; i < password.length() - 2; ++i) {
        std::string subStr = password.substr(i, 3);
        if (substrings.count(subStr) > 0) {
            return false;
        }
        substrings.insert(subStr);
    }

    return true;
}

int main() {
    std::string password;
    while (std::cin >> password) {
        if (checkPassword(password)) {
            std::cout << "OK\n";
        } else {
            std::cout << "NG\n";
        }
    }
    return 0;
}