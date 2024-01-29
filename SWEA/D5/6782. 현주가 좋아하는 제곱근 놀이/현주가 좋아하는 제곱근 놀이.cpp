#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int inf = 2e9;
#define f(a,b,c) for (int a=b;a<c;a++)
using ll = unsigned long;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int t; cin >> t;
    ll ans = 0;
    f(i,1,t+1) {
        ll n; cin >> n;
        ans = 0;
        while (1) {
            if (n == 2) break;
            ll root = (ll) sqrt(n);

            if (root * root == n) {
                n = root;
            }
            else {
                ans += (root +1)*(root+1) - n;
                n = root + 1;
            }
            ans++;
        }
        cout << '#' << i << ' ' << ans << '\n';
    }
    return 0;
}