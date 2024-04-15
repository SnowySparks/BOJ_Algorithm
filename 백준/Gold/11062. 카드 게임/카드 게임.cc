#include <iostream>
#include <cstring>
using namespace std;
int n;
int arr[1002];
int dp[1002][1002]; //현재, l, r 까지 선택되었을 때, 근우가 가질 수 있는 최대 값

int dfs(int l, int r, int t) {
    if (abs(r-l)<=1) return 0;
    int &res = dp[l][r];
    if (res != -1) return res;
    res = 0;
    if (t%2==0) { //근우 턴 : 근우는 가능한 큰 값을 가져가므로 max
        res = max(dfs(l+1, r, t+1) + arr[l+1], dfs(l, r-1, t+1) + arr[r-1]); 
    }
    else { // 명우 턴 : 근우 입장에선 점수가 작은걸 가져갈 수 밖에 없음
        res = min(dfs(l+1, r, t+1), dfs(l, r-1, t+1));
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    while (T--)
    {
        cin >> n;
        memset(dp, -1, sizeof(dp));
        for (int i = 1; i <= n; ++i) cin >> arr[i];
        cout << dfs(0, n+1, 0) << '\n';
    }
    return 0;
}