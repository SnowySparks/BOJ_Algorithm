#include <iostream>
using namespace std;
const long long mod = 1000000007;
using ll = long long;
ll dp[1000001];
int main(void)
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    dp[0] = 1; dp[1] = 2; dp[2] = 7;
    if (n <= 2) {
        cout << dp[n];
        return 0;
    }
    for (int i =3;i <= n; ++i) {
        dp[i] = (3*dp[i-1] + dp[i-2] - dp[i-3] + mod)%mod;
    }
    cout << dp[n];
    return 0;
}
