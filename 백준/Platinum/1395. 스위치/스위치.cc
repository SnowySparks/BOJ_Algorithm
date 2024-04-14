#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int nmax = 1e5+1;
const int inf = 4e5;
int n, q;
// 들어가는 값 : 해당 구간에서의 반전 호출 횟수. - 홀수인 경우 켜진 거고, 짝수인 경우 꺼진 거임 
int tree[inf];
int lazy[inf];

void lazy_update(int node, int l, int r) {
    if (lazy[node]) {
        if (lazy[node] & 1) { //해당 구간에서 누적된 반전 호출 횟수가 홀수일 때만 반영
            tree[node] = (r - l + 1) - tree[node]; //켜진 갯수 , 꺼진 갯수 반전
        }
        if (l!=r) {
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}


int update(int node, int l, int r, int s, int e) {
    lazy_update(node, l, r);
    if ( e < l || r < s) return tree[node];
    else if (s <= l && r <= e) {
        lazy[node]++;
        lazy_update(node, l, r);
        return tree[node];
    }

    int mid = (l + r) >> 1;
    return tree[node] = update(2*node, l, mid, s, e) + update(2*node+1, mid+1, r, s, e);
}


int query(int node, int l, int r, int s, int e) {
    lazy_update(node, l, r);
    if (s <= l && r <= e) {
        return tree[node];
    }
    else if ( e < l || r < s) return 0;

    int mid = (l + r) >> 1;
    return query(2*node, l, mid, s, e) + query(2*node+1, mid+1, r, s, e);
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    cin >> n >> q;
    int cmd, s, t;
    while (q--)
    {
        cin >> cmd >> s >> t;
        if (cmd) {
            cout << query(1, 0, n-1, s-1, t-1) << '\n';
        }
        else {
            update(1, 0, n-1, s-1, t-1);
        }
    }
    return 0;
    

    return 0;
}