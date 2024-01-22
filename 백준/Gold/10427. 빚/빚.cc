#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int mv = 4001;
const long long inf = 1e11;
int arr[mv], sum[mv];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t, n; cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n ; ++i) cin >> arr[i];
        sort(arr+1,arr+n+1);
        for (int i = 1; i <= n ; ++i) sum[i] = sum[i-1]+arr[i];
        long long ans = 0, min_val;
        for (int sz = 1; sz <= n ; ++sz) { // s(sz)
            min_val = inf;
            for (int loc = sz; loc <= n ; ++loc) {
                min_val = min(min_val, (long long)arr[loc]*sz - (sum[loc] - sum[loc-sz]));
            }
            ans += min_val;
        }
        cout << ans << '\n';
        memset(arr,0,sizeof(arr));
        memset(sum,0,sizeof(sum));
    }
}