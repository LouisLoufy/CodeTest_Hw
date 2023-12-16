#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

struct Node {
    int                   weight;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int w)
        : weight(w)
        , left(nullptr)
        , right(nullptr) {}
};

// 构建Huffman树
std::shared_ptr<Node> huffman_tree(const std::vector<int> &data) {
    if (data.empty()) {
        return {};
    }

    std::vector<std::shared_ptr<Node>> nodes;
    for (int weight : data) {
        nodes.push_back(std::make_shared<Node>(weight));
    }

    while (nodes.size() > 1) {
        std::sort(nodes.begin(), nodes.end(),
                  [](const auto &a, const auto &b) { return a->weight < b->weight; });

        auto left  = std::move(nodes[0]);
        auto right = std::move(nodes[1]);
        nodes.erase(nodes.begin(), nodes.begin() + 2);

        auto merged_node   = std::make_shared<Node>(left->weight + right->weight);
        merged_node->left  = std::move(left);
        merged_node->right = std::move(right);
        nodes.push_back(std::move(merged_node));
    }

    return std::move(nodes[0]);
}

// 前序遍历，用于进行 Huffman 树的前序遍历
void preorder(const Node *root, std::vector<int> &result) {
    if (root) {
        preorder(root->left.get(), result);
        result.push_back(root->weight);
        preorder(root->right.get(), result);
    }
}

void test() {
    // 空测试
    {
        std::vector<int> intput = {};
        auto             root   = huffman_tree(intput);
        std::vector<int> result;
        preorder(root.get(), result);

        std::vector<int> expected = {};
        assert(result == expected);
    }

    // 单个元素
    {
        std::vector<int> intput = {5};
        auto             root   = huffman_tree(intput);
        std::vector<int> result;
        preorder(root.get(), result);

        std::vector<int> expected = {5};
        assert(result == expected);
    }

    // 标准测试
    {
        std::vector<int> intput = {5, 29, 7, 8, 14, 23, 3, 11};
        auto             root   = huffman_tree(intput);
        std::vector<int> result;
        preorder(root.get(), result);

        std::vector<int> expected = {3, 8, 5, 19, 11, 42, 23, 100, 29, 58, 14, 29, 7, 15, 8};
        assert(result == expected);
    }

    std::cout << "test passed\n";
}

int main() {
    test();

    int n;
    std::cin >> n;

    std::vector<int> input_data(n);
    for (auto &weight : input_data) {
        std::cin >> weight;
    }

    auto root = huffman_tree(input_data);

    std::vector<int> result;
    preorder(root.get(), result);

    for (const auto &value : result) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    return 0;
}