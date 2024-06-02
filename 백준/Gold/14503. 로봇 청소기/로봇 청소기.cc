#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)
int mv[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // 북, 동, 남, 서;

int n, m; // max R, max C
struct robot { // Robot Status
    int r, c, dir;
};

int state[50][50]; // 0 : 청소상태 아님, 1 : 벽, 2 : 청소상태임

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    bool hasNotCleaned= false; //주변에 청소 여부
    cin >> n >> m;
    int r, c, d; // 처음 로봇 위치 + 방향
    cin >> r >> c >> d;
    f(r, 0, n) f(c, 0, m) cin >> state[r][c]; //map input
    int ans = 0;

    while (1)
    {
        //setting
        hasNotCleaned = false;

        //1. 청소
        if (state[r][c] == 0) {
            state[r][c] = 2;
            ++ans;
        }

        //회전 시도. 
        f(i, 1, 5) {
            int nd = (d - i + 4)%4; //반시계방향 회전
            int nr = r + mv[nd][0], nc = c + mv[nd][1];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m || state[nr][nc] == 1) continue; //범위 밖 혹은 벽

            if (state[nr][nc] == 0) { //청소 안한 곳임 이동할 곳이 발견됨
                r = nr; c = nc; d = nd;
                hasNotCleaned = true;
                break;
            }
        }
        if (hasNotCleaned) continue; //청소해야 할 공간 있음 1번으로
        else {
            r -= mv[d][0]; c -= mv[d][1];
            if (r < 0 || r >= n || c < 0 || c >= m || state[r][c] == 1) break; //이동불가 -> 종료
            else continue;
        }
    }
    cout << ans;
    return 0;
}