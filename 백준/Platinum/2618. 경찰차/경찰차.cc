#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int N, W; 
int dp[1001][1001];
pair<int, int> wk[1001];

int dst(const pair<int, int> &a, const pair<int, int> &b) {
    return abs(a.first -b.first) + abs(a.second -b.second); }

int dfs(int c1, int c2) { // 1번 자동차가 마지막으로 끝내는 거, 2번 자동차 ;;
    if (c1 == W || c2 == W) return 0;
    if (dp[c1][c2] != -1) return dp[c1][c2];
    int next = max(c1, c2)+1;
    int d1 = (c1 == 0) ? dst({1,1},wk[next]) : dst(wk[c1],wk[next]);
    int d2 = (c2 == 0) ? dst({N,N},wk[next]) : dst(wk[c2],wk[next]);
    return dp[c1][c2] = min(dfs(next,c2) + d1 , dfs(c1,next)+d2);
}

void tr(int c1, int c2) {
    if (c1 == W || c2 == W) return;
    int next = max(c1, c2)+1;
    int d1 = (c1 == 0) ? dst({1,1},wk[next]) : dst(wk[c1],wk[next]);
    int d2 = (c2 == 0) ? dst({N,N},wk[next]) : dst(wk[c2],wk[next]);

    if (dp[next][c2] + d1 < dp[c1][next] + d2) {
        cout << 1 <<'\n'; tr(next,c2);
    }
    else {
        cout << 2<<'\n'; tr(c1,next);
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N >> W;
    for (int i = 1 ; i<= W ; i++) cin >> wk[i].first >> wk[i].second;
    memset(dp,-1,sizeof(dp));
    cout << dfs(0,0) <<'\n';
    tr(0,0);
}