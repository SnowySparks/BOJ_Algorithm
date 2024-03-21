#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define f(a, b, c) for (int a = b; a < c; ++a)
#define N_MAX 401
const int inf = 1e9 + 7;
vector<int> adj[N_MAX];
int capacity[N_MAX][N_MAX];
int flow[N_MAX][N_MAX];
int parent[N_MAX];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, p; cin >> n >> p;
    int fr, to;
    f(i, 0, p) {
        cin >> fr >> to;
        adj[fr].push_back(to);
        adj[to].push_back(fr);

        capacity[fr][to]++;
        // capacity[to][fr]++;
    }
    int ans = 0;
    while (1)
    {
        // 초기
        memset(parent, -1, sizeof(parent));
        parent[1] = 1;
        queue<int> q; q.push(1);

        while (!q.empty())
        {
            int loc = q.front(); q.pop();
            for (int nxt : adj[loc]) {
                int left_capacity = capacity[loc][nxt] - flow[loc][nxt];
                if (left_capacity > 0 && parent[nxt] == -1) {
                    parent[nxt] = loc;
                    q.push(nxt);
                    if (nxt == 2) break;
                }
            }
        }

        if (parent[2] == -1) break;

        int min_left_cp = inf;
        for (int node = 2; node != 1; node = parent[node]) {
            min_left_cp = min(min_left_cp, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for (int node = 2; node != 1; node = parent[node]) {
            flow[parent[node]][node] += min_left_cp;
            flow[node][parent[node]] -= min_left_cp;
        }
        ans += min_left_cp;
    }
    cout << ans;
    return 0;
}