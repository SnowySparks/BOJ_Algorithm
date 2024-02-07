#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
using ll = long long;
#define f(a,b,c) for (int a=b;a<c;a++)
using pii = pair<ll,ll>;
pii dt[1000];
bool comp(const pii &a, const pii &b) {
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    f(i,0,n) cin >> dt[i].first >> dt[i].second;
    priority_queue<int, vector<int>, greater<> > pq;
    sort(dt,dt+n,comp);

    f(idx, 0, n) {
        while ((int)pq.size() >= dt[idx].first && pq.top() < dt[idx].second) pq.pop();
        if ((int)pq.size() == dt[idx].first) {
            if (pq.top() < dt[idx].second) {
                pq.pop();
                pq.push(dt[idx].second);
            }
        }
        else pq.push(dt[idx].second);
    }

    int ans = 0;
    while (!pq.empty()) {
        ans += pq.top();
        pq.pop();
    }
    cout<<ans;
    return 0;
}