#include "dbg.h"

#include <cassert>
#include <iostream>
#include <sstream>

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

private:
    int         id_;
    int         size_;
    vector<int> subfolders_;
};

int getSum(int targetId, vector<Folder> Folders) {}

void test() {
    {
        int            targetId = 1;
        vector<Folder> Folders  = {Folder{3, 15, {}}, Folder{1, 20, {2}}, Folder{2, 10, {3}}};

        int result = getSum(targetId, Folders);
        assert(result == 45);
    }

    {
        int            targetId = 2;
        vector<Folder> Folders  = {Folder{4, 20, {}}, Folder{5, 30, {}}, Folder{2, 10, {4, 5}},
                                   Folder{1, 40, {}}};

        int result = getSum(targetId, Folders);
        assert(result == 60);
    }

    cout << "testGetSum pass" << endl;
}

int main() {
    // test();

    int n, targetId;
    cin >> n >> targetId;

    vector<Folder> folders(n);

    for (int i = 0; i < n; i++) {
        int id, size;
        cin >> id >> size;

        string line;
        cin.ignore();
        getline(cin, line);

        stringstream ss(line);
        string       token;
        vector<int>  subfolders;

        while (getline(ss, token, ',')) {
            subfolders.push_back(stoi(token));
        }

        folders[i] = Folder(id, size, subfolders);
    }

    for (const auto &folder : folders) {
        cout << folder << endl;
    }

    return 0;
}