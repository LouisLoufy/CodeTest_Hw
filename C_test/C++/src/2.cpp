#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 自定义排序函数
std::pair<std::string, int> custom_sort(std::string s) {
    // 将字符串划分为两部分来进行排序
    return std::make_pair(s.substr(0, 2), std::stoi(s.substr(4)));
}

int main() {
    std::string s;
    // 读取一行输入并保存在变量s
    std::getline(std::cin, s);
    std::vector<std::string> input_data;
    size_t                   pos = 0;
    std::string              token;
    // 将输入的字符串按逗号分隔成一个列表 input_data
    while ((pos = s.find(",")) != std::string::npos) {
        token = s.substr(0, pos);
        input_data.push_back(token);
        s.erase(0, pos + 1);
    }
    input_data.push_back(s);

    // 调用自定义排序函数 custom_sort，对 input_data 列表进行排序
    std::sort(input_data.begin(), input_data.end(),
              [](const std::string &a, const std::string &b) { return custom_sort(a) < custom_sort(b); });

    // 将排序后的列表转换为一个字符串，每个元素之间用逗号分隔打印输出
    for (size_t i = 0; i < input_data.size(); ++i) {
        std::cout << input_data[i];
        if (i != input_data.size() - 1) {
            std::cout << ",";
        }
    }

    return 0;
}
