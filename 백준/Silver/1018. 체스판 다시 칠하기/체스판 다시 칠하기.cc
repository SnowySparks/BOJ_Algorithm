#include <iostream>
#include <cstring>
using namespace std;

int n, m, k=8;
string inp[50];
int dp[51][51];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int ans = 1<<30;
    for (int i = 0; i < n; ++i) {
        cin >> inp[i];
    }
    //가장 최상위 왼쪽 위치가 B, W 인가를 가정하고, 해당 위치에 맞는 값이면 0, 아니면 1를 두고
    //누적합을 시키는 방법

    //가장 최상위가 B일때
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if ((i+j)%2 == 0 && inp[i-1][j-1] == 'W') dp[i][j] = 1;
            else if ((i+j)%2 == 1 && inp[i-1][j-1] == 'B') dp[i][j] = 1;
            else dp[i][j] = 0;

            dp[i][j] += (dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]);
        }
    }

    for (int i = n; i >= k; --i) {
        for (int j = m; j >=k; --j) {
            ans = min(ans, dp[i][j] - dp[i-k][j] - dp[i][j-k] + dp[i-k][j-k]); 
        }
    }

    //가장 최상위가 W일때
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if ((i+j)%2 == 0 && inp[i-1][j-1] == 'B') dp[i][j] = 1;
            else if ((i+j)%2 == 1 && inp[i-1][j-1] == 'W') dp[i][j] = 1;
            else dp[i][j] = 0;

            dp[i][j] += (dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]);
        }
    }
    for (int i = n; i >= k; --i) {
        for (int j = m; j >=k; --j) {
            ans = min(ans, dp[i][j] - dp[i-k][j] - dp[i][j-k] + dp[i-k][j-k]); 
        }
    }
    cout << ans;
    return 0;
}