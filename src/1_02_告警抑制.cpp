#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

map<string, set<string>> suppressMap;

void dfs(const string &id, set<string> &suppressedIds) {
    if (suppressMap.count(id) > 0) {
        for (const auto &suppressed : suppressMap[id]) {
            if (suppressedIds.count(suppressed) == 0) {
                suppressedIds.insert(suppressed);
                dfs(suppressed, suppressedIds);
            }
        }
    }
}

int main() {
    int N;

    cout << "Enter the number of suppress relations:";
    cin >> N;
    for (int i = 0; i < N; i++) {
        string id1, id2;
        cin >> id1 >> id2;
        suppressMap[id1].insert(id2);
    }

    // Compute transitive closure
    for (auto &relation : suppressMap) {
        dfs(relation.first, relation.second);
    }

    cout << "Enter the list of alerts, end with 'end':";
    vector<string> alertList;
    string              alert;
    while (cin >> alert && alert != "end") {
        alertList.push_back(alert);
    }

    // Removing suppressed alerts
    for (const auto &relation : suppressMap) {
        alertList.erase(remove(alertList.begin(), alertList.end(), relation.first), alertList.end());
        for (const auto &suppressed : relation.second) {
            alertList.erase(remove(alertList.begin(), alertList.end(), suppressed), alertList.end());
        }
    }

    cout << "Real alerts list:";
    for (const auto &alert : alertList) {
        cout << " " << alert;
    }
    
    cout <<  endl;

    return 0;
}