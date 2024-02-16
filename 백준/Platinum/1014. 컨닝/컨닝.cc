#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

int dp[11][1<<10], n, m;
string inp[11];

int dfs(int cur, int now_state) { //cur : 현재까지 처리된 행 위치, now_state : 현재 행에서 선택된 상태값
    if (cur == n) return 0; //종료조건 
    int &res = dp[cur][now_state]; // dp
    if (res != -1) return res; //dp처리
    res = 0;
    int cnt = 0;
    bool flag = false;
    for (int i = 0; i < (1<<m); ++i) { //다음 행에 대한 선택 탐색
        flag = false;
        cnt = 0;
        for (int k = 0; k < m; ++k) {
            int temp = 1<<k;
            if (i & temp) {
                ++cnt;
                if (inp[cur+1][k] == 'x') { // x가 있ㅇ면 종료
                    flag = true;
                    break;
                }
                if (k > 0 && ((now_state  & (1<<(k-1)))|| (i & (1<<(k-1) )))) { // k열 기준 왼쪽에 누가 있는가?
                    flag = true;
                    break;
                }
                if (k < m && ((now_state  & (1<<(k+1))) || (i & (1<<(k+1) )))) { //k열 기준 오른쪽에 누가 있는가?
                    flag = true;
                    break;
                }
            }
        }
        if (!flag) { //조건에 부합하는 경우 dfs 재귀 접근
            res = max(res, dfs(cur+1, i) + cnt );
        }
    }
    return res;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >>T;
    while(T--) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {cin >> inp[i]; reverse(inp[i].begin(), inp[i].end());}
    memset(dp,-1,sizeof(dp));
    cout << dfs(0, 0) <<'\n'; }
    return 0;
}