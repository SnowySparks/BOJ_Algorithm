#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int n; ll m;
ll prime[10];
ll ans = 0;

int main(void) {
    ios_base::sync_with_stdio(0); cout.tie(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0 ; i < n ; i++) cin >> prime[i];

    for (int i = 1; i < (1<<n) ; i++) {
        int tmp = i, cnt = 0;
        unsigned long p = 1;
        for (int k = 0; tmp>0; k++) {
            if (tmp&1) {p*=prime[k]; cnt++;}
            tmp>>=1;
        }
        if (cnt%2) ans+= m/p;
        else ans-= m/p;
    }
    cout << ans; return 0;

}