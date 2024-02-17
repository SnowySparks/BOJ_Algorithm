#include <iostream>
#include <cstring>
using namespace std;
const int inf = 2e9;
int n, dp[11][1<<11];
int pts[12][2];
int dist(int a, int b) {
    return abs(pts[a][0] - pts[b][0]) + abs(pts[a][1]-pts[b][1]);
}

int tsp(int loc, int state) {
    int &r = dp[loc][state];
    if (r != -1) return r;
    if (state == (1<<(n+1))-1)  return dist(loc,n+1); 
    r= inf;
    for (int i = 1 ; i <=n ; i++ ) {
        if (state & (1<<i)) continue;
        r= min(r, tsp(i,state|(1<<i)) + dist(loc,i));
    }
    return r;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T ; cin >> T;
    for (int t = 1 ; t <= T ; t++) {
        cin >> n;
        cin >> pts[0][0] >> pts[0][1] >> pts[n+1][0] >> pts[n+1][1];
        for (int i = 1; i < (n+1) ; i++) cin >> pts[i][0] >> pts[i][1];
        memset(dp,-1,sizeof(dp));
        cout << '#' << t <<' '<< tsp(0,1) <<'\n';
    }
}