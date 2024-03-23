#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
#define f(a,b,c) for(int a = b; a < c; a++)
const int mt = 2e6+2;
int tree[3 * mt];
int num, n;

int update(int node, int l, int r, int loc) {
    if (loc < l || r < loc) return tree[node];
    if (l == r) return tree[node] = tree[node] + 1;
    int mid = (l + r) >> 1;
    return tree[node] = update(2*node, l, mid, loc) + update(2*node+1, mid+1, r, loc);
}

int query(int node, int l, int r, int k) {
    // cout << l <<' ' << r <<' ' << k << '\n';
    if (l == r) {
        tree[node]--;
        return l;
    }

    int mid = (l + r) >> 1;
    if (tree[2*node] >= k) {
        tree[node]--;
        return query(2*node, l, mid, k);
    }
    else {
        tree[node]--;
        return query(2*node+1, mid+1, r, k - tree[2*node]);
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    cin >> n;
    int cmd, k;
    while (n--)
    {
        // cout << "top : " << tree[1] << '\n';
        cin >> cmd >> k;
        if (cmd == 1) update(1, 0, mt-2,k);
        else {
            cout << query(1, 0, mt-2, k) << '\n';
        }
    }

    return 0;
}