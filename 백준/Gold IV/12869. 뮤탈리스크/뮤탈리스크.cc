#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
using ll = long long;
const int mv = 61;
const int inf = 1e8;
int arr[3];
int dp[mv][mv][mv];
int n;

int re[6][3] = { 
    {9, 3, 1},
    {9, 1, 3},
    {3, 9, 1},
    {3, 1, 9},
    {1, 9, 3},
    {1, 3, 9}
};

//dp index 역할 : 각각 SCV라는 어떠한 오브젝트의 남은 체력 상태
int dfs(int x1, int x2, int x3) {
    if (x1 == 0 && x2 == 0 && x3 == 0) return 0; 
    int &res = dp[x1][x2][x3];
    if (res != -1) return res;
    res = inf;
    for (int i = 0; i < 6; ++i) {
        res = min(res, 1+dfs(max(0, x1-re[i][0]),max(0, x2-re[i][1]),max(0, x3-re[i][2])));
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0 ; i < n ; ++i) cin >> arr[i];
    memset(dp, -1, sizeof(dp));
    cout << dfs(arr[0],arr[1],arr[2]);
    return 0;
}