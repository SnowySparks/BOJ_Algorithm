#include <iostream>
#include <algorithm>
using namespace std;
int inp[5000];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0 ; i < n ; ++i) cin >> inp[i];
    int minval, maxval, idx;
    int l = 0, r = *max_element(inp,inp+n);
    int ans = r;
    while (l <= r) {
        int mid = (l+r) >> 1;
        int cnt = 1;
        minval = inp[0]; maxval=inp[0];

        for (int i = 1 ; i < n; ++i) {
            minval = min(minval, inp[i]);
            maxval = max(maxval, inp[i]);

            if (maxval - minval > mid) {
                ++cnt;
                minval = inp[i];
                maxval = inp[i];
            }
        }

        if (cnt <= m) {
            ans = min(ans, mid);
            r = mid-1;
        }
        else l = mid+1;
    }
    cout << ans;
    return 0;
    
}