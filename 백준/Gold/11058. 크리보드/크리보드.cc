#include <iostream>
using namespace std;
unsigned long long dp[101];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    dp[4] = 4;

    // 3번 버튼 사용 남은 경우 -> 선복붙, 4번 남은 경우 선복붙붙, 5번 남는 경우 선복붙붙붙, 6번 남는 경우는 다음 선복붙붙붙붙 
    // 그러나 6번은 선복붙선복붙 이렇게도 동작이 되고 동일함

    for (int i = 5; i <= n; ++i) {
        dp[i] = dp[i-1] + 1; // 단일 A 입력
        dp[i] = max(dp[i], max(dp[i-3] * 2 ,max( dp[i-4] * 3, dp[i-5] * 4)));
        
    }

    cout << dp[n];
    return 0;
}
