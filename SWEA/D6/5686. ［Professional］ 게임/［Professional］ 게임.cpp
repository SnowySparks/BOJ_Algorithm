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
        //초기화
        memset(dp,0,sizeof(dp));
        memset(sarr,0,sizeof(sarr));
        memset(sarr,0,sizeof(tmp));
        memset(tmp2,0,sizeof(tmp2));
        //input
        cin >> n >> m;
        for (int i = 0 ; i < n ; ++i) {
            for (int j = 0; j < m ; ++ j) {
                cin >> tmp[j];
            }

            //한 줄(가로줄)에 대해서 선택 가능한 경우의 수중 가장 최대값을 도출
            //DP이용 , tmp[col][opt] opt : 0 -> 해당 값을 선택하지 않은 경우, opt : 1-> 해당 값을 선택한 경우
            tmp2[m-1][1] = tmp[m-1];
            
            for (int j = m-1; j >=0; --j) {
                tmp2[j][0] = max(tmp2[j+1][0],tmp2[j+1][1]);//선택 안하는 경우 -> 바로 직전걸 가져옴
                tmp2[j][1] = max(tmp2[j+2][0],tmp2[j+2][1]) + tmp[j];//선택한 경우 -> 두칸 건너뛴 것들중 최대값 + 자기자신
                sarr[i] = max(sarr[i],max(tmp2[j][0],tmp2[j][1]));//해당 행에 대한 최대값 갱신
            }
        }
        //행 방향에 했던 방식 드개로 열 방식으로도 동일하게 적용
        dp[n-1] = sarr[n-1];
        int ans = dp[n-1];
        for (int i = n-2; i >= 0 ; --i) {
            dp[i] = max(dp[i+1], dp[i+2] + sarr[i]);
            ans = max(ans,dp[i]);
        }
        cout << '#' << tc <<' ' << ans <<'\n';
    }
}