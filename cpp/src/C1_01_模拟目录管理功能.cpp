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

    TreeNode(string curDicName, TreeNode *father) {
        this->curDicName = curDicName;
        this->father     = father;
    }
};

class Tree {
public:
    TreeNode *root;
    TreeNode *cur;

    Tree() {
        this->root = new TreeNode("/", nullptr);
        this->cur  = root;
    }

    void mkdir(string childDicName) {
        this->cur->children.emplace(childDicName, new TreeNode(childDicName + "/", this->cur));
    }

    void cd(string dicName) {
        if (dicName == "..") {
            if (this->cur->father != nullptr) {
                this->cur = this->cur->father;
            }
        } else {
            if (this->cur->children.find(dicName) != this->cur->children.end()) {
                this->cur = this->cur->children[dicName];
            }
        }
    }

    string pwd() {
        stack<TreeNode *> pathStack;
        TreeNode         *curNode = this->cur;
        while (curNode != nullptr) {
            pathStack.push(curNode);
            curNode = curNode->father;
        }
        string path;
        while (!pathStack.empty()) {
            path += pathStack.top()->curDicName;
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