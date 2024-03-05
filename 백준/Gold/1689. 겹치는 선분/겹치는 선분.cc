#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using pii = pair<int,int>;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >>n;
    vector<pii> lst(2*n);
    for (int i = 0; i <n; ++i) {
        cin >> lst[2*i].first >> lst[2*i+1].first;
        lst[2*i].second = 1;
        lst[2*i+1].second = -1;
    }
    sort(lst.begin(), lst.end());
    int cnt = 0;
    int ans = 0;
    for (pii &a : lst) {
        ans = max(cnt, ans);
        cnt += a.second;
    }
    cout << ans;
    return 0;
}