#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
using ll = long long;
const int max_tn = 3e6+10;
int n, m;
ll tree[max_tn];

//node : tree node. start 1
//l, r : arr range. 
ll update(int node, int l, int r, int loc ,ll val) {
    if (loc < l || loc > r) return tree[node];
    if (l == r) return tree[node] = val;
    int mid = (l+r)>>1;
    return tree[node] = update(2*node,l,mid,loc,val) + update(2*node+1,mid+1,r,loc,val);
}

ll query(int node, int l, int r, int fr, int to) {
    if (r < fr || to < l) return 0;
    if (fr <= l && r <= to) return tree[node];
    int mid = (l+r)>>1;
    return query(2*node, l, mid, fr, to) + query(2*node+1,mid+1,r,fr,to);
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    while(m--) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 0) {
            if (b > c) swap(b, c);
            cout << query(1, 0, n-1, b-1, c-1)<<'\n';
        }
        else update(1, 0, n-1, b-1, c);
    }
    return 0;
}