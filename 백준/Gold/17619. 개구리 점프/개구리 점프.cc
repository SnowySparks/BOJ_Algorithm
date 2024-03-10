#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INF 0x7f7f7f7f
#define MAX_N 100001
int parent[MAX_N];

int p(int a) {
    if (parent[a] == a) return a;
    return parent[a] = p(parent[a]);
}

bool merge(int a, int b) {
    a = p(a); b = p(b);
    if (a == b) return false;
    parent[max(a, b)] = min(a, b);
    return true;
}

struct info{
    int fr, to, idx; // fr = x1, to = x2, idx = number
};

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<info> line(n);
    int x1, x2, y;
    for (int i = 0; i < n; ++i) {
        parent[i+1] = i+1;
        cin >> x1 >> x2 >> y;
        line[i] = {x1, x2, i+1};
    }

    sort(line.begin(), line.end(), [](const info &a, const info &b) {
        return a.fr < b.fr;
    });

    int en = -INF;
    int rootidx = -1;
    for (auto &[s, e, idx] : line) {
        if (en < s) {
            en = e;
            rootidx = idx;
        }
        else {
            en = max(e, en);
            merge(rootidx, idx);
        }
    }

    while (q--)
    {
        int a1, a2; cin >> a1 >> a2;
        if (p(a1) == p(a2)) cout <<"1\n";
        else cout <<"0\n";
    }
    
    return 0;
}

// y좌표는 의미가없음. 그것 빼곤 그냥 스위핑