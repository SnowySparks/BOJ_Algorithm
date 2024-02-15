#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;
const int mv = 2001;
ll arr[mv];
ll dp[mv][mv];
int n;

int toclk(int x) { //현재 x번에 있고 시계방향 이동시 다음 값 , r 전용
    return (x-1+n)%n;
}
int tocclk(int x) {//현재 x번에 있고 반시계방향 이동시 다음 값 , l 전용
    return (x+1)%n;
}

//l, r 범위까지 지정된 상태에서 가능한 최대값을 고르는 함수
ll dfs(int l, int r, int cnt) { //현재 l, r 범위까지 골라져서 dp에 업로드 된 상태
    if (toclk(r) == l) return 0;
    ll &res = dp[l][r];
    if (cnt % 2 == 0) { //JOI Turn
        if (res != -1) return res;
        res = 0;
        res = max(dfs(tocclk(l),r,cnt+1)+arr[tocclk(l)], dfs(l,toclk(r),cnt+1)+arr[toclk(r)]);
    }
    else { // IOI Turn
        if (res != -1) return res;
        res = 0;
        if (arr[tocclk(l)] > arr[toclk(r)]) res = dfs(tocclk(l),r,cnt+1);
        else res = dfs(l,toclk(r),cnt+1);
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0 ; i < n ; ++i) cin >> arr[i];
    fill(&dp[0][0], &dp[2000][2000], -1);
    ll ans = 0;
    for (int i = 0; i < n ; ++i) ans = max(ans, dfs(i, i, 1) + arr[i]);
    cout << ans;
    return 0;
}