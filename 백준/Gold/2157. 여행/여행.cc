#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
#define f(a,b,c) for(int a=b;a<=c;a++)
int n, m, k;
int dp[301][301]; // i 여행지가 k번째 도시일 때 최대 스코어
const int inf = 1e9+7;
vector<pair<int, int> > gh[301]; // to, score

int dfs(int loc, int travel) {
    if (travel == m && loc != n ) return -inf;
    if (loc == n ) return 0;
    int &ret = dp[loc][travel];
    if (ret!= -1) return ret;
    ret = -inf;
    for (pair<int, int> dt : gh[loc]) {
        if (loc < dt.first) ret = max(ret, dfs(dt.first, travel+1) + dt.second);
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> k;
    f(i,1,k) {
        int from ,to, score;
        cin >> from >> to >> score;
        if (from < to ) gh[from].push_back({to, score});
    }
    memset(dp, -1, sizeof(dp));
    cout << dfs(1, 1);

    return 0;
}