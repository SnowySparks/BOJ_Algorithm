#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#define f(a, b, c) for(int a=b;a<c;++a)
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int max_n = 75001;
int n;
ll cnt[max_n];
ll tree[max_n*4];
pair<int, int> pts[max_n];

void init(int node, int l, int r) {
    if (l == r) {
        tree[node] = cnt[l];
        return;
    }
    int mid = (l + r) >> 1;
    init(node << 1, l, mid);
    init((node << 1) + 1, mid+1, r);
    tree[node] = tree[2*node + 1] + tree[2*node];
    return;
}
void update(int node, int l, int r, int idx) {
    if (idx < l || idx > r) return;
    --tree[node];
    if (l == r) return;
    int mid = (l+r) >> 1;
    update(2*node, l, mid, idx);
    update(2*node +1, mid+1, r, idx);
    return;
}

ll query(int node, int l, int r, int fr, int to) {
    if (r < fr || to < l) return 0;
    if (fr <= l && r <= to) return tree[node];
    int mid = (l+r) >> 1;
    return query(2*node,l,mid,fr,to) + query(2*node+1, mid+1, r, fr, to);
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    unordered_map<int ,int> grid;
    while (T--)
    {
        cin >> n;
        grid.clear();
        memset(tree, 0, sizeof(tree));
        memset(cnt, 0, sizeof(cnt));
        f(i, 0, n) cin >> pts[i].first >> pts[i].second;

        // x축 오름차순 - 좌표 압축용
        sort(pts, pts+n);
        f(i, 0, n) {
            if (grid.find(pts[i].first) == grid.end()) grid[pts[i].first] = (int) grid.size();
            cnt[grid[pts[i].first]]++;
        }
        int grid_size = (int) grid.size();
        init(1, 0, grid_size-1);
        // cout << tree[1] << '\n';
        // y축 내림차순, 동일 y대해선 x 오름차순
        sort(pts, pts+n, [](const pii &a, const pii &b){
            if (a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });
        ll ans = 0;
        f(i, 0, n) {
            int loc = grid[pts[i].first];
            update(1, 0, grid_size-1, loc);
            ll a = query(1, 0, grid_size-1, loc, grid_size-1);
            ans += a;
        }
        cout << ans << '\n';
    }
    return 0;
}