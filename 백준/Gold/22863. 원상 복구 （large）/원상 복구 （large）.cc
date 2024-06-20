#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#define f(a, b, c) for (int a = b; a<c;++a)
using namespace std;
using ll = long long;
const int maxn = 1e6+1;
const int maxh = 51;
int n; ll k;
int s[maxn], p[maxn];

int d[maxh][maxn];

int to(int idx) {
    ll tmp = k;
    for(int i = 0; tmp ;++i) {
        if (tmp & 1) {
            idx = d[i][idx];
        }
        tmp>>=1;
    }
    return idx;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    int tmp;
    f(i, 1, n+1) cin >> s[i];
    f(i, 1, n+1) {
        cin >> tmp;
        d[0][tmp] = i;
    }

    // f(i, 1, n+1) cout << d[i][0] <<' ';
    // cout << '\n';

    // 합성함수 처리
    f(lv, 1, maxh) {
        f(i, 1, n+1) {
            d[lv][i] = d[ lv-1 ][ d[lv-1][i] ];
        }
    }

    // f(i, 1, n+1) cout << d[i][0] <<' ';
    // cout << '\n';

    f(i, 1, n+1) {
        int nxt_to = to(i);
        p[i] = s[nxt_to];
    }
    f(i, 1, n+1) cout << p[i] <<' ';    


    return 0;
}