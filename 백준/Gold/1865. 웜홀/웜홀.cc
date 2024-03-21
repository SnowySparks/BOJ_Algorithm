#include <iostream>
#include <vector>
#include <algorithm>
#define INF 0x7f7f7f7f
#define f(a, b, c) for (int a = b; a < c; ++a)
using namespace std;
int n, m, w;

vector<pair<int ,int> > adj[501];
int dist[501];
bool bell_ford(int start = 0) {
    dist[start] = 0;
    bool is_minus_cycle = false;
    // N번 순회 , N번째에서 dist값 갱신이 있으면 사이클이 있는 것
    for (int iter = 1; iter <= n; ++iter) {
        for (int node = 1; node <= n; ++node) {
            for (auto &[nxt, cost] : adj[node]) {
                int new_cost = cost + dist[node];
                if (new_cost < dist[nxt]) {
                    dist[nxt] = new_cost;
                    if (iter == n) is_minus_cycle = true;
                }
            }
        }
    }
    return is_minus_cycle;
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int tc; cin >> tc;
    int s, e, t;
    while (tc--) {
        cin >> n >> m >> w;
        f(i, 1, n+1) dist[i] = INF;
        f(i, 1, n+1) adj[i].clear();
        // 길
        f(i, 0, m) {
            cin >> s >> e >> t;
            adj[s].push_back({e, t});
            adj[e].push_back({s, t});
        }
        // 웜홀
        f(i, 0, w) {
            cin >> s >> e >> t;
            adj[s].push_back({e, -t});
        }
        // cout <<"--\n";
        cout << (bell_ford() ? "YES\n" : "NO\n");
    }
    return 0;
}