#include <iostream>
#include <algorithm>
#define f(a,b,c) for(int a=b; a<c; a++)
using namespace std;
using ll =  long long;
const int _m = 3188647;

ll dp[_m];
int a, b, k;
ll cal(ll  p){
    ll r = 0, t, e;
    while(p) {
        t = 1; e = p%10;
        f(i,0,k) t*=e;
        r+=t; p/=10;
    }
    return r;
}

ll dfs(ll p) {
    if (dp[p] == -1) {
        dp[p] = 0;
        ll next = cal(p);
        dp[p] = min(p, dfs(next));
    }
    else if (dp[p] != 0) {
        return dp[p];
    }
    else {
        ll mini = p;
        ll nn = cal(p);

        while( nn!= p) {
            mini= min(mini, nn);
            nn = cal(nn);
        }
        dp[p] = mini;
        nn = cal(p);

        while(nn!=p) {
            dp[nn] = mini;
            nn = cal(nn);
        }
    }
    return dp[p];
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> a >> b >> k;
    fill(dp, dp+_m,-1); dp[0] = 0; dp[1] = 1;
    ll ans = 0;
    f(i,a,b+1) ans+=dfs(i);
    cout << ans; return 0;
}