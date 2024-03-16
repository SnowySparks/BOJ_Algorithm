#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int n, max_depth;
const int mn = 1E5+1;
const int max_val = 0x7f7f7f7f;
int level[mn];
long long dist[mn]; // 1를 루트로 잡을때 나머지 노드들의 거리 (1 _ 노드 사이 거리)
int p[mn][19];
vector<pair<int ,int> > adj[mn];

void set_tree(int node, int pnode, long long d) {
    // 일반 lca 구성
    level[node] = level[pnode] + 1;
    p[node][0] = pnode;
    dist[node] = d;

    for (int i = 1; i < 19; ++i) {
        p[node][i] = p[ p[node][i-1] ][i-1];
    }

    for (auto &[nxt, dst] : adj[node]) {
        if (nxt == pnode) continue;
        set_tree(nxt, node, d+dst);
    }

}

int lca(int a, int b) {
    if (level[a] < level[b]) swap(a, b);
    int lvdiff = level[a] - level[b];

    for (int i = 0; lvdiff; ++i) {
        if (lvdiff & 1) {
            a = p[a][i];
        }
        lvdiff >>=1;
    }

    if (a == b) {
        return a;
    }

    for (int i = 18; i >= 0; --i) {
        if (p[a][i] != p[b][i]) {
            a = p[a][i];
            b = p[b][i];
        }
    }
    return p[a][0];
}

// p[node][i] = node 에서 2^i 번째 조상을 이용한 것
int find_kth(int u, int v, int k) {
    k--; // 조정
    if (k == 0) return u; //0번째 이동 

    int lca_root = lca(u, v); // 최소 조상 노드
    if (k <= level[u] - level[lca_root]) { // u -> k 사이에 무조건 있는 k 범위
        int node = u;
        for (int i = 0; k; ++i) {
            if (k & 1) node = p[node][i];
            k>>=1;
        }
        return node;
    }
    // lca -> v 사이, 단 v -> lca탐색으로 만들기 위한 조치 후 시행
    k = level[u] + level[v] - 2*level[lca_root] - k;
    int node = v;
    for (int i = 0; k; ++i) {
        if (k & 1) node = p[node][i];
        k>>=1;        
    }
    return node;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r" , stdin);
    cin >> n;
    int a, b, cost, q, k;
    for (int i = 0; i < n-1; ++i) {
        cin >> a >> b >> cost;
        adj[a].push_back({b, cost});
        adj[b].push_back({a, cost});
    }
    set_tree(1, 0, 0);
    int m; cin >> m;
    while (m--)
    {
        cin >> q;
        if (q == 1) {
            cin >> a >> b;
            cout << dist[a] + dist[b] - 2*dist[lca(a,b)] << '\n';
        }
        else {
            cin >> a >> b >> k;
            cout << find_kth(a, b, k) << '\n';
        }
    }
    
    return 0;
}