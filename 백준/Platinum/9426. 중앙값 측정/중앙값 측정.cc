#include <iostream>
#include <vector>
#include <algorithm>
#define f(a, b, c) for(int a=b;a<c;++a)
using namespace std;

const int MAX_C = 65535;
const int MAX_N = 250000;

int tree[3*(MAX_N+2)];
int arr[MAX_N+1];
int n, k;


void update(int node, int l, int r, int val, int offset = 1) {
    if (val < l || val > r) return;
    if (l == r) {
        tree[node] += offset;
        return;
    }
    int mid = (l + r) >> 1;
    update(2*node, l, mid, val, offset);
    update(2*node + 1, mid+1, r, val, offset);

    tree[node] = tree[2*node] + tree[2*node + 1];
}

int query(int node, int l, int r, int cnt) {
    if (l == r) return l;
    int mid = (l + r) >> 1;

    if (tree[2*node] >= cnt) return query(2*node, l, mid, cnt);
    else return query(2*node+1, mid+1, r, cnt-tree[2*node]);
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;

    for (int i = 1; i <= n; ++i) cin >> arr[i];

    for (int i = 1; i < k; ++i) {
        update(1, 0, MAX_C, arr[i],1);
    }
    long long ans = 0;
    for (int i = k; i <= n; ++i) {
        update(1, 0, MAX_C, arr[i], 1);
        int res = query(1, 0, MAX_C, k/2 + k%2);
        ans += 1LL * res;
        update(1, 0, MAX_C, arr[i-k+1], -1);
    }
    cout << ans;

    return 0;
}