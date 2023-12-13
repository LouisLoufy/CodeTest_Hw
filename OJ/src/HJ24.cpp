#include "dbg.h"

#include <iostream>
#include <vector>

int process(std::vector<int> &height) {
    if (height.empty()) {
        return 0;
    }

    int              n = height.size();
    std::vector<int> up(n, 1), down(n, 1);

    // 计算以每个索引结尾的递增子序列长度
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (height[i] > height[j]) {
                up[i] = std::max(up[j] + 1, up[i]);
            }
        }
    }

    // 计算以每个索引开始的递减子序列长度
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j > i; --j) {
            if (height[j] < height[i]) {
                down[i] = std::max(down[j] + 1, down[i]);
            }
        }
    }

    dbg(up, down);

    // 计算每个索引上的合唱队人数
    int res = INT32_MIN;
    for (int i = 0; i < n; ++i) {
        res = std::max(res, up[i] + down[i] - 1);
    }

    return n - res;
}

int main() {
    int n;
    while (std::cin >> n) {
        int              h;
        std::vector<int> height(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> h;
            height[i] = h;
        }
        std::cout << process(height) << "\n";
    }

    return 0;
}