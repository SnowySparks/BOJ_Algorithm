#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
bool v[101];
int assign[101]; // right 노드가 어느 왼쪽 노드에 연결되어 있는가?
vector<int> adj[101];
int n, m;

bool dfs(int node) {
    for (int &nxt : adj[node]) {
        if (v[nxt]) continue;
        v[nxt] = true;

        if (assign[nxt] == 0 || dfs(assign[nxt])) {
            assign[nxt] = node;
            return true;
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    while (m--)
    {
        int a, b;
        cin >> a >> b; //person -> notebook
        adj[a].push_back(b);
    }
    int ans = 0;
    for (int i =1; i <=n; ++i) {
        memset(v, 0, sizeof(v));
        if (dfs(i)) ans++;
    }
    cout << ans;

    return 0;
}