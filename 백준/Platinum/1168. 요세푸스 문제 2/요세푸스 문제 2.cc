#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
#define f(a,b,c) for(int a = b; a < c; a++)
const int mt = 1e5+10;
const int inf = 1e5;
int tree[3 * mt];
int n, k;

int init(int node, int l, int r) {
    if (l == r) return tree[node] = 1;
    int mid = (l + r) >> 1;
    return tree[node] = init(2*node, l, mid) + init(2*node + 1, mid +1, r);
}

int query(int node, int l, int r, int k) {
    // cout << l <<' ' << r <<' ' << k << '\n';
    tree[node]--;
    if (l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    if (tree[2*node] >= k) {
        return query(2*node, l, mid, k);
    }
    else {
        return query(2*node+1, mid+1, r, k - tree[2*node]);
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    cin >> n >> k;
    init(1, 1, n);
    int nxt = 1;
    vector<int> ans;
    while (tree[1])
    {
        nxt += (k-1);
        if (nxt % tree[1] == 0) nxt=tree[1];
        else nxt%=tree[1];
        ans.push_back(query(1, 1, n, nxt));

    }

    cout << '<';
    for (int i = 0; i < n-1; ++i) {
        cout << ans[i] <<", ";
    }
    cout << ans.back() <<">\n";
    

    return 0;
}