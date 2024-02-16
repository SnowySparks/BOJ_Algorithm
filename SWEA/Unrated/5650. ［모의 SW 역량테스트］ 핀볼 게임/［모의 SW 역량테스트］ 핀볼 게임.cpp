#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define f(a,b,c) for(int a=b;a<c;++a)
#define DOWN 0
#define LEFT 1
#define UP 2
#define RIGHT 3
#define REFLECT -1

int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, -1, 0, 1};
int n, arr[102][102];
int wp[11][2][2]; //wp number
int wpcnt[11]; //wp counter
bool v[102][102][4];

struct info {
    int r, c, dir, cnt; //행, 열, 방향, 부딛친 횟수
    bool mv = false;
};


int block[6][4] = { //해당하는 블록에 도달하면, 가게 되는 방향
    {DOWN, LEFT, UP, RIGHT}, //air
    {RIGHT, UP, REFLECT, REFLECT}, //1
    {REFLECT, DOWN, RIGHT, REFLECT}, //2
    {REFLECT, REFLECT, LEFT, DOWN}, //3
    {LEFT, REFLECT, REFLECT, UP}, //4
    {-1, -1, -1, -1} //5
};


int simulation(int cr, int cc) {
    int res = 0;
    int nr = cr, nc = cc, dir = 0, cnt = 0;
    f(i, 0, 4) { //방향
        nr = cr;
        nc = cc;
        dir = i;
        cnt = 0;
        bool mved = false;
        while (true) {
            nr += dr[dir]; nc += dc[dir];
            // cout << nr << ' ' << nc << ' ' << dir << ' ' << cnt <<'\n';
            int blk_state = arr[nr][nc];
            //원점복귀
            if (nr == cr && nc == cc && mved) {
                res = max(res,cnt);
                break;
            }
            //블랙홀
            if (blk_state == -1) {
                res = max(res,cnt);
                break;                
            }
            //warp
            if (blk_state >= 6) {
                mved = true;
                if (nr == wp[blk_state][0][0] && nc == wp[blk_state][0][1]) {
                    nr = wp[blk_state][1][0]; nc = wp[blk_state][1][1];
                }
                else {
                    nr = wp[blk_state][0][0]; nc = wp[blk_state][0][1];
                }
            }
            //block
            if (blk_state > 0 && blk_state < 6) {
                dir = block[blk_state][dir];
                if (dir == REFLECT) {
                    res = max(res, cnt*2 + 1);
                    break;
                }
                else {
                    mved = true;
                    ++cnt;
                }
            }
            mved = true;
        }
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    f(tc, 1, T + 1) {
        //초기화
        memset(arr, 0, sizeof(arr));
        memset(wp, 0, sizeof(wp));
        memset(wpcnt, 0 , sizeof(wpcnt));
        memset(v, 0, sizeof(v));
        int ans = 0;
        //INPUT
        cin >> n;
        f(i, 1, n+1) {
            f(j, 1, n+1) {
                cin >> arr[i][j];
                if (arr[i][j] >= 6) { //warp data input
                    wp[arr[i][j]][wpcnt[arr[i][j]]][0] = i;
                    wp[arr[i][j]][wpcnt[arr[i][j]]][1] = j;
                    wpcnt[arr[i][j]]++;
                }
            }
        }
        //setting - 외벽
        f(i, 0, n+2) {
            arr[i][0] = 5;
            arr[i][n+1] = 5;
            arr[0][i] = 5;
            arr[n+1][i] = 5;
        }

        // ans = simulation(3, 4);
        // 각 위치마다 simulation
        f(r, 1, n+1) {
            f(c, 1, n+1) {
                if (arr[r][c] != 0) continue; //빈공간 아니면 스킵
                ans = max(ans, simulation(r, c));
                
            }
        }
        cout << '#' << tc <<' ' << ans <<'\n';
    }
    return 0;
}