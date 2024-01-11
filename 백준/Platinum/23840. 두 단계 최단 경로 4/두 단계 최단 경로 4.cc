#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
using ll = long long;
#define f(a,b,c) for (int a=b;a<c;a++)
const int max_node = 1e5+1;
const ll inf = (1LL << 60);
vector<pair<int,ll> > gh[max_node]; //그래프, {to , cost};
int n, m, u ,v, w, x, z, p;
int mapping[22]; // idx : tsp 노드번호 , 값 : 그래프 노드(원 노드 값)
ll arr[22][22]; // 출발점 -> P개 -> 도착점
ll dp[21][1<<21]; //
ll dist[max_node]; // 다익스트라 알고리즘에 사용할 거리값

void dijkstra(int start) {
    f(i,1,n+1) dist[i] = inf;
    dist[start] = 0;
    priority_queue< pair<ll,int> > pq;
    pq.push({0,start});

    while (!pq.empty()) {
        int loc = pq.top().second;
        ll cost = -pq.top().first;
        pq.pop();
        if (dist[loc] < cost) continue;

        for (pair<int, int> p : gh[loc]) {
            ll ncost = cost + p.second;
            int nxt = p.first;
            if (dist[nxt] > ncost) {
                dist[nxt] = ncost;
                pq.push({-ncost,nxt});
            }
        }
    }
}

ll tsp(int loc, int state) {
    if (state == ( (1<< (p+1))-1)) return arr[loc][p+1];
    ll &res = dp[loc][state];
    if (res != -1) return res;
    res = inf;

    f(i,1,p+1) {
        if ((state & (1<<i)) || arr[loc][i] == inf) continue;
        res = min(res, tsp(i, state|(1<<i)) + arr[loc][i]);
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    f(i,0,m) {
        cin >> u >> v >> w;
        gh[u].push_back({v,w});
        gh[v].push_back({u,w});
    }
    cin >> x >> z;
    cin >> p;
    f(i,1,p+1) cin >> mapping[i];
    mapping[0] = x; mapping[p+1] = z;

    f(i,0,p+2) {
        f(j,0,p+2) {
             arr[i][j] = inf; }
        arr[i][i] = 0;
    }
    f(i,0,p+1) {
        fill(dp[i],dp[i] + (1<<(p+1)),-1);
    }

    f(i,0,p+2) {
        dijkstra(mapping[i]);
        f(j,0,p+2) {
            if (i==j) {arr[i][j] = 0; continue;}
            arr[i][j] = min(arr[i][j], dist[mapping[j]]);
            arr[j][i] = arr[i][j];
        }
    }
    ll res = tsp(0,1);
    cout << (res >= inf ? -1 : res);
    return 0;

}