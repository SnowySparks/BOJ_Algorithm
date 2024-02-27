#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[501][501];
int arr[501][501];

int dr[] {1,-1,0,0};
int dc[] {0,0,1,-1};

int nr,nc,n;

int dfs(int r, int c) {
    //이미 값이 있을 경우 바로 리턴
    if (dp[r][c]) return dp[r][c];
    
    dp[r][c] = 1 ; // 방문처리

    for (int i = 0; i < 4 ; i++) {
        nr = r+dr[i];
        nc = c+dc[i];

        if (nr >=1 && nc >=1 && nr <=n && nc <=n) {
            if (arr[r][c] < arr[nr][nc]) {
                dp[r][c] = max(dp[r][c],dfs(nr,nc)+1);
            }
        }
    }
    return dp[r][c];
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    int ans = 0;

    for (int i = 1; i<=n;i++) {
        for (int j = 1 ; j <= n;j++) {
            cin >> arr[i][j];
        }
    }

    for (int i = 1; i<=n;i++) {
        for (int j = 1 ; j <= n;j++) {
            ans = max(ans,dfs(i,j));
        }
    }
    cout << ans;
}