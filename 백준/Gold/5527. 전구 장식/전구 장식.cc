#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)
const int inf = 1e5+1;
int n;
int arr[inf];
vector<int> dp;


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    f(i, 1, n+1) cin >> arr[i];
    int cnt = 1;
    f(i, 2, n+1) {
        if ( arr[i]^arr[i-1] ) {
            ++cnt;
            if (i == n) dp.push_back(cnt);
        }
        else {
            dp.push_back(cnt);
            cnt = 1;
            if (i == n) dp.push_back(1);
        } 
    }
    int sz = (int)dp.size();
    // f(i, 0, sz) cout << dp[i] << ' ';
    // cout << '\n';
    if (sz == 1) cout << dp[0];
    else if (sz == 2) cout << dp[0]+dp[1];
    else {
        int ans = -1;
        f(i, 1, sz-1) {
            ans = max(ans, dp[i-1]+dp[i]+dp[i+1]);
        }
        cout << ans;
    }
    return 0;
}

// 원리
// 먼저 연속된 교대 패턴 그룹핑한 갯수들을 dp에 저장
// 그다음 3개 연속 수를 더한 값중 최대값이 답 -> 이유 "중간 부분만 바꾸면" 양 옆 교대패턴과 이어지기 때문