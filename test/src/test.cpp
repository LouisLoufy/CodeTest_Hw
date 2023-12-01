#include <iostream>
#include <queue>
#include <string>

std::string result(std::string post, std::string mid) {
    if (post.empty() || mid.empty()) {
        return ""; // 处理空序列的情况
    }

    std::queue<std::pair<std::string, std::string>> queue;
    std::string ans;

    queue.push({post, mid});

    while (!queue.empty()) {
        std::string postSubtree = queue.front().first;
        std::string midSubtree = queue.front().second;
        queue.pop();

        char root = postSubtree.back();
        ans.push_back(root);

        size_t rootIdx = midSubtree.find(root);
        std::string leftPost, leftMid, rightPost, rightMid;

        if (rootIdx != 0 && rootIdx != std::string::npos) {
            leftPost = postSubtree.substr(0, rootIdx);
            leftMid = midSubtree.substr(0, rootIdx);
            queue.push({leftPost, leftMid});
        }

        if (rootIdx != midSubtree.size() - 1 && rootIdx != std::string::npos) {
            rightPost = postSubtree.substr(rootIdx, postSubtree.size() - rootIdx - 1);
            rightMid = midSubtree.substr(rootIdx + 1);
            queue.push({rightPost, rightMid});
        }
    }

    return ans;
}

int main() {
    std::string post, mid;
    std::cin >> post >> mid;
    std::cout << result(post, mid) << std::endl;
    return 0;
}
