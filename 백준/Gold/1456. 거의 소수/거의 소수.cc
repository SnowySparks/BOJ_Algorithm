#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
using ll = unsigned long;
const ll inf = 1e7;
bool arr[inf+1];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll a, b; cin >> a >> b;
    for (ll i = 2; i <= int(sqrt(inf)+1); ++i) {
        if (!arr[i]) for (ll v = i*i; v <= inf; v+=i) arr[v] = true;
    }
    int cnt = 0;
    for (ll idx = 2; idx <= inf; ++idx) {
        if (idx*idx > b) break;
        if (arr[idx]) continue;

        ll tmp = idx*idx;
        while (tmp <= b)
        {
            if (tmp >= a) ++cnt;
            tmp*=idx;
            if (tmp%idx != 0) break; //overflow대비
        }
    }
    cout << cnt;
    return 0;
}