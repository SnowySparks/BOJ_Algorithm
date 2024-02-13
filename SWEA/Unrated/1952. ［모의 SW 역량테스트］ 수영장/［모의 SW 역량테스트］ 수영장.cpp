#include <iostream>
#include <cstring>
using namespace std;
const int inf = 1e9;
#define f(a, b, c) for (int a=b;a<c;++a)

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    int inp[4];
    int arr[13];
    int dp[13];
    dp[0] = 0;
    f(tc, 1, t+1) {
        f(i, 0, 4) cin >> inp[i];
        f(i, 1, 13) {
            cin >> arr[i];
            dp[i] = inf;
        }

        f(i, 1, 13) {
            dp[i] = dp[i-1]+min(inp[0]*arr[i],inp[1]);
            if (i >= 3) {
                dp[i] = min(dp[i],dp[i-3] + inp[2]);
            }
        }
        cout << '#'<<tc<<' '<<min(dp[12],inp[3]) <<'\n';
    }
    return 0;
}