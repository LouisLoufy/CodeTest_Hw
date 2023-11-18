#include "dbg.h"

#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

class TreeNode {
public:
    string                            curDicName;
    TreeNode                         *father;
    unordered_map<string, TreeNode *> children;

    TreeNode(string curDicName, TreeNode *father)
        : curDicName(curDicName)
        , father(father) {}
};

class Tree {
public:
    TreeNode *root;
    TreeNode *cur;

    Tree() {
        root = new TreeNode("/", nullptr);
        cur  = root;
    }

    void mkdir(const string &childDicName) {
        if (cur->children.find(childDicName) == cur->children.end()) {
            cur->children[childDicName] = new TreeNode(childDicName + "/", cur);
        }
    }

    void cd(const string &dicName) {
        if (dicName == "..") {
            if (cur->father != nullptr) {
                cur = cur->father;
            }
        } else {
            if (cur->children.find(dicName) != cur->children.end()) {
                cur = cur->children[dicName];
            }
        }
    }

    string pwd() {
        stack<string> pathStack;
        TreeNode     *node = cur;
        while (node != nullptr) {
            pathStack.push(node->curDicName);
            node = node->father;
        }
        string path;
        while (!pathStack.empty()) {
            path += pathStack.top();
            pathStack.pop();
        }
        return path;
    }
};

int main() {
    Tree   tree;
    string lastCommandOutput = "";

    while (true) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            break;
        }

        string cmd_key;
        string cmd_val;

        size_t spacePos = line.find(' ');
        if (spacePos != string::npos) {
            cmd_key = line.substr(0, spacePos);
            cmd_val = line.substr(spacePos + 1);
        } else {
            cmd_key = line;
        }

        if (cmd_key == "pwd") {
            if (!cmd_val.empty()) {
                continue;
            }
            lastCommandOutput = tree.pwd();
        } else if (cmd_key == "mkdir" || cmd_key == "cd") {
            if (cmd_val.empty()) {
                continue;
            }

            bool isValidDirectory = true;
            for (char c : cmd_val) {
                if (c < 'a' || c > 'z') {
                    isValidDirectory = false;
                    break;
                }
            }

            if (!isValidDirectory) {
                continue;
            }

            if (cmd_key == "mkdir") {
                tree.mkdir(cmd_val);
                lastCommandOutput = "";
            } else {
                tree.cd(cmd_val);
                lastCommandOutput = "";
            }
        }
    }

    cout << lastCommandOutput << endl;

    return 0;
}