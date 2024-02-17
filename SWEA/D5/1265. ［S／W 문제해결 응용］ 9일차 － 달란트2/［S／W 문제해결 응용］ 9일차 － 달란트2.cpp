#include <iostream>
#include <cstring>
using namespace std;
using ll = unsigned long;

//산술 - 기하 평균에서 기하가 최대값이 되는 경우를 생각해보면...
//딱 안떨어지는 경우 (즉 나머지 생기면), 각각 그룹에 +1 한만큼 값을 곱하면 끝...
int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, p;
    int T; cin >>T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> n >> p;
        ll q = n/p;
        ll res = n%p;
        ll ans = 1;
        while (res--) {
            ans *= (q+1);
            p--;
        }
        while (p--) {
            ans *= q;
        }
        cout << '#' <<tc << ' ' << ans <<'\n';
    }
    return 0;
}