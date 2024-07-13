#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define f(a, b, c) for (int a=b;a<c;++a)

int arr[100001];
int tree[400004];
int n, k;

void init(int node, int l, int r ) {
    if (l == r) {
        tree[node] = arr[l];
        return;
    }
    int mid = (l + r) >> 1;
    init(2*node, l, mid);
    init(2*node+1, mid+1, r);
    tree[node] = tree[2*node] * tree[2*node + 1];
}

void update(int node, int l, int r, int idx, int val) {
    if (idx < l ||r < idx) return;
    if (l == r) {
        tree[node] = val;
        arr[l] = val;
        return;
    }
    int mid = (l + r) >> 1;
    update(2*node, l, mid, idx, val);
    update(2*node + 1, mid +1, r , idx, val);

    tree[node] = tree[2*node] * tree[2*node+1];
}

int query(int node, int l, int r, int fr, int to) {
    if (r < fr || to < l) return 1;
    if (fr <= l && r <= to) return tree[node];
    int mid = (l + r) >> 1;
    return query(2*node, l, mid, fr, to) * query(2*node +1,mid +1, r, fr, to);
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r", stdin);
    char ch;
    string ans;
    int idx, val, fr, to;
    while (cin >> n >> k)
    {   
        ans = "";
        memset(arr, 0, sizeof(arr));
        memset(tree, 0, sizeof(tree));
        f(i, 0, n) cin >> arr[i];
        f(i, 0, n) arr[i] = (arr[i] > 0 ? 1 : ( arr[i] < 0 ?  -1 : 0));
        init(1, 0, n-1);
        f(i, 0, k) {
            cin >> ch;
            if (ch == 'C') {
                cin >> idx >> val;
                val = val > 0 ? 1 : (val < 0 ? -1 : 0);
                update(1, 0, n-1, idx-1, val);
            }
            else {
                cin >> fr >> to;
                int res = query(1, 0, n-1, fr-1, to-1);
                ans.push_back( (res > 0 ? '+' : (res < 0 ? '-' : '0')));
            }
        }
        cout << ans << '\n';
    }
    

    return 0;
}