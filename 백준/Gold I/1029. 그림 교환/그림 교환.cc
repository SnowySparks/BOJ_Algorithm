#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

string dt[15];
int dp[10][15][1<<15]; //가격, 
int N;
int answer = 0;
int dfs(int nowartist, int state, int curprice) {
    int &ret = dp[curprice][nowartist][state];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 0 ; i< N ; i++) {
        if (!(state & (1 << i)) && i!=nowartist && (dt[nowartist][i] - '0' >= curprice) ) {
            ret = max(ret, dfs(i,state|(1<<i), dt[nowartist][i] - '0')+1);
        }
    }
    return ret;
}  

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> dt[i];
    memset(dp,-1,sizeof(dp));
    cout << dfs(0,1,0)+1;
}