#include <iostream>
using namespace std;
const int inf = 1e5+1;
#define f(a, b, c) for(int a = b; a < c; ++a)

int arr[inf], dp[inf], prefix[inf];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    f(i, 1, n+1) cin >> arr[i];
    f(i, 1, n+1) prefix[i] = prefix[i-1] + arr[i];
    f(i, 1, n+1) dp[i] = max(dp[i-1] + arr[i], arr[i]);
    int ans = 0;
    f(i, m, n+1) {
        ans = max(ans, (prefix[i] - prefix[i-m]) + max(dp[i-m], 0));
    }
    cout << ans;
    return 0;
}