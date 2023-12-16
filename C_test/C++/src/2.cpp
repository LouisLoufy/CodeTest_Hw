#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// 自定义排序函数
std::pair<std::string, int> custom_sort(std::string s) {
    // 将字符串划分为两部分来进行排序
    return std::make_pair(s.substr(0, 2), std::stoi(s.substr(4)));
}

std::vector<std::string> process(std::string &s) {
    // 将输入的字符串按逗号分隔成一个列表 num
    std::vector<std::string> num;
    int                      pos = 0;
    std::string              token;
    while ((pos = s.find(",")) != std::string::npos) {
        token = s.substr(0, pos);
        num.push_back(token);
        s.erase(0, pos + 1);
    }
    num.push_back(s);

    // 调用自定义排序函数 custom_sort，对 num 列表进行排序
    std::sort(num.begin(), num.end(),
              [](const std::string &a, const std::string &b) { return custom_sort(a) < custom_sort(b); });
    return num;
}

void test() {
    // 标准测试
    {
        std::string              input    = "CZ6678,CA3385,SC6508,DU7523,HK4456,MK0987";
        std::vector<std::string> expected = {"CA3385", "CZ6678", "DU7523", "HK4456", "MK0987", "SC6508"};
        std::vector<std::string> result   = process(input);
        assert(result == expected);
    }

    // 标准测试
    {
        std::string              input    = "*Z6678,&A3385,$C6508,DU7523,HK4456,MK0987";
        std::vector<std::string> expected = {"$C6508", "&A3385", "*Z6678", "DU7523", "HK4456", "MK0987"};
        std::vector<std::string> result   = process(input);
        assert(result == expected);
    }

    std::cout << "test passed\n";
}

int main() {
    test();

    // 读取一行输入并保存在变量s
    std::string s;
    std::getline(std::cin, s);

    std::vector<std::string> result = process(s);

    // 将排序后的列表转换为一个字符串，每个元素之间用逗号分隔打印输出
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i];
        if (i != result.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "\n";

    return 0;
}
