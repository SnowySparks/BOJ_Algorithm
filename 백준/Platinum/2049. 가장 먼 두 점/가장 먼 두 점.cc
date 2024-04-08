#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct pts {
    int x, y, px, py;
    pts() : x(0), y(0), px(0), py(0) {}
    pts(int x, int y) : x(x), y(y), px(0), py(0) {}
    pts(int x, int y, int px, int py) : x(x), y(y), px(px), py(py) {}

    void cal_from_center(int cx, int cy) {
        px = x - cx; py = y - cy;
    }

    bool operator<(const pts &other) const {
        if (py*other.px != px*other.py) return py*other.px < px*other.py;
        if (y!=other.y) return y < other.y;
        return x < other.x;
    }
};

int ccw(const pts &a, const pts &b, const pts &c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y-a.y)*(c.x-a.x);
}

int ccw(const pts &a, const pts &b, const pts &c, const pts &d) { //(a->b) and (c -> d) ccw
    int abx = b.x - a.x, aby = b.y - a.y, cdx = d.x - c.x, cdy = d.y - c.y;

    return abx * cdy - aby * cdx;
}

int dist(const pts &a, const pts &b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

int n;
pts p[100010];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
        if (i > 0 && p[i] < p[0]) swap(p[0], p[i]);
    }
    // ConvexHull
    for (int i =1 ;i <n; ++i) p[i].cal_from_center(p[0].x, p[0].y);
    sort(p+1, p+n);


    vector<pts> hull_list;
    hull_list.push_back(p[0]);
    hull_list.push_back(p[1]);

    for (int i = 2; i < n; ++i) {
    
        while (hull_list.size() >= 2)
        {
            int l = hull_list.size();
            if (ccw(hull_list[l-2], hull_list[l-1], p[i]) > 0) break;
            hull_list.pop_back();
        }
        hull_list.push_back(p[i]);
    }

    // rotating calipers

    int ans = -1;
    int sz = hull_list.size();
    for (int i = 0; i < sz; ++i) {
        int j = (i+1)%sz;
        while (1)
        {
            ans = max(ans, dist(hull_list[i], hull_list[j]));
            if (ccw(hull_list[i], hull_list[(i+1)%sz], hull_list[j], hull_list[(j+1)%sz]) <= 0) break;
            j = (j+1)%sz;
        }
    }
    cout << ans;
    return 0;
}