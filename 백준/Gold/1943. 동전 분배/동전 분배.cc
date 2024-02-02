#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using pii = pair<int, int>;
bool dp[50001];

//배낭문제 동전의 업글버전
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; T=3;
    while (T--) {
        int n; cin >> n;
        int total_money = 0;
        vector<pii> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].first >> p[i].second;
            total_money += (p[i].first * p[i].second);
        }
        dp[0]=true;
        if (total_money % 2 == 1) {
            cout << 0 <<'\n';
            continue;
        }
        total_money/=2;
        for (auto dat : p) {
            //역순 이유 : 중복되는 경우 억제용
            for (int tg = total_money; tg >= dat.first; --tg) {
                if (dp[tg - dat.first]) {
                    for (int k = 0; k < dat.second; ++k) {
                        if (tg + k*dat.first <= total_money) {
                            dp[tg + k*dat.first] = true;
                        }
                    }
                }
            }
            if (dp[total_money]) break;
        }

        if (dp[total_money]) cout << 1;
        else cout << 0;
        cout << '\n';
        memset(dp,false,sizeof(dp));
    }
    return 0;
}