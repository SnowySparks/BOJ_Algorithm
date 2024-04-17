#include <iostream>
#include <deque>
using namespace std;
using ll = long long;
const int maxn = 1e5+1;

int n, d;
ll arr[maxn];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> d;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    deque<pair<int, ll> > dq;
    dq.push_back({1, arr[1]});
    ll ans = arr[1];

    for (int i =2; i <= n; ++i) {
        while (!dq.empty() && dq.front().first < i - d ) dq.pop_front();
        
        ll before_max = dq.front().second;
        ll now_max = max(before_max + arr[i], arr[i]);

        ans = max(ans, now_max);
        
        while (!dq.empty() && dq.back().second <= now_max) dq.pop_back();
        dq.push_back({i, now_max});
    }

    cout << ans;

    return 0;
}
