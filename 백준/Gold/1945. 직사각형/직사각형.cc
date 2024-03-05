#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct io {
    int x, y, w; //x, y 위치, 가중치
};
bool comp(const io &a, const io &b) {
    double al = (double)a.y/a.x;
    double bl = (double)b.y/b.x;
    if (al == bl) return a.w > b.w;
    return al > bl;
}
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<io> dt;
    int xbl, ybl, xtr, ytr;
    for (int i = 0 ; i < n; ++i) {
        cin >> xbl >> ybl >> xtr >> ytr;
        dt.push_back({xbl, ytr, 1});
        dt.push_back({xtr, ybl, -1});
    }
    sort(dt.begin(), dt.end(), comp);
    int cnt = 0;
    int ans = 0;
    for (io &c : dt) {
        ans = max(ans, cnt);
        cnt += c.w;
    }
    cout << ans;
    return 0;
}

//원리 : 직사각형 죄측상단, 우측하단을 가지고 함
//기울기를 가장 높은 것부터 시작해서 점차 낮아지는 방향으로 서서히 이동하면 좌측상단 부터 거치고, 우측하단 지남
//즉 기울기를 낮추면서 좌측상단 점 만나면 해당 직사각형은 해당 줄 통과한다는 뜻히고
//우측 하단 만나고 나서 기울기 낮아지면 해당 직사각형은 만날 수 없음을 의미