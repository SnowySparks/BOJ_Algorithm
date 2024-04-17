#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
using vl = vector< ll >;
using vll = vector< vl >;

vll operator*(const vll &a, const vll &b) {

    vll result(2, vl(2, 0));

    for (int i = 0; i < 2; i ++) {
        for (int j = 0; j <2; j ++) {
            for (int k = 0 ; k < 2; k ++) {
                result[i][j] += (a[i][k]*b[k][j] + mod);
            }
            result[i][j]%=mod;
        }
    }
    return result;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll n; cin >> n;
    if (n&1) {
        cout << 0; return 0;
    }

    n >>= 1;
    vll res = {{4, -1}, {1, 0}};
    vll ans = {{1, 0}, {0, 1}};

    while (n)
    {
        if (n&1) {
            ans = ans * res;
        }
        res = res * res;
        n >>= 1;
    }

    // for (int i = 0; i < 2; ++i) {
    //     for (int j = 0 ; j < 2; ++j) {
    //         cout << ans[i][j] <<' ';
    //     }
    //     cout << '\n';
    // }
    
    cout << ((ans[1][0] * 3) + (ans[1][1] )) % mod << '\n';

    return 0;
    
}


// f(2n+2)   [4 -1] ^ (N/2)    [3]
// f(2n)     [1  0]            [1]