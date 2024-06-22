#include <iostream>
#include <cstring>
#include <vector>
#define f(a, b, c) for(int a=b;a<c;++a)
using namespace std;
const long long inf =1e14;
const int max_n = 1e5+10;
int n;
int arr[max_n][2];
long long dp[max_n][5];

int mv[5][2] = {
    {0, 0},
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1},
};

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    f(i, 0, n+1) cin >> arr[i][0] >> arr[i][1];
    dp[0][0] = 0;
    f(i, 1, 5) dp[0][i] = 1;

    f(i, 1, n+1) {
        f(j, 0, 5) { //현재 있을 수 있는 위치 방향
            dp[i][j] = inf;
            f(k, 0, 5) { //직전에 있었던 위치 방향
                long long r1 = arr[i-1][0] + mv[k][0], c1 = arr[i-1][1] + mv[k][1];
                long long r2 = arr[i][0] +  mv[j][0], c2 = arr[i][1] + mv[j][1];
                dp[i][j] = min(dp[i][j], dp[i-1][k] + abs(r2-r1) + abs(c2-c1)); 
            }
        }
    }
    long long ans = inf;
    f(i, 0, 5) {
        ans = min(ans, dp[n][i]);
    }
    cout << ans;
    return 0;
}