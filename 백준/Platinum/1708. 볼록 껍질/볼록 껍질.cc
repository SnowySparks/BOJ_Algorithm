#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
using ll = long long;

class pts {
    public:
        int x, y, rx, ry; //절대 좌표 x, y // 상대좌표 rx, ry;
        pts() : x(0), y(0), rx(0), ry(0) {}
        pts(int x, int y) :x(x), y(y), rx(0), ry(0) {}
        pts(int x, int y, int rx, int ry) : x(x), y(y), rx(rx), ry(ry) {}
        pts(const pts &a) {
            x = a.x; y=a.y; rx=a.rx; ry = a.ry;
        }
        //비교연산자
        // 가장 먼저 기준점과 자기 점의 각도가 가장 작은것 우선연산, 만약 동일하면, y가 작을수록 그리고 x가 작을수록 작다고 판단
        bool operator<(const pts &a) const {
            if (1LL*ry*a.rx != 1LL*rx*a.ry) return 1LL*ry*a.rx < 1LL*rx*a.ry; // tan 기울기 이용. - 수직,수평 경우 제외
            if (y!=a.y) return y<a.y; //수직차기 았는 경우 더 작은 쪽
            return x <a.x; //수평 경우가 있는 경우 더 작은쪽
        }
        void cal_relative(int ptx, int pty);

        void datas(void) {
            cout << x << ' ' << y << ' ' << rx <<' ' <<ry <<'\n';
        }
};

void pts::cal_relative(int ptx, int pty) {
    rx = x- ptx; ry =y-pty;
}

ll ccw(const pts &a, const pts &b, const pts &c) {
    return  1LL*(b.x - a.x)*(c.y-a.y) - 1LL*(c.x-a.x)*(b.y-a.y);
}

int main(void) {
    int n; cin >> n;
    vector<pts> arr(n,pts());
    for (int i = 0 ; i < n ; i++) {
        cin >> arr[i].x >> arr[i].y;
        if (i > 0 && arr[i] < arr[0]) swap(arr[i],arr[0]);
    }
    for (int i = 1 ; i < n; i++) arr[i].cal_relative(arr[0].x, arr[0].y);
    sort(arr.begin()+1, arr.end());
    stack<int> s; s.push(0); s.push(1);
    for (int i = 2 ; i < n ; i++) {
        while ((int)s.size() >= 2) {
            int fir, sec;
            sec = s.top(); s.pop();
            fir = s.top();
            if (ccw(arr[fir],arr[sec],arr[i]) > 0) {
                s.push(sec);
                break;
            }
        }
        s.push(i);
    }
    cout << (int)s.size();

    return 0;
}