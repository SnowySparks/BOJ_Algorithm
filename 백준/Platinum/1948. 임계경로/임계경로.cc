#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int nmax = 1e5+1;
vector<pair<int, int> > adj[nmax], radj[nmax]; // < to , cost >, 정방향, 역방향
int indeg[nmax], rindeg[nmax]; // 정방향용 indegree, 역방향용 indegree
int dist[nmax], rdist[nmax];
int n, m; // 도시 갯수, 길 갯수
bool v[nmax];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    cin >> m;
    int fr, to, cost;
    for (int i = 0; i < m; ++i) {
        cin >> fr >> to >> cost;
        // 정방향
        adj[fr].push_back({to, cost});
        // 역방향
        radj[to].push_back({fr, cost});

        indeg[to]++; rindeg[fr]++;
    }

    int st, en; cin >> st >> en; //시작 종료
    // 정방향에 대해서 

    queue<int> q;
    q.push(st);

    while (!q.empty())
    {
        int loc = q.front(); q.pop();

        for (auto &[nxt, cost] : adj[loc]) {
            int nxt_cost = cost + dist[loc];
            dist[nxt] = max(dist[nxt], nxt_cost);
            indeg[nxt]--;

            if (!indeg[nxt]) q.push(nxt);
        }
    }

    // 역방향
    q.push(en);
    while (!q.empty())
    {
        int loc = q.front(); q.pop();

        for (auto &[nxt, cost] : radj[loc]) {
            int nxt_cost = cost + rdist[loc];
            rdist[nxt] = max(rdist[nxt], nxt_cost);
            rindeg[nxt]--;

            if (!rindeg[nxt]) q.push(nxt);
        }
    }

    
    // BFS 탐색
    q.push(st);
    v[st] = true;
    int ans = 0;
    while (!q.empty()) 
    {
        
        int loc = q.front(); q.pop();
        for (auto &[nxt, cost] : adj[loc]) {
            // 해당 정방향 위치의 임계값 + 다음 경로의 비용 + 다음 위치의 역방향의 임계값 == 임계경로비용 -> 임계경로노선
            if (dist[loc] + cost + rdist[nxt] == dist[en]) ++ans;
            // BFS탐색
            if (!v[nxt]) {
                v[nxt] = true;
                q.push(nxt);
            }
        }
    }
    
    cout << dist[en] << '\n' << ans;

    return 0;
}