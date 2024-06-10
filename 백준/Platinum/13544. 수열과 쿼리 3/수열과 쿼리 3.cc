#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int max_node = 4e5+100;
vector<int> tree[max_node];
int arr[100001];

void init(int node, int l, int r) {
    if (l == r) {
        tree[node].push_back(arr[l]);
        return;
    }

    int mid = (l + r) >> 1;
    init(2*node, l, mid);
    init(2*node+1, mid+1, r);

    tree[node].resize((int)(tree[2*node].size() + tree[2*node+1].size()));
    merge(tree[2*node].begin(), tree[2*node].end(), tree[2*node+1].begin(), tree[2*node+1].end(), tree[node].begin());
    return;
}

int query(int node, int l, int r, int s, int e, int val) {
    if ( r < s || e < l) return 0;
    if ( s <= l && r <= e) {
        return tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), val);
    }
    int mid = (l + r) >> 1;
    return query(2*node, l, mid, s, e, val) + query(2*node+1, mid+1, r, s, e, val);
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int n; cin >> n;
    for (int i = 1; i <= n;++i) cin >> arr[i];
    init(1,1,n);
    int m; cin >> m;
    int a, b, c;
    int i, j, k;
    int last_ans = 0;
    while (m--)
    {
        cin >> a >> b >> c;
        i = a ^ last_ans;
        j = b ^ last_ans;
        k = c ^ last_ans;
        last_ans = query(1, 1, n, i, j, k);
        cout << last_ans << '\n';
    }
    
    return 0;
}