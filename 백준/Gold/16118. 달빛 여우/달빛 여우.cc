#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
using pii = pair<int ,int>;
const int inf = 2e9;
#define f(a, b, c) for (int a = b; a < c; ++a)
int n, m;
vector<pii> adj[4001]; //nxt, cost
int fox_dist[4001]; //
int wolf_dist[4001][2]; //늑대, 짝수(0포함) 이동, 홀수 번째 이동

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    f(i, 0, n+1) {
        fox_dist[i] = inf;
        wolf_dist[i][0] = inf;
        wolf_dist[i][1] = inf;
    }
    int a, b, d;
    f(i, 0, m) {
        cin >>a >> b >> d;
        d*=2; // 일부러 -> 0.5 억제용
        adj[a].push_back({b, d});
        adj[b].push_back({a, d});
    }
    priority_queue<pii> pq;
    // 여우 이동
    fox_dist[1] = 0;
    
    pq.push({0, 1});
    while (!pq.empty())
    {
        int loc = pq.top().second, d = -pq.top().first; pq.pop();
        if (fox_dist[loc] < d) continue;
        for (auto &[nxt, cost] : adj[loc]) {
            int new_dist = d + cost;
            if (new_dist < fox_dist[nxt]) {
                pq.push({-new_dist, nxt});
                fox_dist[nxt] = new_dist;
            }
        }
    }
    
    //늑대 이동
    priority_queue<pair<int, pair<int, int > > > fpq; // {dist, {loc, day}}
    fpq.push({0, {1, 0}});
    wolf_dist[1][0] = 0;
    while (!fpq.empty())
    {
        int d = -fpq.top().first, loc = fpq.top().second.first, day = fpq.top().second.second;
        fpq.pop();

        if (wolf_dist[loc][day] < d) continue;

        for (auto [nxt, cost] : adj[loc]) {
            if (day) cost *= 2;
            else cost >>= 1;

            int new_cost = d + cost;
            if (wolf_dist[nxt][day^1] > new_cost) {
                wolf_dist[nxt][day^1] = new_cost;
                fpq.push({-new_cost, {nxt, day^1}});
            }
        }
    }
    
    int ans = 0;
    f(i, 1, n+1) {
        if (fox_dist[i] < min(wolf_dist[i][0], wolf_dist[i][1])) {
            // cout << i <<' ' << fox_dist[i] <<' ' << min(wolf_dist[i][0], wolf_dist[i][1]) << '\n';
            ++ans;
        }
    }
    cout << ans;

    return 0;
}