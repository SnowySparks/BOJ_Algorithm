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

priority_queue<pii> pq; // -cost, node 순서
//b_path : 해당 간선은 블락
int dijkstra(int start = 1,int end = n, const pair<int ,int> &b_path = {-1, -1}) {
    fill(dist, dist + n +1, inf);
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int cost = -pq.top().first, node =pq.top().second;
        pq.pop();
        for (auto &[nxt, add_cost] : gh[node]) {
            int nxt_cost = cost + add_cost;
            if (b_path.first == node && b_path.second == nxt || b_path.first == nxt && b_path.second == node) continue;
            if (dist[nxt] < nxt_cost) continue;
            path[nxt] = node;
            dist[nxt] = nxt_cost;
            pq.push({-nxt_cost, nxt});
        }
    }
    return (dist[end] == inf ? -1 : dist[end]);
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    cin >> n >> m;
    int a, b, c;
    for (int i = 0 ; i < m; ++i) {
        cin >> a >> b >> c; 
        gh[a].push_back({b, c});
        gh[b].push_back({a, c});
    }

    //출발, 도착지점 길이 단 1개이면 여기만 차단하면 경로 완전 끊긴거니 
    if ((int) gh[1].size() == 1 || (int) gh[n].size() == n) {
        cout << -1;
        return 0;
    }

    int min_path = dijkstra();
    vector<pii> block_list;
    int ans = 0;
    int idx = n, nxtidx = -1;
    while (idx != 1)
    {
        nxtidx = path[idx];
        block_list.push_back({idx, nxtidx});
        idx = nxtidx;
    }

    for (pii p : block_list) {
        int res = dijkstra(1, n, p);
        if (res == -1) {
            cout << -1;
            return 0;
        }
        ans = max(ans, res - min_path);
    }
    cout << ans;
    return 0;   
}

// 다익스트라로 어느 시작점에서 다른 노드들에 대한 최단 거리구함에 있어
// 그 경로들만 모으면 트리 구조를 가짐
// 특히 1 ~ n 까지 경로 가는데에서 간선이 아무리 많아봤자 n-1개가 한계임