#include <cassert>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>

struct TreeNode {
    char      val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(char x)
        : val(x)
        , left(nullptr)
        , right(nullptr) {}
};

// 递归构建二叉树
TreeNode *buildTree(const std::string &inorder, const std::string &postorder, int in_start, int in_end,
                    int post_start, int post_end, const std::unordered_map<char, int> &inorder_map) {
    if (in_start > in_end || post_start > post_end) {
        return nullptr;
    }

    char      root_val = postorder[post_end];
    TreeNode *root     = new TreeNode(root_val);

    int root_index = inorder_map.at(root_val);
    int left_size  = root_index - in_start;

    root->left  = buildTree(inorder, postorder, in_start, root_index - 1, post_start,
                            post_start + left_size - 1, inorder_map);
    root->right = buildTree(inorder, postorder, root_index + 1, in_end, post_start + left_size, post_end - 1,
                            inorder_map);

    return root;
}

// 层次遍历
void bfs(TreeNode *root) {
    if (!root) {
        return;
    }

    std::queue<TreeNode *> queue;
    queue.push(root);

    while (!queue.empty()) {
        TreeNode *curr = queue.front();
        queue.pop();
        std::cout << curr->val;

        if (curr->left) {
            queue.push(curr->left);
        }
        if (curr->right) {
            queue.push(curr->right);
        }
    }
}

void printLevelOrder(const std::string &inorder, const std::string &postorder) {
    int                           n = inorder.size();
    std::unordered_map<char, int> inorder_map;
    for (int i = 0; i < n; ++i) {
        inorder_map[inorder[i]] = i;
    }

    TreeNode *root = buildTree(inorder, postorder, 0, n - 1, 0, n - 1, inorder_map);

    bfs(root);
}

void testPrintLevelOrder(const std::string &postorder, const std::string &inorder,
                         const std::string &expected_output) {
    std::stringstream input;
    std::stringstream output;

    // 重定向输入输出流
    std::streambuf *orig_input  = std::cin.rdbuf(input.rdbuf());
    std::streambuf *orig_output = std::cout.rdbuf(output.rdbuf());

    // 输入测试用例
    input << postorder << " " << inorder;

    // 执行被测函数
    printLevelOrder(inorder, postorder);

    // 还原输入输出流
    std::cin.rdbuf(orig_input);
    std::cout.rdbuf(orig_output);

    // 使用 assert 断言输出结果是否与预期相符
    assert(output.str() == expected_output);
}

void test() {
    {
        std::string postorder = "HIDJEBFGCA", inorder = "HDIBJEAFCG", expected = "ABCDEFGHIJ";
        testPrintLevelOrder(postorder, inorder, expected);
    }
    std::cout << "test passed\n";
}

int main() {
    test();

    std::string inorder, postorder;
    std::cin >> postorder >> inorder;

    printLevelOrder(inorder, postorder);

    return 0;
}