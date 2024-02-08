#include <iostream>
#include <algorithm>
using namespace std;
#define f(a,b,c) for (int a=b;a<c;a++)
int n, m, cost;

struct bridge {
    int a, b, cost;

    bool operator>(const struct bridge &a) const {
        return cost > a.cost;
    }
    bool operator<(const struct bridge &a) const {
        return cost < a.cost;
    }
};

bridge bd[30001];
int p[10001];

int parent(int a) {
    if (p[a] == a) return a;
    return p[a] = parent(p[a]);
}

bool _union(int a, int b) {
    a = parent(a);
    b = parent(b);
    if (a == b) return false;
    p[max(a,b)] = min(a,b);
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int cnt = 0;
    long long ans = 0;
    cin >> n >> m >> cost;
    f(i,1,m+1) cin >> bd[i].a >> bd[i].b >> bd[i].cost;
    f(i,1,n+1) p[i]=i;
    sort(bd+1,bd+m+1);

    f(i,1,m+1) {
        if (_union(bd[i].a,bd[i].b)) {
            ans += (bd[i].cost + cnt * cost);
            ++cnt;
        }
    }
    cout << ans;
    return 0;
}