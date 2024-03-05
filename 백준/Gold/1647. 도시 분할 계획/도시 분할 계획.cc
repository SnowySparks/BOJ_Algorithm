#include <iostream>
#include <algorithm>
#include <cstdarg>
#define f(a, b, c) for (int a =b; a<c;++a)
using namespace std;

int p[100001];
int find(int a) {
    if (p[a] == a) return a;
    return p[a] = find(p[a]);
}
struct io {
    int a, b, cost;
    bool operator<(const io &other) const {
        return cost < other.cost;
    }
};
bool merge(int a, int b){
    a = find(a);
    b = find(b);
    if (a == b) return false;
    p[max(a,b)]=min(a,b);
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    f(i, 1, n+1) p[i] = i;
    vector<io> d(m);
    vector<io> lst;
    f(i, 0, m) {
        cin >> d[i].a >> d[i].b >> d[i].cost; }
    sort(d.begin(), d.end());
    int ans = 0;
    for (const io &dt : d) {
        if (merge(dt.a,dt.b)) {ans += dt.cost; lst.push_back(dt);}
    }
    cout << ans - lst.back().cost;
    return 0;
}