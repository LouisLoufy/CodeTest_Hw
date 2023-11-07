#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

string getResult(unordered_map<int, unordered_set<int>> &trans) {
    for (const auto &[send, receivers] : trans) {
        for (const auto &receive : receivers) {
            if (trans[receive].find(send) == trans[receive].end()) {
                return "False";
            }
        }
    }
    return "True";
}

void test() {
    {
        unordered_map<int, unordered_set<int>> trans  = {{1, {2}}, {2, {1}}, {3, {4}}, {4, {3}}};
        string                                 result = getResult(trans);
        assert(result == "True");
    }
    {
        unordered_map<int, unordered_set<int>> trans  = {{1, {2}}, {2, {3}}, {3, {1}}};
        string                                 result = getResult(trans);
        assert(result == "False");
    }
    {
        unordered_map<int, unordered_set<int>> trans  = {{1, {2}}, {2, {1}}, {3, {4}}};
        string                                 result = getResult(trans);
        assert(result == "False");
    }
    {
        unordered_map<int, unordered_set<int>> trans  = {{1, {2, 3}}, {2, {1}}, {3, {1}}};
        string                                 result = getResult(trans);
        assert(result == "True");
    }
    {
        unordered_map<int, unordered_set<int>> trans  = {{1, {2}}};
        string                                 result = getResult(trans);
        assert(result == "False");
    }

    cout << "All test cases passed!" << endl;
}

int main() {
    test();

    cout << "Enter the number of packets" << endl;
    int n;
    cin >> n;

    cout << "Enter one-way messages" << endl;
    unordered_map<int, unordered_set<int>> trans;
    for (int i = 0; i < n; i++) {
        int send, receive;
        cin >> send >> receive;
        trans[send].insert(receive);
    }

    cout << "Result: " << endl;
    cout << getResult(trans) << endl;

    return 0;
}