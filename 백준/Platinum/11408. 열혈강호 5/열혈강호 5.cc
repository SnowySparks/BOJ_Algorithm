#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;
int n, m;
vector<int> adj[900]; // to, cost
int src = 0, sink;
// s : 0, e  : n + m + 1;
const int inf = 1e9;

int c[900][900], f[900][900], cost[900][900]; // 용량, 유량, 비용
int dist[900], prv[900]; // spfa 전용
bool v[900]; //queue에 포함되었는지 판단여부

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int to, wcost;
    int total_flow = 0;
    int total_cost = 0;
    // input
    cin >> n >> m;
    sink = n + m + 1;

    // 연결

    for (int person = 1; person <= n; ++person) {
        // src -> person
        adj[src].push_back(person);
        adj[person].push_back(src);
        c[src][person] = 1;

        //person -> work(to)
        int wcnt; cin >> wcnt;
        while (wcnt--)
        {
            cin >> to >> wcost;
            to += n;
            adj[person].push_back(to);
            adj[to].push_back(person);

            // 비용 역방향에 대한 처리
            cost[person][to] = wcost;
            cost[to][person] = -wcost;

            // 용량
            c[person][to] = 1;
        }
    }

    // work -> sink
    for (int w = n+1; w <= n+m; ++w) {
        adj[w].push_back(sink);
        adj[sink].push_back(w);
        c[w][sink] = 1;
    }

    // mcmf

    while (1)
    {
        // 초기화 + src처리
        memset(prv, -1, sizeof(prv));
        fill(dist, dist+sink+1, inf);
        memset(v, 0, sizeof(v));

        prv[src] = src;
        dist[src] = 0;
        v[src] = true;
        queue<int> q;
        q.push(src);

        // spfa

        while (!q.empty())
        {
            int loc = q.front(); q.pop(); v[loc] = false;
            for (int nxt : adj[loc]) {
                if (c[loc][nxt] - f[loc][nxt] > 0 && dist[nxt] > dist[loc] + cost[loc][nxt]) {
                    dist[nxt] = dist[loc] + cost[loc][nxt];
                    prv[nxt] = loc;

                    if (!v[nxt]) {
                        v[nxt] = true;
                        q.push(nxt);
                    }
                }
            }
        }

        if (prv[sink] == -1) break;

        for (int i = sink; i != src; i = prv[i]) {
            total_cost += cost[prv[i]][i];
            f[prv[i]][i]++;
            f[i][prv[i]]--;
        }
        total_flow++;
    }

    cout << total_flow << '\n' << total_cost;

    return 0;
}