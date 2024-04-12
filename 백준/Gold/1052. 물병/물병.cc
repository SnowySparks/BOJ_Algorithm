#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    if (n <= k) {
        cout << 0;
        return 0;
    }
    vector<int> loc;
    int tmp = 1;
    for (int i = 0; i < n; ++i) {
        if (tmp & n) loc.push_back(i);
        tmp<<=1;
    }

    if(loc.size() <= k) {
        cout << 0;
        return 0;
    }

    for (int i = loc.size()-1; i >= loc.size() - k; --i) n -= (1<<loc[i]);

    int ans = (1 << loc[loc.size() - k]) - n;
    cout << ans;

    return 0;
}