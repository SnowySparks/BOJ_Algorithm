#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define f(a, b, c) for (int a = b; a < c; ++a)
using namespace std;
#define INF 200001
int n, m, k;
struct io {
    int n1, n2, t;
};
vector<int> adj[INF];
io edge[INF];
int p[INF];
int v[INF];

int parent(int x) {
    if (x == p[x]) return x;
    return p[x] = parent(p[x]);
}

bool merge(int a, int b) {
    a = parent(a);
    b = parent(b);
    if (a == b) return false;
    p[max(a, b)] = min(a, b);
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    int a, b;
    f(i, 1, n+1) p[i] = i;
    for (int i = 0; i < m; ++i) {
        cin >> edge[i].n1 >> edge[i].n2;
        adj[edge[i].n1].push_back(edge[i].n2);
        adj[edge[i].n2].push_back(edge[i].n1);
        
    }
    queue<int> q;

    while (k--)
    {   
        cin >> a;
        q.push(a);
        v[a] = 1;
    }

    while (!q.empty())
    {
        int loc = q.front(); q.pop();
        for (int &child : adj[loc]) {
            if (v[child] == 0) {
                v[child] = v[loc] + 1;
                q.push(child);
            }
        }
    }

    f(i, 0, m) {
        edge[i].t = min(v[edge[i].n1], v[edge[i].n2]);
    }

    sort(edge, edge+m, [](const io &a, const io &b) {
        return a.t > b.t;
    });
    int ans = 0;
    f(i, 0, m) {
        if (!merge(edge[i].n1, edge[i].n2)) {
            ans = edge[i].t;
            break;
        }
    }
    cout << ans;
    return 0;
}