#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int max_v = 1e5+1;
using ll = long long;
const ll inf = 1e18;
vector<pair<int, ll> > adj[max_v];

ll dist[max_v];
bool isdest[max_v];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n, m, k; cin >> n >> m >> k;
    if (n == k) {
        cout << 0 <<'\n' << 1 << '\n';
        return 0;
    }
    vector<int> dest(k);
    for (int i = 1; i <= n; ++i) dist[i] = inf;
    int fr, to, cost;

    // 단방향에서 출발점 -> 도착점 거리 
    // 단방향 그래프 간선들 전부 뒤집은 상태애서 도착점 -> 출발점 거리 는 동치
    while (m--)
    {
        cin >> fr >> to >> cost;
        adj[to].push_back({fr, cost});
    }

// 출발점 여러개에 대한 미리 선 처리
    priority_queue<pair<ll, int> > pq; // 누적거리, 노드
    for (int i = 0 ; i < k; ++i) {
        cin >>dest[i];
        isdest[dest[i]] = true;
        dist[dest[i]] = 0;
        pq.push({0, dest[i]});
    }

// 다익스트라
    while (!pq.empty())
    {
        int loc = pq.top().second;
        ll pre_dist = - pq.top().first;
        pq.pop();

        if (dist[loc] < pre_dist) continue;

        for (auto &[nxt, d] : adj[loc]) {
            ll new_dist = d + pre_dist;
            if (dist[nxt] > new_dist) {
                dist[nxt] = new_dist;
                pq.push({-new_dist, nxt});
            }
        }
    }

    int ans_loc = -1;
    ll ans_dist = -1;

// 가장 먼 거리 찾기
    for (int i = 1; i <= n; ++i) {
        if (isdest[i]) continue;
        if (dist[i] > ans_dist) {
            ans_loc = i;
            ans_dist = dist[i];
        }
    }
    cout << ans_loc <<'\n' << ans_dist;
    return 0;
}