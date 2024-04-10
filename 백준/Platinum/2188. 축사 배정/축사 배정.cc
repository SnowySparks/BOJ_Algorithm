#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m;
int rassign[201];
bool v[201];
vector<int> adj[201];

bool dfs(int node) {
    for (int nxt : adj[node]) {
        if (v[nxt]) continue;
        v[nxt] = true;
        if (rassign[nxt] == 0 || dfs(rassign[nxt])) {
            rassign[nxt] = node;
            return true;
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int cnt, tmp;
    for (int i = 1; i <= n; ++i) {
        cin >> cnt;
        while (cnt--)
        {
            cin >> tmp;
            adj[i].push_back(tmp);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        memset(v, 0, sizeof(v));
        if (dfs(i)) ++ans;
    }
    cout << ans;
    return 0;
}