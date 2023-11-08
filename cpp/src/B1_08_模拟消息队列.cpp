#include "dbg.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> split(const string &s) {
    stringstream ss(s);
    string       item;
    vector<int>  elems;
    while (getline(ss, item, ' ')) {
        elems.emplace_back(stoi(item));
    }
    return elems;
}

vector<vector<int>> getResult(vector<int> &pubArr, vector<int> &subArr) {
    int n = pubArr.size();
    int m = subArr.size();

    vector<vector<int>> publisher(n / 2), subscriber(m / 2);
    for (int i = 0; i < n; i += 2) {
        publisher[i / 2] = {pubArr[i], pubArr[i + 1]};
    }

    for (int j = 0; j < m; j += 2) {
        subscriber[j / 2] = {subArr[j], subArr[j + 1]};
    }

    sort(publisher.begin(), publisher.end());
    // dbg(publisher);

    vector<vector<int>> subContent(subscriber.size());

    for (auto &pub : publisher) {
        for (int j = subscriber.size() - 1; j >= 0; --j) { // 优先发给后面的消费者，倒序
            if (pub[0] >= subscriber[j][0] && pub[0] < subscriber[j][1]) {
                subContent[j].emplace_back(pub[1]);
                // dbg(subContent);
                break;
            }
        }
    }

    return subContent;
}

void testSplit() {
    vector<int> expected = {1, 2, 3, 4, 5};
    string      input    = "1 2 3 4 5";

    vector<int> result = split(input);
    assert(result == expected);

    cout << "testSplit pass" << endl;
}

void testGetResult() {
    {
        vector<int> pubArr = {0, 1, 1, 2, 2, 3};
        vector<int> subArr = {0, 1, 1, 3};

        vector<vector<int>> expected = {{1}, {2, 3}};
        vector<vector<int>> result   = getResult(pubArr, subArr);

        assert(result == expected);
    }

    {
        vector<int> pubArr = {2, 22, 1, 11, 4, 44, 5, 55, 3, 33};
        vector<int> subArr = {1, 7, 2, 3};

        vector<vector<int>> expected = {{11, 33, 44, 55}, {22}};
        vector<vector<int>> result   = getResult(pubArr, subArr);

        assert(result == expected);
    }

    {
        vector<int> pubArr = {5, 64, 11, 64, 9, 97};
        vector<int> subArr = {9, 11, 4, 9};

        vector<vector<int>> expected = {{97}, {64}};
        vector<vector<int>> result   = getResult(pubArr, subArr);

        assert(result == expected);
    }

    cout << "testGetResult pass" << endl;
}

int main() {
    testSplit();
    testGetResult();

    string pubLine, subLine;
    getline(cin, pubLine);
    getline(cin, subLine);

    vector<int> pubArr = split(pubLine);
    vector<int> subArr = split(subLine);

    vector<vector<int>> res = getResult(pubArr, subArr);

    for (auto &contents : res) {
        if (contents.empty()) {
            cout << "-1" << endl;
        } else {
            for (int i = 0; i < contents.size(); ++i) {
                if (i != 0) {
                    cout << ' ';
                }
                cout << contents[i];
            }
            cout << endl;
        }
    }

    return 0;
}