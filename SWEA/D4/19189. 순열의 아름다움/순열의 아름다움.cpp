#include <iostream>
using namespace std;
const int inf = 250003;
using ll = long long;
#define f(a, b, c) for (int a=b;a<c;++a)
ll fact[inf];
int n; ll prime;
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    fact[1] = 1;
    f(tc, 1, T+1) {
        cin >> n >> prime;
        f(i, 2, n+2) {
            fact[i] = (fact[i-1] * i)%prime; }
        ll ans = 0;
        f(i, 0, n) {
            ans += fact[i+1]%prime * fact[n-i]%prime * (n-i) %prime;
            ans%=prime;
        }
        cout << '#' << tc <<' ' <<ans << '\n';
    }
    return 0;
}