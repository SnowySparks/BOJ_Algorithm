#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 1e9;
using pii = pair<int, int>; 

int n, m; // node, edge 수
int s, e; //start, end
int dist[501];
bool block_path[501][501];

vector<pii> adj[501]; // cost, nxt


// 역방향 탐색 및 방문판별기
vector<int> radj[501];
bool vis[501];

void clean() {
    for(int i = 0; i <= n; ++i) {
        adj[i].clear();
        radj[i].clear();
    }
    memset(block_path, 0, sizeof(block_path));
    memset(vis, 0, sizeof(vis));
}

void dist_set() {
    for (int i = 0; i <= n; ++i) dist[i] = inf;
    dist[s] = 0;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int u, v, p;
    priority_queue<pii> pq;
    queue<int> q;
    while (1)
    {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        cin >> s >> e;
        clean();

        while (m--)
        {
            cin >> u >> v >> p;
            adj[u].push_back({p, v});
        }
        
        // first dijkstra
        dist_set();
        pq.push({0, s});

        while (!pq.empty())
        {
            int cost =  -pq.top().first, loc = pq.top().second; pq.pop();
            if (dist[loc] < cost) continue;

            for (auto &[c, nxt] : adj[loc]) {
                int new_cost = c + cost;
                if (dist[nxt] == new_cost) {
                    // 해당 간선을 통해 누적된 비용이 같은 경우. 이것도 일단 후보군에 올림
                    radj[nxt].push_back(loc);
                }
                else if (dist[nxt] > new_cost) {
                    // 더 짧은 경로가 있는 것이므로. 기존 탐색한 역방향 그래프 정보 새로 지우고 다시 추가
                    radj[nxt].clear();
                    radj[nxt].push_back(loc);
                    dist[nxt] = new_cost;
                    pq.push({-new_cost, nxt});
                }
            }
        }

        if (dist[e] == inf) {
            cout << -1 << '\n';
            continue;
        }

        // 역방향 그래프. 도착점 -> 시작점 가는 모든 경로를 배제하기 위함
        q.push(e);
        vis[e] = true;
        while (!q.empty())
        {   
            int loc = q.front(); q.pop();
            if (loc == s) continue;
            for (int nxt : radj[loc]) {
                // 역방향으로 연결된 간선은 다시 정방향 입장에서 해당 경로 블락
                block_path[nxt][loc] = true;
                if (!vis[nxt]) {
                    q.push(nxt);
                    vis[nxt] = true;
                }
            }
        }

        // 두번째 다익스트라, 
        dist_set();
        pq.push({0, s});


        while (!pq.empty())
        {
            int cost =  -pq.top().first, loc = pq.top().second; pq.pop();
            if (dist[loc] < cost) continue;

            for (auto &[c, nxt] : adj[loc]) {
                if (block_path[loc][nxt]) continue;
                int new_cost = c + cost;
                if (dist[nxt] > new_cost) {
                    dist[nxt] = new_cost;
                    pq.push({-new_cost, nxt});
                }
            }
        }

        cout << (dist[e] == inf ? -1 : dist[e]) << '\n';
    }
    return 0;
}

// 다익스트라를 통해서 최단 경로가 될 수 있는 "모든" 경로를 찾는 문제
// 