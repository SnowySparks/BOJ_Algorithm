#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int dp[10001];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N; cin >> N;
    int t; vector<int> coins; int total_money; int temp;
    dp[0] = 1;
    while(N--) {
        cin >> t;
        for (int i = 0; i <t ; i++) {
            cin >> temp; coins.push_back(temp);
        }
        cin >> total_money;
        for (int i = 1; i <= t ; i++) { //동전 종류 개수
            for (int j = coins[i-1] ; j <= total_money ; j++) { //j : 돈위치
                 dp[j]+=dp[j-coins[i-1]];
            }
        }
        cout << dp[total_money] << endl;
    //초기화
    fill (dp+1,dp+total_money+1,0);
    coins.clear();
    }
    return 0;
}