#include <iostream>
using namespace std;

long long dp[2501];
const long long inf = 1e9+7;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;


    for (int i = 3; i <= 2500; ++i) {
        for (int k = 0; k <= i-1; ++k) {
            dp[i] += (dp[k] % inf) * (dp[i-1 -k] % inf);
            dp[i] %= inf;
        }
    }

    int t; cin >> t;
    while (t--)
    {
        int a; cin >> a;
        if (a&1) cout << 0 << '\n';
        else cout << dp[a>>1] << '\n';
    }
    

    return 0;
}

// 카탈린 수 
// dp[i] = for(int k = 0; k <= i-1; ++k) dp[i] += dp[k]dp[i-1-k]; , dp[0] = 0
// n개의 괄호 쌍으로 만들 수 있는 조합
// X, Y 이루어진 길이 2n이 있을 때, 맨 앞에서 x, y 새울 때 x가 y보다 크가너 같은 문자열 구하기 (뒤크 단어) dp[n] 경우의 수