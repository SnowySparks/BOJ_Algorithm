#include <iostream>
#include <cmath>
using namespace std;
using ll = long long;
bool isprime(ll n) {
    if (n <= 1) return false;
    for (int i = 2; i <= int(sqrt(n));++i) {
        if (n%i==0) return false;
    }
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        ll tmp ; cin >> tmp;
        if (tmp <= 1) cout << 2 <<'\n';
        else {
            while (1) {
                if (isprime(tmp)) {
                    cout << tmp <<'\n';
                    break;
                }
                ++tmp;
            }
        }
    }
}
