#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 1e9;
using pii = pair<int, int>;

int n, m;
vector<pii> adj[501]; // nxt, cost

int c[501][501]; //capacity
int f[501][501]; // flow
int prv[501]; //
bool v[501];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int s, e;
    int total = 0;
    // input
    cin >> n >> m;
    int a, b, v;
    while (m--)
    {
        cin >> a >> b >> v;
        adj[a].push_back({b, v});
        adj[b].push_back({a, v});
        c[a][b] = v;
        c[b][a] = v;
    }
    cin >> s >> e;
    // 에드몬드-카프
    while (1)
    {
        /* code */
        memset(prv, -1, sizeof(prv));
        prv[s] = s;
        queue<int> q;
        q.push(s);

        while (!q.empty() && prv[e] == -1)
        {
            int loc = q.front(); q.pop();
            for (auto &[nxt, cost] : adj[loc]) {
                if (prv[nxt] == -1 && c[loc][nxt] - f[loc][nxt] > 0) {
                    q.push(nxt);
                    prv[nxt] = loc;
                }
            }
        }

        if (prv[e] == -1) break;

        //해당 경로 잔여 용량 최저
        int min_res = inf;
        for (int i = e; i != s; i = prv[i]) {
            min_res = min(min_res, c[prv[i]][i] - f[prv[i]][i]);
        }

        for (int i = e; i != s; i = prv[i]) {
            f[prv[i]][i] += min_res;
            f[i][prv[i]] -= min_res;
        }      
        total += min_res;
    }
    cout << total;

    return 0;
}