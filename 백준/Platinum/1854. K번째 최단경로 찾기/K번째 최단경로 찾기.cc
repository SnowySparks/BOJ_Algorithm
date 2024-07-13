#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)
using pii = pair<int ,int>;
const int MAXN = 1e3+1;
const int INF = 1e9+7;
vector<pii> adj[MAXN]; // {nxt, cost}
int dist[MAXN];
int n, m, k;
priority_queue<pair<int ,int> > pq;

priority_queue<int> weight[MAXN]; // 각 노드마다할당. 1에서부터 


void dijkstra() {
    f(i, 0, n+1) dist[i] = INF;
    weight[1].push(0);

    int acc_cost, node;
    pq.push({0, 1}); // {누적비용, 노드}
    while (!pq.empty())
    {
        tie(acc_cost, node) = pq.top(); pq.pop();
        acc_cost=-acc_cost;
        for (auto &[nxt, cost] : adj[node]) {
            int nxt_cost = acc_cost + cost;

            if (weight[nxt].size() < k) {
                weight[nxt].push(nxt_cost);
                pq.push({-nxt_cost, nxt});
            }
            else if (weight[nxt].top() > nxt_cost) {
                weight[nxt].pop();
                weight[nxt].push(nxt_cost);
                pq.push({-nxt_cost, nxt});
            }
        }
    }
}
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    int a, b ,c;
    f(i, 0, m) {
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    dijkstra();
    f(i, 1, n+1) {
        if (weight[i].size() == k) cout << weight[i].top() << '\n';
        else cout << -1 << '\n';
    }
    return 0;
}