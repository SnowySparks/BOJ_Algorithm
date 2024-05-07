#include <iostream>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)

int dp[101][101][2][2]; //w(x), h(y), 여기로 왔는 dir(0 : w방향, 1 : h방향), 다음 이동시 방향꺽기 가능여부 형태 (0:가능, 1:불가능)
// 0 : w 방향, 1 : h 방향
int w, h;
int mod = 1e5;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> w >> h;
    f(i, 1, w+1) dp[i][1][0][0] = 1;
    f(i, 1, h+1) dp[1][i][1][0] = 1;

    f(i, 2, w+1) {
        f(j, 2, h+1) {
            dp[i][j][1][0] = (dp[i][j-1][1][0] + dp[i][j-1][1][1])%mod;
            dp[i][j][1][1] = dp[i][j-1][0][0]; 
            dp[i][j][0][0] = (dp[i-1][j][0][1] + dp[i-1][j][0][0])%mod;
            dp[i][j][0][1] = dp[i-1][j][1][0];
        }
    }
    cout << (dp[w][h][1][0] + dp[w][h][1][1] + dp[w][h][0][1] + dp[w][h][0][0])%mod;

    // f(i, 1, h+1) {
    //     f(j, 1, w+1) {
    //         cout << (dp[j][i][0][0] + dp[j][i][1][0] + dp[j][i][0][1] + dp[j][i][1][1]) % mod << ' ';
    //     }
    //     cout << '\n';
    // }
    return 0;
}