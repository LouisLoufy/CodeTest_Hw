#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

struct Node {
    int   weight;
    Node *left;
    Node *right;

    Node(int w)
        : weight(w)
        , left(nullptr)
        , right(nullptr) {}
};

// 构建Huffman树
Node *huffman_tree(const std::vector<int> &data) {
    if (data.empty()) {
        return nullptr;
    }

    // 使用 nodes 接收data的权重
    std::vector<Node *> nodes;
    for (int weight : data) {
        nodes.push_back(new Node(weight));
    }

    while (nodes.size() > 1) { // 结束判断 直到只剩下一个最后一个节点
        // 按照权重对 nodes 进行升序排序
        std::sort(nodes.begin(), nodes.end(),
                  [](const auto &a, const auto &b) { return a->weight < b->weight; });

        // 从 nodes 中移除权重最小的两个节点，分别记为 left 和 right
        Node *left  = nodes[0];
        Node *right = nodes[1];
        nodes.erase(nodes.begin(), nodes.begin() + 2);

        // 创建一个新的节点 merged_node，其权重为left和right节点的权重之和
        Node *merged_node  = new Node(left->weight + right->weight);
        merged_node->left  = left;
        merged_node->right = right;
        nodes.push_back(merged_node);
    }

    return nodes[0];
}

// 前序遍历，用于进行 Huffman 树的前序遍历
void preorder(const Node *root, std::vector<int> &result) {
    if (root) {
        preorder(root->left, result);
        result.push_back(root->weight);
        preorder(root->right, result);
    }
}

void test() {
    // 空测试
    {
        std::vector<int> intput = {};
        Node            *root   = huffman_tree(intput);
        std::vector<int> result;
        preorder(root, result);

        std::vector<int> expected = {};
        assert(result == expected);
    }

    // 单个元素
    {
        std::vector<int> intput = {5};
        Node            *root   = huffman_tree(intput);
        std::vector<int> result;
        preorder(root, result);

        std::vector<int> expected = {5};
        assert(result == expected);
    }

    // 标准测试
    {
        std::vector<int> intput = {5, 29, 7, 8, 14, 23, 3, 11};
        Node            *root   = huffman_tree(intput);
        std::vector<int> result;
        preorder(root, result);

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

    Node *root = huffman_tree(input_data);

    std::vector<int> result;
    preorder(root, result);

    for (const auto &value : result) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    return 0;
}
