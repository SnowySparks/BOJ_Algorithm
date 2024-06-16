#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
vector<pair<int ,int> > adj[101]; // nxt, cnt;
int indegree[101];
int dp[101];
vector<int> leap;
bool v[101];
// 말단찾기
void dfs(int x) {
    if (adj[x].empty()) {
        leap.push_back(x);
        return;
    }

    for (auto &[nxt, cost] : adj[x]) {
        if (v[nxt]) continue;
        v[nxt] = true;
        dfs(nxt);
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    cin >> m;
    int x, y, k;
    while (m--)
    {
        cin >> x >> y >> k; // x 만드는데 y가 k개 필요하다는 것
        adj[x].push_back({y, k});
        indegree[y]++;
    }

    dfs(n);
    sort(leap.begin(), leap.end());
    queue<int > q;
    q.push(n);
    dp[n] = 1;

    while (!q.empty())
    {
        int loc = q.front(); q.pop();
        
        for (auto &[nxt, weight] : adj[loc]) {
            dp[nxt] += dp[loc] * weight;
            indegree[nxt]--;

            if (indegree[nxt] == 0) {
                q.push(nxt);
            }
        }
    }
    for (int &node : leap) {
        cout << node << ' ' << dp[node] << '\n';
    }
    return 0;
}