#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define f(a, b, c) for (int a = b; a < c; ++a)
int n;
const int max_node = 1e5+3;
vector<int> adj[max_node];
int p[max_node][18], lv[max_node];

void reset() {
    f(i, 0, n+1) adj[i].clear();
    memset(p, 0, sizeof(p));
    memset(lv, 0, sizeof(lv));
}


int lca(int a, int b) {
    if (a == 1 || b == 1) return 1;
    if (a == b) return a;
    if (lv[a] < lv[b]) swap(a, b);

    int lvdiff = lv[a] - lv[b];

    for (int i = 0; lvdiff; ++i) {
        if (lvdiff & 1) {
            a = p[a][i];
        }
        lvdiff >>=1;
    }

    if (a == b) return a;

    for (int i = 17; i >= 0; --i) {
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
    int T, tmp; cin >> T;
    f(tc, 1, T+1) {
        int cnt = 0;
        cin >> n;
        reset();
        lv[1] = 1;
        f(i, 2, n+1) {
            cin >> tmp;
            adj[tmp].push_back(i);

            p[i][0] = tmp;
            lv[i] = lv[tmp]+1;
            f(k, 1, 18) p[i][k] = p[p[i][k-1]][k-1];
        }

        // f(i, 1, n+1) sort(adj[i].begin(), adj[i].end());

        queue<int> q;
        q.push(1);
        int before = 1;
        long long ans = 0;
        int loc = 1;
        
        while (!q.empty())
        {
            before = loc;
            loc = q.front(); q.pop();
            int lca_loc = lca(loc, before);
            // cout << "check:" <<loc << ' '<< before <<' ' <<lca_loc << ' ' << (lv[loc] + lv[before] - 2*lv[lca_loc]) << '\n';
            ans += 1LL * (lv[loc] + lv[before] - 2*lv[lca_loc]);

            for (int nxt : adj[loc]) {
                q.push(nxt);
            }
        }

        cout << '#' << tc << ' ' << ans << '\n';
    }


    return 0;
}