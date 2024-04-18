#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int R, C;
bool emp[301][301];
int assign[301];
bool v[301];
int n;
vector<int> adj[301];

bool dfs(int x) {
    for (int &nxt : adj[x]) {
        if (v[nxt]) continue;
        v[nxt] = true;
        if (!assign[nxt] || dfs(assign[nxt])) {
            assign[nxt] = x;
            return true;
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> R >> C >> n;
    int a, b;
    for (int i = 0; i < n ; ++i) {
        cin >> a >> b;
        emp[a][b] = true;
    }

    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C; ++j) {
            if (!emp[i][j]) {
                adj[i].push_back(j);
            }
        }
    }

    int cnt = 0;
    for (int i = 1; i <= R; ++i) {
        memset(v, 0, sizeof(v));
        cnt += ( dfs(i) ? 1 : 0);
    }
    cout << cnt;
    return 0;
}