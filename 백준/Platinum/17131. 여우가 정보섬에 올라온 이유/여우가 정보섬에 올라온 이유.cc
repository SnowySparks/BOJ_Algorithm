#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define f(a, b, c) for(int a=b;a<c;++a)
const int max_n = 2e5+1;
const ll mod = 1e9+7;
unordered_map<int, int> grid;
int n, grid_cnt = 0;
pii pts[max_n];
ll tree[max_n];
ll cnt[max_n];

void update(int i, ll diff = 1) {
    while (i <= grid_cnt)
    {
        tree[i] += diff;
        i += (i & (-i));
    }
}

ll sum(int i) {
    ll total = 0;
    while (i > 0)
    {
        total += tree[i];
        i -= (i & -i);
    }
    return total;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    cin >> n;
    f(i,0,n) cin >> pts[i].first >> pts[i].second;
    sort(pts, pts+n);
    f(i,0,n) {
        if (grid.find(pts[i].first) == grid.end()) grid[pts[i].first] = grid.size()+1;
    }
    grid_cnt = grid.size();
    f(i, 0, n) update(grid[pts[i].first]);

    // y오름차순, 그리고 x오름차순
    sort(pts, pts+n, [](const pii &a, const pii &b) {
        return (a.second == b.second) ? a.first < b.first : a.second < b.second;
    });

    int fr = -1, to = -1; //같은 y축 범위에 대한 것
    ll ans = 0;
    while (true)
    {
        fr = to + 1;
        to++;
        if (fr == n) break;
        while (to + 1 < n && pts[to+1].second == pts[fr].second) ++to;

        f(i, fr, to+1) update(grid[pts[i].first],-1);
        f(i, fr, to+1) {
            if (grid[pts[i].first] == 1 || grid[pts[i].first] == grid_cnt) continue;
            ll r = sum(grid_cnt) - sum(grid[pts[i].first]);
            ll l = sum(grid[pts[i].first]-1);
            // cout << l <<' ' << r << '\n';
            ans += r*l;
            ans %= mod;
        }
    }
    
    cout << ans%mod;
    return 0;
}