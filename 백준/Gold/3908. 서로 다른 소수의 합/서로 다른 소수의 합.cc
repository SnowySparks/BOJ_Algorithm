#include <iostream>
#include <vector>
using namespace std;
vector<int> primes;
const int mn =1121;
int arr[mn];
int dp[mn][15];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // 1. find primes
    for (int i = 2; i < mn ; ++i) {
        if (!arr[i]) primes.push_back(i);
        for (int prime : primes) {
            if (prime * i >= mn) break;
            arr[i*prime] = prime;
            if (i%prime==0) break;
        }
    }
    // 2 dp 처리
    dp[0][0] = 1; // 공집합 케이스 
    for (int prime : primes) {
        for (int i = mn-1; i >= 1 ; --i) {
            //일부러 역순으로 + 소수루프 먼저
            // 중복을 피하기 위함 역순으로 {2,3} , {3,2}
            // 소수먼저 루프를 두어 {2}, {2,2} 같은 경우 발생방지
            for (int k = 1 ; k <= 14; ++k) {
                if (i-prime >= 0) dp[i][k] += dp[i-prime][k-1];
            }
        }
    }

    int t,a,b; cin >> t;
    while(t--) {
        cin >> a >> b;
        cout << dp[a][b] <<'\n';
    }
    return 0;
}