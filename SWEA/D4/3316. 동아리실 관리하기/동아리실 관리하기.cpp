#include <iostream>
#include <cstring>
#define f(a, b, c) for(int a=b;a<c;++a)
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
ll dp[10001][1<<4];
// idx, (state : DBCA(2) ) , A = (1 << 0), B = (1 << 1), C = (1 << 2), D = (1 << 3)

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    int n, prefix;
    string state;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> state;
        int len = state.size();
        memset(dp, 0, sizeof(dp));
        
        // 맨 처음 경우, A가 키를 가지고 있으니 A 참석인 상태와 , 현재 관리자가 참석한 경우의 bit가 만족하는 것만 경우 1로 계산
        f(i, 0, 16) {
            if ( (i & (1<<0)) && ( i & (1 << (state[0] - 'A')) ) ) {
                dp[0][i] = 1;
            }
        }

        // 2번째 이후의 dp 계산
        f(i, 1, len) {
            f(k, 0, 16) { // k : 현재 파티원 참가 bit 경우
                if (k & ( 1 << (state[i] - 'A'))) { // 현재 idx에서, 해당 관리자가 "참가" 하는 경우만 탐색
                    f(p, 0, 16) { //어제 파티원 참가 경우의 수 탐색
                        if ((p & k)) { //  어제 파티원 참가와 오늘 파티원 참가의 교집합이 있는 경우에 경우의 수 추가 갱신함
                            dp[i][k] +=dp[i-1][p];
                        }
                    }
                    dp[i][k]%= mod;
                }
            }
        }   


        // 마지막 idx의  모든 경우의 수를  다 더하면 답
        ll ans = 0;
        f(i, 0, 16) {
            ans += dp[len-1][i];
        }
        cout << '#' <<tc << ' ' << ans%mod << '\n';
    }
}