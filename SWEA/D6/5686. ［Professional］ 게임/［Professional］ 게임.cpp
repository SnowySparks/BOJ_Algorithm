#include <iostream>
#include <cstring>
using namespace std;
const int inf = 1e5+2;
int sarr[inf];
int tmp[inf];
int tmp2[inf][2];
int n, m;
int dp[inf];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    int T; cin >> T;
    for (int tc = 1; tc <= T ; ++tc) {
        memset(dp,0,sizeof(dp));
        memset(sarr,0,sizeof(sarr));
        memset(sarr,0,sizeof(tmp));
        memset(tmp2,0,sizeof(tmp2));
        cin >> n >> m;
        for (int i = 0 ; i < n ; ++i) {
            for (int j = 0; j < m ; ++ j) {
                cin >> tmp[j];
            }
            tmp2[m-1][1] = tmp[m-1];
            
            for (int j = m-1; j >=0; --j) {
                tmp2[j][0] = max(tmp2[j+1][0],tmp2[j+1][1]);
                tmp2[j][1] = max(tmp2[j+2][0],tmp2[j+2][1]) + tmp[j];
                sarr[i] = max(sarr[i],max(tmp2[j][0],tmp2[j][1]));
            }
        }

        dp[n-1] = sarr[n-1];
        int ans = dp[n-1];
        for (int i = n-2; i >= 0 ; --i) {
            dp[i] = max(dp[i+1], dp[i+2] + sarr[i]);
            ans = max(ans,dp[i]);
        }
        cout << '#' << tc <<' ' << ans <<'\n';
    }
}