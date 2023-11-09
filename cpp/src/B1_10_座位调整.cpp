#include "dbg.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int getResult(vector<int> &desk) {
    int num = 0;
    int n   = desk.size();

    for (int i = 0; i < n; ++i) {
        if (desk[i] == 0) {
            dbg(i, desk);
            if ((i == 0 || desk[i - 1] == 0) && (i == n - 1 || desk[i + 1] == 0)) {
                ++num;
                dbg(i, desk);
                desk[i] = 1;
            }
        }
    }

    return num;
}

void test() {
    {
        vector<int> desk{0};
        assert(getResult(desk) == 1);
    }

    {
        vector<int> desk{1};
        assert(getResult(desk) == 0);
    }

    {
        vector<int> desk{0, 0, 1, 0, 0};
        assert(getResult(desk) == 2);
    }

    {
        vector<int> desk{1, 0, 0, 0, 1};
        assert(getResult(desk) == 1);
    }

    cout << "testgetResult pass" << endl;
}

int main() {
    // test();

    string line;
    getline(cin, line);

    stringstream ss(line);
    string       str;
    vector<int>  desk;

    while (getline(ss, str, ',')) {
        desk.emplace_back(stoi(str));
    }

    cout << "Result: " << getResult(desk) << endl;
}