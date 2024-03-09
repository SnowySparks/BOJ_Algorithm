#include <iostream>
#include <vector>
#include <algorithm>
#define NMAX 100001
using namespace std;

struct edge {
    int n1, n2, dist;
};

struct cord
{
    int node, x, y, z;
};

int p[NMAX];
int parent(int a) {
    if (a == p[a]) return a;
    return p[a] = parent(p[a]);
}

bool merge(int a, int b) {
    a = parent(a);
    b = parent(b);
    if (a == b) return false;
    p[max(a,b)] = min(a,b);
    return true;
}
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) p[i]=i;
    vector<cord> nd(n);
    for (int i = 0; i < n; ++i) {
        nd[i].node = i+1;
        cin >> nd[i].x >> nd[i].y >> nd[i].z;
    }
    vector<edge> e;

    //x좌표 오름차순
    sort(nd.begin(), nd.end(), [](const cord &a1, const cord &a2) {
        return a1.x < a2.x;
    });
    for (int i = 1; i <n; ++i) e.push_back({nd[i-1].node,nd[i].node,nd[i].x-nd[i-1].x});

    //y좌표 오름차순
    sort(nd.begin(), nd.end(), [](const cord &a1, const cord &a2) {
        return a1.y < a2.y;
    });
    for (int i = 1; i <n; ++i) e.push_back({nd[i-1].node,nd[i].node,nd[i].y-nd[i-1].y});

    //z좌표 오름차순
    sort(nd.begin(), nd.end(), [](const cord &a1, const cord &a2) {
        return a1.z < a2.z;
    });
    for (int i = 1; i <n; ++i) e.push_back({nd[i-1].node,nd[i].node,nd[i].z-nd[i-1].z});

    //Edge 길이 오름차순
    sort(e.begin(), e.end(), [](const edge &a, const edge &b) {
        return a.dist < b.dist;
    });

    //크루스칼 알고리즘 - MST 구하기
    long long ans = 0;
    int cnt = 0;
    for (edge dt : e) {
        if (cnt == n-1) break;
        if (merge(dt.n1, dt.n2)) {
            ++cnt;
            ans += dt.dist;
        }
    }
    
    cout << ans;
    return 0;
}