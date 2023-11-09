#include "dbg.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Folder {
public:
    Folder() = default;
    Folder(int id, int size, vector<int> subfolders)
        : id_(id)
        , size_(size)
        , subfolders_(subfolders){};

    friend ostream &operator<<(ostream &os, const Folder &fd) {
        os << "id:" << fd.id_ << ", size:" << fd.size_ << ", subFolders:(";
        for (size_t i = 0; i < fd.subfolders_.size(); ++i) {
            os << fd.subfolders_[i];
            if (i != fd.subfolders_.size() - 1) {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

public:
    int         id_;
    int         size_;
    vector<int> subfolders_;
};

unordered_map<int, Folder> saveFolders(const vector<Folder> &folders) {
    unordered_map<int, Folder> folderMap;
    for (const Folder &folder : folders) {
        folderMap[folder.id_] = folder;
    }
    return folderMap;
}

int calculateTotalSize(int id, const unordered_map<int, Folder> &folderMap) {
    if (folderMap.find(id) == folderMap.end()) {
        return 0;
    }

    const Folder &folder    = folderMap.at(id);
    int           totalSize = folder.size_;

    for (int subfolderId : folder.subfolders_) {
        totalSize += calculateTotalSize(subfolderId, folderMap);
    }

    return totalSize;
}

void test() {
    {
        int                        targetId  = 1;
        vector<Folder>             folders   = {Folder{3, 15, {}}, Folder{1, 20, {2}}, Folder{2, 10, {3}}};
        unordered_map<int, Folder> folderMap = saveFolders(folders);
        assert(calculateTotalSize(targetId, folderMap) == 45);
    }

    {
        int                        targetId  = 2;
        vector<Folder>             folders   = {Folder{4, 20, {}}, Folder{5, 30, {}}, Folder{2, 10, {4, 5}},
                                                Folder{1, 40, {}}};
        unordered_map<int, Folder> folderMap = saveFolders(folders);

        assert(calculateTotalSize(targetId, folderMap) == 60);
    }

    cout << "testCalculateTotalSize pass" << endl;
}

int main() {
    test();

    int n, targetId;
    cin >> n >> targetId;
    dbg(n, targetId);

    vector<Folder> folders;
    for (int i = 0; i < n; ++i) {
        // TODO 傻逼输入输出，接收后面的n行输入，推入vector<Folder>
        dbg(folders[i]);
    }

    unordered_map<int, Folder> folderMap = saveFolders(folders);

    cout << "totalSize: " << calculateTotalSize(targetId, folderMap) << endl;

    return 0;
}