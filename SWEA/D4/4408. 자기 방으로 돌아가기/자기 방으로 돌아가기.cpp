#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int dp[202];
int tonode(int x) {
    if (x%2) return (x+1)/2;
    else return x/2;
}
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int tc = 1; tc <=t; ++tc) {
        int n; cin >> n;
        memset(dp, 0, sizeof(dp));

        for (int i = 0; i < n; ++i) {
            int a, b; cin >> a >> b;
            if (a > b) swap(a, b);
            a = tonode(a);
            b = tonode(b);

            dp[a]++; dp[b+1]--;
        }
        int ans = 0;
        for (int i = 1; i <= 200; i++) {
            dp[i] +=dp[i-1];
            ans = max(dp[i], ans);
        }

        cout << '#' << tc <<' ' << ans << '\n';
    }
    return 0;
}