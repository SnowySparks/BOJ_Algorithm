#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<int> minus;
    vector<int> plus;
    vector<int> one;
    long long ans = 0;
    int one_cnt = 0;
    int n; cin >> n;
    int tmp;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        if (tmp > 1) plus.push_back(tmp);
        else if (tmp == 1) one_cnt++;
        else minus.push_back(tmp);
    }
    sort(plus.begin(), plus.end(), greater<>() );
    sort(minus.begin(), minus.end());

    int idx = 0;
    for (; idx < plus.size(); idx += 2) {
        if (idx == (int)plus.size() -1 ) {
            ans += plus[idx];
            break;
        }
        ans += 1LL * plus[idx] * plus[idx + 1];
    }

    idx = 0;

    for (; idx < minus.size(); idx += 2) {
        if (idx == (int)minus.size() -1 ) {
            ans += minus[idx];
            break;
        }
        ans += 1LL * minus[idx] * minus[idx + 1];
    }
    cout << ans + one_cnt;
    return 0;
}