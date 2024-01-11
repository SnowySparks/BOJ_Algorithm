#include <iostream>
#include <vector>
#include <algorithm>
#define inf 18000001
using namespace std;
int N;
int arr[16][16];
int dp[16][1 << 16];

int dfs(int cur, int state) {
    //현재 방문 도시, 현재 방문 상태
    if (state == (1<<N)-1) {
        if (arr[cur][0] == 0) return inf;
        return arr[cur][0];
    }
    int &ret = dp[cur][state];
    if (ret != -1) return ret;
    ret = inf;

    for (int i = 0; i < N; i++) {//다음 도시 방문
        if ((state & (1 << i)) ) continue; //이미 찍먹상태
        if ( arr[cur][i] == 0) continue; //방문불가
        ret = min(ret, dfs(i, state | (1 << i)) + arr[cur][i]);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); 
    cin >> N;
    for (int i = 0; i < N; i++) {
        fill (dp[i], dp[i] + (1<<N), -1);
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
    cout << dfs(0,1); return 0;
}