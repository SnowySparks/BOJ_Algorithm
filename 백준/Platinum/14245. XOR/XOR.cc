#include <iostream>
#define MAXN 500000
using namespace std;
int n, arr[MAXN], tree[MAXN*4], lazy[MAXN*4];

int init(int node, int l ,int r) {
    if (l == r) return tree[node] = arr[l];
    int mid = (l + r) >> 1;
    return tree[node] = init(2 * node, l , mid) ^ init(2 *node + 1, mid + 1, r);
}

void lazy_update(int node, int l, int r) {
    if (lazy[node]) {
        tree[node] ^= (((r - l + 1)&1) * lazy[node]);
        if (l != r) {
            lazy[2*node] ^= lazy[node];
            lazy[2*node+1] ^= lazy[node];
        }
        lazy[node] = 0;
    }
}

int update(int node, int l, int r, int fr, int to, int val) {
    lazy_update(node, l, r);
    if (r < fr || l > to) return tree[node];
    else if (fr <= l && r <= to) {
        lazy[node] = val;
        lazy_update(node, l, r);
        return tree[node];
    }
    else {
        int mid = (l + r) >> 1;
        return tree[node] = update(2 * node, l, mid, fr, to , val) ^ update(2 *node + 1, mid+1, r, fr, to , val);
    }
}

int query(int node, int l, int r, int loc) {
    lazy_update(node, l, r);
    if (loc < l || loc > r) return 0;
    else if ( l == r) return tree[node];
    else {
        int mid = (l + r) >> 1;
        return query(2 * node, l, mid, loc) ^ query(2 *node + 1, mid + 1, r, loc);
    }
}


int main(void){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for (int i = 0 ; i < n; ++i) cin >> arr[i];
    init(1, 0, n-1);
    int q; cin >> q;
    int cmd, a, b, c;
    while (q--)
    {
        cin >> cmd;
        if (cmd == 1) {
            cin >> a >> b >> c;
            update(1, 0, n-1, a, b, c);
        }
        else {
            cin >> a;
            cout << query(1, 0, n-1, a) <<'\n';
        }
    }
    return 0;
}