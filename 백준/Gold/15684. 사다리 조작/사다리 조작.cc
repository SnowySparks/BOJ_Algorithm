#include <iostream>
using namespace std;
#define f(a,b,c) for(int a=b;a<c;++a)
int N, M, H;

int ans = 4;
bool ladder[32][12]; //가로줄 위치값, 세로줄 위치값, [a][b] = True이건 해당 a위치에 b, b+1 세로줄에 연결되어있음 의미
bool fd = false;

int go(int x) { //시작점이 x일때 끝점이 어디지?
    int nowh = 1;
    while (nowh <= H)
    {
        if (ladder[nowh][x]) ++x;
        else if (ladder[nowh][x-1]) --x;
        ++nowh;
    }
    return x;
}

bool check() { //전체 탐색하고 하나라도 원래 자리 안가면 False
    f(i, 1, N+1) {
        if (go(i) != i) return false;
    }
    return true;
}

void back_track(int nowh, int nowl, int cnt, int maxcnt) { //backtracking
    if (fd) return;
    if (maxcnt == cnt) {
        if (check()) {
            ans = cnt;
            fd = true;
        }
        return;
    }
    f(h, nowh, H+1) {
        int locl= (h == nowh ? nowl : 1);
        f(l, locl, N) {
            if (ladder[h][l-1] || ladder[h][l] || ladder[h][l+1]) continue;
            ladder[h][l] = true;
            back_track(h, l+1, cnt+1, maxcnt);
            if (fd) return;
            ladder[h][l] = false;
        }
    }
    return;
}

int main(void) { 
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> N >> M >> H;
    f(i, 0, M) {
        int a, b; cin >> a >> b;
        ladder[a][b] = true;
    }
    f(i, 0, 4) back_track(1, 1, 0, i);
    cout << (ans > 3 ? -1 : ans);
    return 0;

}