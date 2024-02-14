#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
using pli = pair<long long, int>;
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    long long arr[100];
    int n, k; cin >> k >> n;
    priority_queue<pli, vector<pli>, greater<pli> > pq;
    for (int i = 0 ; i < k ; ++i) {cin >> arr[i];}
    for (int i = 0 ; i < k ; ++i) pq.push({arr[i], i});
    int cnt = 0;
    long long ans = 0;
    while(true) {
        pli loc = pq.top(); pq.pop();
        ++cnt;
        if (cnt == n) {
            ans = loc.first;
            break;
        }
        for (int idx = 0; idx <= loc.second; ++idx) {
            pq.push({loc.first * arr[idx],idx});
        }
    }
    cout << ans;
    return 0;
}