#include <iostream>
#include <cmath>
using namespace std;
using ll = unsigned long long;
ll powr(ll a, ll n) {
    ll res = 1, mul = a;
    while(n) {
        if (n&1) res*=mul;
        mul*=mul;
        n>>=1;
    }
    return res;
}
ll const thr = powr(10,12);

int main(void) {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll N; cin >> N;
    ll p = 1, r=2, n=3; // 첫째항, 공비, 등비수열 원소 수(연속)
    bool fd = false;
    ll max_r = (ll)floor(-0.5 + 0.5*sqrt(4*N - 3));
    while (r <= max_r) {
        n = 3;
        ll tmp = r*r*r;
        while (n <= 50) {
            if ( (N * (r -1)) % (tmp - 1) == 0) {
                fd = true;
                p = N*(r-1)/(tmp-1);
                break;
            }
            if (tmp> N) break;
            n++;
            tmp*=r;
        }
        if (fd) break;
        r++;
    }
    if (!fd) {
        cout << -1; return 0;
    }

    cout << n << '\n';
    for (ll k = 0; k < n; k++) {
        cout << p*powr(r,k) << ' ';
    }
    return 0;
}