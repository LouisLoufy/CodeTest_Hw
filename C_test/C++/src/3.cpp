#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

// 定义了一个 TreeNode 结构体，表示二叉树的节点
struct TreeNode {
    int       val;   // 值
    TreeNode *left;  // 左子节点
    TreeNode *right; // 右子节点

    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr) {}
};

// 广度优先搜索（BFS）
void bfs(TreeNode *root) {
    if (!root) {
        return;
    }
    deque<TreeNode *> queue;
    queue.push_back(root);
    while (!queue.empty()) {
        int         level_size = queue.size();
        vector<int> temp;
        for (int i = 0; i < level_size; i++) {
            TreeNode *current_node = queue.front();
            queue.pop_front();
            temp.push_back(current_node->val);
            if (current_node->left) {
                queue.push_back(current_node->left);
            }
            if (current_node->right) {
                queue.push_back(current_node->right);
            }
        }
        for (int i = 0; i < temp.size(); i++) {
            cout << temp[i];
        }
    }
}

// 用于构建二叉树
TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    if (inorder.empty() && postorder.empty()) {
        return nullptr;
    }
    int root_val = postorder.back();
    postorder.pop_back();
    TreeNode *root = new TreeNode(root_val);
    auto      it   = find(inorder.begin(), inorder.end(), root_val);
    int       idx  = distance(inorder.begin(), it);

    vector<int> left_inorder(inorder.begin(), it);
    vector<int> right_inorder(it + 1, inorder.end());
    vector<int> left_postorder(postorder.begin(), postorder.begin() + idx);
    vector<int> right_postorder(postorder.begin() + idx, postorder.end());

    root->left  = buildTree(left_inorder, left_postorder);
    root->right = buildTree(right_inorder, right_postorder);
    return root;
}

int main() {
    string a, b;
    cin >> a >> b;
    vector<int> postorder(a.begin(), a.end());
    vector<int> inorder(b.begin(), b.end());

    TreeNode *root = buildTree(inorder, postorder);

    bfs(root);

    return 0;
}