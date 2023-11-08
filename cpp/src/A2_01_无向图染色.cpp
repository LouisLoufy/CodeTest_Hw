#include <iostream>
#include <vector>

using namespace std;

const int   MOD  = 1e9 + 7;
const int   MAXN = 1e5 + 5;
vector<int> graph[MAXN];
long long   dp[MAXN][2];

void dfs(int node, int parent) {
    dp[node][0] = 1;
    dp[node][1] = 1;
    for (int i = 0; i < graph[node].size(); i++) {
        int neighbor = graph[node][i];
        if (neighbor != parent) {
            dfs(neighbor, node);
            dp[node][0] = dp[node][0] * dp[neighbor][1] % MOD;
            dp[node][1] = dp[node][1] * (dp[neighbor][0] + dp[neighbor][1]) % MOD;
        }
    }
}

int main() {
    int M /* 节点数 */, N /* 边数 */;
    cin >> M >> N;
    for (int i = 0; i < N; i++) {
        int V1, V2;
        cin >> V1 >> V2;
        graph[V1].push_back(V2);
        graph[V2].push_back(V1);
    }
    dfs(1, -1);
    cout << (dp[1][0] + dp[1][1]) % MOD << endl;
    return 0;
}