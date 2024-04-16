#include <iostream>
#include <cstring>
using namespace std;

int n;
string target, s; // 목적지, s,
int dp[10][10000];

int dfs(int loc, int mv) { //바라보는 위치, (탐색해야하는위치), mv = 왼쪽으로 돌렸을 경우의 누적 횟수%10
    if (loc == n) return 0;
    int &res = dp[mv][loc];
    if (res != -1) return res;

    int left_turn = (target[loc] - s[loc] - mv + 20)%10;
    int right_turn = (10 - left_turn);


    res = min(dfs(loc+1, (mv+left_turn)%10) + left_turn, dfs(loc+1, mv) +right_turn);
    return res;

} 

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    cin >> s >> target;
    memset(dp, -1, sizeof(dp));
    cout << dfs(0, 0);
    return 0;
}