#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<string> realAlerts(int N, unordered_map<string, vector<string>> relations, vector<string> alertList) {
    unordered_set<string> restrained;
    for (auto rel : relations) {
        if (find(alertList.begin(), alertList.end(), rel.first) != alertList.end()) {
            restrained.insert(rel.second.begin(), rel.second.end());
        }
    }

    vector<string> realAlerts;
    for (auto alert : alertList) {
        if (restrained.find(alert) == restrained.end()) {
            realAlerts.push_back(alert);
        }
    }

    return realAlerts;
}

unordered_map<string, vector<string>> getRelations(int n, vector<pair<string, string>> suppressRelations) {
    unordered_map<string, vector<string>> relations;
    for (int i = 0; i < n; i++) {
        string id1 = suppressRelations[i].first;
        string id2 = suppressRelations[i].second;
        relations[id1].push_back(id2);
    }
    return relations;
}

void test() {
    {
        int                                   n                 = 1;
        vector<pair<string, string>>          suppressRelations = {{"A", "B"}};
        vector<string>                        alertList         = {"A", "B"};
        unordered_map<string, vector<string>> relations         = getRelations(n, suppressRelations);
        vector<string>                        output            = realAlerts(1, relations, alertList);

        assert(output.size() == 1);
        assert(output[0] == "A");
    }

    {
        int                                   n                 = 2;
        vector<pair<string, string>>          suppressRelations = {{"A", "B"}, {"B", "C"}};
        vector<string>                        alertList         = {"A", "B", "C", "D", "E"};
        unordered_map<string, vector<string>> relations         = getRelations(n, suppressRelations);
        vector<string>                        output            = realAlerts(2, relations, alertList);
        assert(output.size() == 3);
        assert(find(output.begin(), output.end(), "A") != output.end());
        assert(find(output.begin(), output.end(), "D") != output.end());
        assert(find(output.begin(), output.end(), "E") != output.end());
    }

    cout << "All test cases passed!" << endl;
}

int main() {
    test();

    int N;
    cout << "Enter the number of suppress relations:" << endl;
    cin >> N;

    unordered_map<string, vector<string>> relations;
    cout << "Enter the suppress relations:" << endl;
    for (int i = 0; i < N; i++) {
        string id1, id2;
        cin >> id1 >> id2;
        relations[id1].push_back(id2);
    }

    string         alert;
    vector<string> alertList;
    cout << "Enter the list of alerts" << endl;
    while (cin >> alert) {
        alertList.push_back(alert);
        if (cin.get() == '\n') {
            break;
        }
    }

    cout << "Real alerts list:" << endl;
    for (auto realAlert : realAlerts(N, relations, alertList)) {
        cout << realAlert << " ";
    }
    cout << endl;

    return 0;
}