#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int n, max_depth;
const int mn = 1E5+1;
const int max_val = 0x7f7f7f7f;
int level[mn];
int dist[mn]; // 1를 루트로 잡을때 나머지 노드들의 거리 (1 _ 노드 사이 거리)
int p[mn][19];
int max_d[mn][19];
int min_d[mn][19];
vector<pair<int ,int> > adj[mn];

void set_tree(int node, int pnode, int dist) {
    // 일반 lca 구성
    level[node] = level[pnode] + 1;
    p[node][0] = pnode;

    // 자기 위 부모에 대한 거리 갱신
    min_d[node][0] = dist;
    max_d[node][0] = dist;

    // 기본적인 거리
    // dist[node][i] == dist[node][i-1] + dist[ p[node][i-1] ][i - 1]를 응용한 것
    for (int i = 1; i < 19; ++i) {
        p[node][i] = p[ p[node][i-1] ][i-1];
        max_d[node][i] = max(max_d[node][i-1], max_d[ p[node][i-1] ][i-1]);
        min_d[node][i] = min(min_d[node][i-1], min_d[ p[node][i-1] ][i-1]);
    }

    for (auto &[nxt, dst] : adj[node]) {
        if (nxt == pnode) continue;
        set_tree(nxt, node, dst);
    }

}

pair<int, int> lca(int a, int b) {
    // 같은 노드에 대한 입력은 미리 처리
    if (a == b) return {0, 0}; 


    int max_dist = 0;
    int min_dist = max_val;
    if (level[a] < level[b]) swap(a, b);
    int lvdiff = level[a] - level[b];

    for (int i = 0; lvdiff; ++i) {
        if (lvdiff & 1) {
            max_dist = max(max_dist, max_d[a][i]);
            min_dist = min(min_dist, min_d[a][i]);
            a = p[a][i];
        }
        lvdiff >>=1;
    }

    if (a == b) {
        return {min_dist, max_dist};
    }

    for (int i = 18; i >= 0; --i) {
        if (p[a][i] != p[b][i]) {
            max_dist = max(max_dist, max(max_d[a][i], max_d[b][i]));
            min_dist = min(min_dist, min(min_d[a][i], min_d[b][i]));
            a = p[a][i];
            b = p[b][i];
        }
    }
    max_dist = max(max_dist, max(max_d[a][0], max_d[b][0]));
    min_dist = min(min_dist, min(min_d[a][0], min_d[b][0]));
    return {min_dist, max_dist};
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r" , stdin);
    cin >> n;
    int a, b, cost;
    for (int i = 0; i < n-1; ++i) {
        cin >> a >> b >> cost;
        adj[a].push_back({b, cost});
        adj[b].push_back({a, cost});
    }
    //초기화
    for(int i = 1; i <= n; ++i) fill(min_d[i], min_d[i]+19, max_val);
    set_tree(1, 0, 0);
    int k; cin >> k;
    while (k--)
    {
        cin >> a >> b;
        pair<int ,int> res = lca(a, b);
        cout << res.first <<' ' <<res.second <<'\n';
    }
    
    return 0;
}