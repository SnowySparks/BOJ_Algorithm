#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define minf -(1<<26)
using namespace std;

int N, S, T;
int dp[202][202]; // dp[i][j] : 현 i 위치, J left
int lst[210];

int dfs(int loc, int left) {
    if (loc > N) return 0;
    if (left == 0) return minf;
    if (dp[loc][left] != -1) return dp[loc][left];

    int &r = dp[loc][left];
    r = minf;
    for (int i = 1; i <= S ; i++) {
        r = max(r , dfs(loc+i, left -1) + lst[loc]);
    }
    return r;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    while(true) {
        cin >> N; if (N == 0) break;
        cin >> S >> T;
        for (int i = 1 ; i <= N ; i++) cin >> lst[i];
        memset(dp,-1,sizeof(dp));
        cout << dfs(0, T) <<'\n';
    }
    return 0;
}
