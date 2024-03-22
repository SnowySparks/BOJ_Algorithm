#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n;
const int mv = 1e5+1;
const int inf = 1e9+1;
vector<int> adj[mv];
int t[mv];
int indegree[mv];
int dp[mv];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    int tmp;
    for (int i = 1; i <= n ; ++i) {
        // dp[i] = inf;
        cin >> t[i];
        int cnt; cin >> cnt;
        indegree[i] = cnt;
        for (int j = 0; j < cnt; ++j) {
            cin >> tmp;
            adj[tmp].push_back(i);
        }
    }
    queue<int> q;
    for (int i = 1; i <= n ; ++i) {
        if (!indegree[i]) {
            q.push(i);
            dp[i] = t[i];
        }
    }
    while (!q.empty())
    {
        int loc = q.front(); q.pop();
        for (int nxt : adj[loc]) {
            indegree[nxt]--;
            dp[nxt] = max(dp[nxt], dp[loc] + t[nxt]);
            if (indegree[nxt] == 0) {
                q.push(nxt);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = max(ans, dp[i]);
    cout << ans;
    
    return 0;
}