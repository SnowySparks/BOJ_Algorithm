#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

struct pts {
    int x, y, px, py;
    pts(int x = 0, int y = 0) : x(x), y(y), px(0), py(0) {} // 생성자 1
    pts(int x, int y, int px, int py) : x(x), y(y), px(px), py(py) {} //생성자 2
    void cal_frompts(int ptx, int pty) { //해당 포인트 기준 (ptx pty) 해당 객체 벡터값
        px = x - ptx;
        py = y - pty;
    }

    bool operator<(const pts &oth) const {
        if (py * oth.px != px * oth.py) return py * oth.px < px * oth.py;
        if (y != oth.y) return y < oth.y;
        return x < oth.x;
    }
};

int ccw(const pts &a, const pts &b, const pts &c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y-a.y)*(c.x - a.x);
}

int ccw(const pts &a, const pts &b, const pts &c, const pts &d) { //(ab) x (cd), (a->b), (c->d)
    return (b.x  - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);
}

int dist(const pts &a, const pts &b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

int n;
pts arr[100001];
vector<pts>  convexhull;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout << fixed;
    cout.precision(8);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].x >> arr[i].y;
        if (i && arr[i] < arr[0]) {
            swap(arr[i], arr[0]);
        }
    }

    if (n == 2) {
        cout << sqrt(dist(arr[0], arr[1]));
        return 0;
    }
    if (n == 3) {
        cout << max(sqrt(dist(arr[0],arr[1])), max(sqrt(dist(arr[1],arr[2])), sqrt(dist(arr[0],arr[2]))));
    }
    for (int i = 1; i < n; ++i) arr[i].cal_frompts(arr[0].x, arr[0].y);
    sort(arr + 1, arr + n);
    convexhull.push_back(arr[0]);
    convexhull.push_back(arr[1]);

    for (int i = 2; i< n; ++i) {
        while (convexhull.size() >= 2)
        {
            int l = convexhull.size();
            if (ccw(convexhull[l-2], convexhull[l-1], arr[i]) > 0) break;
            convexhull.pop_back();
        }
        convexhull.push_back(arr[i]);
    }

    int ans = -1;
    int sz = (int)convexhull.size();
    int j = 1;
    for (int i = 0; i < sz; ++i) {
        int in = (i + 1) % sz;
        while (1)
        {
            int jn = (j + 1)%sz;
            ans = max(ans, dist(convexhull[i], convexhull[j]));
            
            if (ccw(convexhull[i],convexhull[in],convexhull[j],convexhull[jn]) > 0) j=jn;
            else break;
        }
        
    }
    cout << sqrt(ans);

    return 0;
}