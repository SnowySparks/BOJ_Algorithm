#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
int dp[2001][2001];// nCr mod m
// 뤼카의 정리
// nCr % p = Pi(i = 0 to k) (n_i, k_i) (mod p)
// nCr mod m = nk C rk * n(k-1) C r(k-1) * ... n0 C r0 mod m

// where n = n_k * p^k + n_(k-1) * p^(k-1) + ... + n_0 
// r = r_k * p^k + r_(k-1) * r^(k-1) + ... + r_0
// if n_i < k_i => combination(n_i, k_i) = 0

vector<int> base(ll val, int mod) {
    vector<int> ret;
    while (val) {
        ret.push_back(val % mod);
        val /= mod;
    }
    return ret;
}

int main(void) {
    ll n, k; int mod; cin >> n >> k >> mod;
    //이항분포 nCr , n <= 2000, c <= 2000
    for (int i = 0; i <= 2000; ++i) {
        dp[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = (dp[i-1][j-1] + dp[i-1][j])%mod;
        }
    }
    if (k == 0) { // nC0은 무조건 1로 귀결
        cout << 1; return 0; }
    
    vector<int> n_m = base(n,mod);
    vector<int> k_m = base(k,mod);

    int res = 1;
    int minidx = min(n_m.size(), k_m.size());

    for (int i = 0 ; i < minidx; ++i) {
        int _n = n_m[i], _r = k_m[i];
        res = (res * dp[_n][_r])%mod;
        if (res == 0) break;
    }
    cout << res;
    return 0;
}