#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
#define f(a, b, c) for (int a = b; a < c; ++a)
#define INF (int)1e9
const int max_node = 1e3+1;

int n, m;
int dist[max_node];
int path[max_node]; //

vector<pair<int, int> > gh[max_node];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    f(i, 0, m) {
        int n1, n2, cost; cin >> n1 >> n2 >> cost;
        gh[n1].push_back({n2, cost});
        gh[n2].push_back({n1, cost});
    }
    f(i, 1, n+1) dist[i] = INF;
    dist[1] = 0;
    path[1] = 1;
    priority_queue<pair<int ,int> > pq;
    pq.push({0, 1});

    //다익스트라 알고리즘
    while (!pq.empty()) {
        int cost = -pq.top().first;
        int loc = pq.top().second;
        pq.pop();

        if (cost > dist[loc]) continue;

        for (auto &[nxt, need_cost] : gh[loc]) {
            //더 적은 코스트 경로 존재하면, 해당되는 값과, 그 경로를 업데이트
            if (need_cost + cost < dist[nxt]) {
                path[nxt] = loc;
                dist[nxt] = (need_cost + cost);
                pq.push({-dist[nxt], nxt});
            }
        }
    }

    // f(i, 1, n+1) {
    //     cout << i <<"---\n";
    //     cout <<"dist : " << dist[i] <<'\n';
    //     cout <<"path : " << path[i] <<'\n';
    // }

    cout << n-1 <<'\n';
    f(i, 2, n+1) {
        cout << i << ' ' <<path[i] <<'\n';
    }
    return 0;
}