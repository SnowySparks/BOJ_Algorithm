#include <iostream>
#include <vector>
#include <algorithm>
#define M 1
#define W 0
using namespace std;

int school[1001];
struct io {
    int n1, n2, cost;
};

int p[1001];

int parent(int x) {
    if (p[x] == x) return x;
    return p[x] = parent(p[x]);
}

bool merge(int a, int b) {
    a = parent(a);
    b = parent(b);
    if (a == b) return false;
    p[max(a, b)] = min(a, b);
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    int a, b, c;
    char ch;
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
        cin >>ch;
        if (ch == 'M') school[i] = M;
        else school[i] = W;
    }

    vector<io> v;
    while (m--)
    {
        cin >> a >> b >> c;
        if ((school[a]^school[b]) == 1) {
            v.push_back({a, b, c});
        }
    }

    sort(v.begin(), v.end(), [](const io &a, const io &b) {
        return a.cost < b.cost;
    });

    int conneced_edge = 0;
    int ans =0;
    for (auto &[n1, n2, cost] : v) {
        if (merge(n1, n2)) {
            conneced_edge++;
            ans += cost;
        }
        if (conneced_edge == n-1) break;
    }

    if (conneced_edge == n-1) cout << ans;
    else cout << -1;
    return 0;

}