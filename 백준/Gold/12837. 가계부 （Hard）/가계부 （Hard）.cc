#include <iostream>
#include <cstring>
using ll = long long;
using namespace std;
const int max_n = 1e6+10;
ll arr[max_n];
ll tree[3*max_n];
int n, m;

void update(int node, int l, int r, int target, ll val) {
    if (r < target || l > target) return;
    tree[node] += val;
    if (l == r) return;
    int mid = (l + r) >> 1;
    update((node << 1), l, mid, target, val);
    update((node << 1) + 1, mid+1, r, target, val);
}

ll query(int node, int l, int r, int fr, int to) {
    if (to < l || r < fr) return 0L;
    else if (fr <= l && r <= to) return tree[node];
    int mid = (l + r ) >> 1;
    return query(2*node, l, mid, fr, to) + query(2*node+1, mid+1,r,fr,to);
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    cin >> n >> m;
    int cmd, p, q; ll x;
    while (m--)
    {
        cin >> cmd;
        switch (cmd)
        {
        case 1:
            cin >> p >> x;
            update(1, 0, n-1, p-1, x);
            break;
        
        case 2:
            cin >> p >> q;
            cout << query(1, 0, n-1, p-1, q-1) << '\n';
            break;
        }
    }
    
}