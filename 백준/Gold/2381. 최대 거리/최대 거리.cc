#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;
const int inf = 1e9;
vector<pii> arr;


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<pii> arr(n);

    int xpy, xmy; // (x+y)의 최대 - 최소 값, (x-y)의 최대 - 최소 값
    for (int i =0; i<n;++i) {
        cin >> arr[i].first >> arr[i].second;
    }

    int max_v = -inf, min_v = inf;

    for (auto &[a, b] : arr) {
        max_v = max(max_v, a+b);
        min_v = min(min_v, a+b);
    }
    xpy = max_v - min_v;

    max_v = -inf;
    min_v = inf;

    for (auto &[a, b] : arr) {
        max_v = max(max_v, a-b);
        min_v = min(min_v, a-b);
    }

    xmy = max_v - min_v;

    cout << max(xpy, xmy);

    return 0;
}
