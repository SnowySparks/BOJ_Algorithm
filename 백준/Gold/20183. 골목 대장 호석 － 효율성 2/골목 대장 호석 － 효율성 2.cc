#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int max_node = 1e5+1;
using ll = long long;
const ll inf = 1e15;
int n, m, a, b; ll c; // 노드갯수, edge개수, 시작점, 도착점, 보유돈

ll dist[max_node];
vector<pair<int, ll> > adj[max_node]; // nxt, cost

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> a >> b >> c;
    int fr, to; ll cost;
    while (m--)
    {
        cin >> fr >> to >> cost;
        adj[fr].push_back({to, cost});
        adj[to].push_back({fr, cost});
    }

    ll ans = -1;
    ll l = 1, r = c;
    priority_queue<pair<ll ,int> > pq; // -cost, node
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        fill(dist, dist+n+1, inf);
        dist[a] = 0;
        pq.push({0, a});

        while (!pq.empty())
        {
            ll now_cost = -pq.top().first, node = pq.top().second; pq.pop();
            if (now_cost > dist[node] || now_cost > c) continue;
            for (auto &[nxt, cost] : adj[node]) {
                if (cost > mid) continue;
                ll new_cost = cost + now_cost;
                if (new_cost < dist[nxt] && new_cost <= c) {
                    dist[nxt] = new_cost;
                    pq.push({-new_cost, nxt});
                }
            }
        }

        if (dist[b] != inf) {
            ans = mid;
            r = mid -1;
        }
        else {
            l = mid + 1;
        }
        
    }
    cout << ans;
    return 0;
}