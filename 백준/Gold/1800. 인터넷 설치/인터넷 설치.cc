#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int inf = 2e9;
const int maxn = 1e3+10;
int n, p, k;
int dist[maxn];
bool free_edge[maxn][maxn];

vector<pair<int ,int> > adj[maxn]; // to , cost


bool dijkstra(int threshold_cost) {
    fill(dist, dist+n+1, inf);
    memset(free_edge, 0, sizeof(free_edge));
    dist[1] = 0;
    priority_queue<pair<int ,int> > pq;
    pq.push({0, 1});

    while (!pq.empty())
    {
        int loc = pq.top().second, now_cost = -pq.top().first; pq.pop();

        if (dist[loc] < now_cost) continue;
        for (auto &[nxt, w] : adj[loc]) {
            int new_cost = now_cost + (w > threshold_cost);
            if (dist[nxt] > new_cost) {
                dist[nxt] = new_cost;
                pq.push({-new_cost, nxt});
            }
        }
    }
    if (dist[n] == inf) return false;
    return dist[n] <= k;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> p >> k;
    int fr, to, cost;
    int min_cost = 0, max_cost = -1;
    while (p--)
    {
        cin >> fr >> to >> cost;
        adj[fr].push_back({to, cost});
        adj[to].push_back({fr, cost});
        max_cost = max(max_cost, cost);
    }
    max_cost += 10;
    int ans = inf;

    while (min_cost <= max_cost)
    {
        int mid = (min_cost + max_cost) >> 1;
        bool res = dijkstra(mid);
        if (res) {
            ans = mid;
            max_cost = mid - 1;
        }
        else {
            min_cost = mid + 1;
        }
    }
    cout << ((ans == inf ) ? -1 : ans) ;
    return 0;
}

// 간선의 비용에서 임계값 이상이면 1, 아니면 0으로 임의설정하고 다익스트라 돌리기
// 그리고 임계값 결정은 이분탐색