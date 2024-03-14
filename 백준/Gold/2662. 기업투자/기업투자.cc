#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m; //투자금액, 투자기업수
int company[21][301]; //어느 투자 기업인가?, 투자비용 -> 이익값
int dp[21][301]; // -> i번째 기업 탐색일 때 현재 투자총액이 j일때 얻을 수 있는 최대 이익값
int path[21][301]; //i번째 기업 탐색일 때 현재 투자총액이 j일때 사용한 금액 양.

int main(void) {
    int tmp;
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <=n; ++i) {
        cin >> tmp;
        for (int k = 1; k <= m; ++k) {
            cin >> company[k][tmp];
        }
    }
    tmp = 0;
    //한 회사에는 단 한번의 투자만 가능함을 고려
    for (int i = 1; i <= m ; ++i) { //투자 회사
        for (int j = 1; j <= n; ++j) { //현재 j만큼의 총 투자액이라 두기
            for(int k = 0; k <=j; ++k) { //i화사에 k만큼 투자할 것임 투자를 아에 안하는 경우도 고려
                if (dp[i-1][j-k] + company[i][k] > dp[i][j]) {
                    dp[i][j] = dp[i-1][j-k] + company[i][k];
                    path[i][j] = k; //현재 i 회사차례에서 전체 총 j만큼투자했으면, i회사에 k만큼 투자햇단 의미
                }
            }
        }
    }
    vector<int> cost;
    tmp = n;
    //역추적
    for (int i =m; i >= 1; --i) {
        cost.push_back(path[i][tmp]);
        tmp-=path[i][tmp];
    }
    reverse(cost.begin(), cost.end());
    cout << dp[m][n] <<'\n';
    for (int &val : cost) cout << val <<' ';
    return 0;
}