#include "dbg.h"

#include <iostream>
#include <memory>
#include <stack>
#include <unordered_map>

using namespace std;

class Directory {
public:
    Directory() = default;
    Directory(const string &name, const shared_ptr<Directory> &parent = nullptr)
        : name(name)
        , parent(parent) {}

public:
    string                                       name;
    unordered_map<string, shared_ptr<Directory>> children;
    weak_ptr<Directory>                          parent;
};

class FileSystem {
public:
    FileSystem() {
        root       = make_shared<Directory>("/");
        currentDir = root;
    }

    void mkdir(const string &dirName) {
        auto it = currentDir->children.find(dirName);
        if (it == currentDir->children.end()) {
            auto newDir                   = make_shared<Directory>(dirName, currentDir);
            currentDir->children[dirName] = newDir;
        }
    }

    void cd(const string &dirName) {
        if (dirName == "..") {
            auto parent = currentDir->parent.lock();
            if (parent) {
                currentDir = parent;
            }
        } else {
            auto it = currentDir->children.find(dirName);
            if (it != currentDir->children.end()) {
                currentDir = it->second;
            }
        }
    }

    string pwd() {
        stack<string>         pathStack;
        shared_ptr<Directory> node = currentDir;
        while (node != nullptr) {
            if (!node->name.empty()) {
                pathStack.push(node->name);
            }
            node = node->parent.lock();
        }
        string path;
        while (!pathStack.empty()) {
            if (!path.empty() &&
                !pathStack.top().empty()) {
                path += "/";
            }
            path += pathStack.top();
            pathStack.pop();
        }
        return path;
    }

private:
    shared_ptr<Directory> root;
    shared_ptr<Directory> currentDir;
};

bool validateDirectory(const string &dirName) {
    for (char c : dirName) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

void executeCommand(FileSystem &fs, const string &cmdKey, const string &cmdVal, string &lastCommandOutput) {
    if (cmdKey == "pwd") {
        if (!cmdVal.empty()) {
            return;
        }
        lastCommandOutput = fs.pwd();
    } else if (cmdKey == "mkdir") {
        if (cmdVal.empty() || !validateDirectory(cmdVal)) {
            return;
        }
        fs.mkdir(cmdVal);
        lastCommandOutput = "";
    } else if (cmdKey == "cd") {
        if (cmdVal.empty() || !validateDirectory(cmdVal)) {
            return;
        }
        fs.cd(cmdVal);
        lastCommandOutput = "";
    }
}

void processCommand(FileSystem &fs, const string &line, string &lastCommandOutput) {
    string cmdKey;
    string cmdVal;

    size_t spacePos = line.find(' ');
    if (spacePos != string::npos) {
        cmdKey = line.substr(0, spacePos);
        cmdVal = line.substr(spacePos + 1);
        dbg(cmdKey, cmdVal);
    } else {
        cmdKey = line;
    }

    executeCommand(fs, cmdKey, cmdVal, lastCommandOutput);
}

int main() {
    FileSystem fs;
    string     lastCommandOutput = "";

    while (true) {
        string line;
        getline(cin, line);

        if (line.empty()) {
            break;
        }
        processCommand(fs, line, lastCommandOutput);
    }

    cout << lastCommandOutput << endl;

    return 0;
}