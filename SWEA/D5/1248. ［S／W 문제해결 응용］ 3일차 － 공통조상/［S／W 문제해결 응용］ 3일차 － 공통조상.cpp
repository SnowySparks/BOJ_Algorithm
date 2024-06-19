#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#define f(a, b, c) for (int a = b; a<c;++a)
using namespace std;
const int maxv = 10001;
int v, e, a, b;

int p[maxv][16];
int child[maxv][2];
int lv[maxv];
int cnt[maxv];

void set_tree(int st) {
    queue<int> q;
    q.push(st);
    lv[st] = 1;
    while (!q.empty())
    {
        int node = q.front(); q.pop();
        f(i, 1, 16) p[node][i] = p[ p[node][i-1] ][i-1];

        for (int nxt : child[node]) {
            if (nxt) {
                q.push(nxt);
                lv[nxt] = lv[node] + 1;
            }
        }
    }
}

int dfs(int n) {
    cnt[n] = 1;
    if (child[n][0] == 0) {
        return 1;
    }

    for (int nxt : child[n]) {
        if (nxt) cnt[n] += dfs(nxt);
    }
    return cnt[n];
}

int lca() {
    if (lv[a] < lv[b]) swap(a, b);
    int lvdiff = lv[a] - lv[b];
    for (int i = 0;lvdiff;i++) {
        if (lvdiff & 1) {
            a = p[a][i];
        }
        lvdiff >>= 1;
    }
    if (a == b) return a;
    for (int i =15; i >= 0; --i) {
        if (p[a][i] != p[b][i]) {
            a = p[a][i];
            b = p[b][i];
        }
    }
    return p[a][0];
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    int fr, to;
    f(tc, 1, T+1) {
        cin >> v >> e >> a >> b;
        memset(child, 0, sizeof(child));
        memset(lv, 0, sizeof(lv));
        memset(cnt, 0, sizeof(cnt));
        f(i, 0, e) {
            cin >> fr >> to;
            p[to][0] = fr;
            if (child[fr][0]) child[fr][1] = to;
            else child[fr][0] = to;
        }
        set_tree(1);
        dfs(1);
        int sub_r = lca();
        cout << '#' << tc <<' ' << sub_r <<' ' << cnt[sub_r]<< '\n';
    }
    return 0;
}