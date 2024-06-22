#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)
using ll = long long;
int n, m;
ll arr[10000];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    f(i, 0, n) cin>>arr[i];
    if (n <= m) {
        cout << *max_element(arr, arr+n);
        return 0;
    }
    ll t = 0;
    sort(arr, arr+n, greater<>());
    priority_queue<ll> pq;

    f(i, 0, m) pq.push(-arr[i]);

    f(i, m, n) {
        t = -pq.top(); pq.pop();
        // cout << t << '\n';
        pq.push(-(t + arr[i]));
    }

    while (!pq.empty())
    {
         t = - pq.top(); pq.pop();
        // cout << t << '\n';

    }
    cout << t;
    
    return 0;
}