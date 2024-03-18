#include <iostream>
#include <vector>
#include <algorithm>
#define f(a,b,c) for(int a = b; a < c ; a++)
using namespace std;
int tr, tc,cnt = 0;
int dt[101][101];
void mv(int cr, int cc ) {
    if (cr == tr-1 && cc == tc -1) {
        if (dt[cr][cc] ) {
            cnt--;
            dt[cr][cc] = 0;
        }
        return;
    }
    f(i,cr,tr) f(k,cc,tc) {
        if( dt[i][k]) {
            dt[i][k] =0;
            cnt--;
            mv(i,k); return;
        }
    }
    return;
}
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> tr >> tc;
    int ans = 0;
    f(i,0,tr) f(k,0,tc) {
        cin >> dt[i][k];
        if (dt[i][k]) cnt++;
    }
    while (cnt > 0) {
        ans++;
        mv(0,0);
    }
    cout << ans;
    return 0;
}