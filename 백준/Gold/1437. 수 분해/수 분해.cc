#include <iostream>
using namespace std;
const int mod = 10007;
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    //그리디 : 가능하면 2 혹은 3 을 많이 곱하는 것이 이득, 가능하면 3을 우선적으로
    int n; cin >> n;
    int r = 1;
    if (n <= 4) cout << n;
    else {
        while (n >= 5)
        {
            n-=3;
            r*=3;
            r%=mod;
        }
        if (n == 4) r = r*4%mod;
        else if (n == 3) r = r*3%mod;
        else r = r*n%mod;
        cout << r;
    }
    return 0;
}