#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int inf = 2e9;
using pii = pair<int, int>;
vector<pii> gh[1001]; //to, cost
int n, m; //노드, 간선 수
int path[1001];
int dist[1001]; 

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    cin >> n >> m;
    int a, b, c, cost, node;
    for (int i = 0 ; i < m; ++i) {
        cin >> a >> b >> c; 
        gh[a].push_back({b, c});
        gh[b].push_back({a, c});
    }

    fill(dist, dist + n +1, inf);
    dist[1] = 0;
    priority_queue<pii> pq;
    pq.push({0, 1});

    //첫 다익스트라
    while (!pq.empty())
    {
        cost = -pq.top().first; node =pq.top().second;
        pq.pop();
        for (auto &[nxt, add_cost] : gh[node]) {
            int nxt_cost = cost + add_cost;
            if (dist[nxt] > nxt_cost) {
            path[nxt] = node;
            dist[nxt] = nxt_cost;
            pq.push({-nxt_cost, nxt});
            }
        }
    }
    
    //다음 다익스트란
    int ans = dist[n];
    int idx = n, nxtidx = -1;

    while (idx != 1)
    {
        nxtidx = path[idx];

        pq.push({0, 1});
        fill(dist, dist + n +1, inf);
        dist[1] = 0;

        while (!pq.empty()) {
            cost = -pq.top().first; node =pq.top().second;
            pq.pop();
            for (auto &[nxt, add_cost] : gh[node]) {
                if (idx == node && nxtidx == nxt) continue;
                if (idx == nxt && nxtidx == node) continue;

                int nxt_cost = cost + add_cost;
                if (dist[nxt] > nxt_cost) {
                dist[nxt] = nxt_cost;
                pq.push({-nxt_cost, nxt}); }
            }
        }
        ans = max(ans, dist[n]);
        idx = nxtidx;
    }
    cout << ans;
    return 0;   
}

// 다익스트라로 어느 시작점에서 다른 노드들에 대한 최단 거리구함에 있어
// 그 경로들만 모으면 트리 구조를 가짐
// 특히 1 ~ n 까지 경로 가는데에서 간선이 아무리 많아봤자 n-1개가 한계임