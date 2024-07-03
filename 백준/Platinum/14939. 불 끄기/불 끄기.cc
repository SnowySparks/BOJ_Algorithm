#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define f(a, b, c) for(int a=b;a<c;++a)
const int inf = 1e9+7;
const int n = 10;
int m[10][10], copy_m[10][10];

int mv[5][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {0, 0}};

void tg(int r, int c) {
    for (auto &[dr, dc] : mv) {
        int nr = r + dr, nc = c + dc;
        if (nr < 0 || nr >=n || nc < 0 || nc >= n) continue;
        copy_m[nr][nc] ^= 1;
    }
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    char ch;
    f(i, 0, n) {
        f(j, 0, n) {
            cin >> ch;
            m[i][j] = (ch == 'O' ? 1 : 0);
        }
    }

    int ans = inf;

    f(st, 0, 1<<n) { //첫 줄 버튼 입력 state 모든 경우의 수
        copy(&m[0][0], &m[0][0]+100, &copy_m[0][0]);
        int cnt = 0;

        f(i, 0, n) {
            if ( st & (1 << i)) {
                tg(0, i);
                ++cnt;
            }
        }

        // 이후 2번째 줄부터는(2번째 행) 그 직전 행의 동일한 열 위치에서 불이 켜저 있으면
        // 그 불을 끄기 위해 토글
        f(r, 1, n) {
            f(c, 0, n) {
                if (copy_m[r-1][c]) {
                    ++cnt;
                    tg(r, c);
                }
            }
        }

        // 마지막 줄에 불 켜진게 있으면 그건 실패한 케이스
        f(i, 0, 10) {
            if (copy_m[n-1][i]) {
                cnt = inf;
                break;
            }
        }
        ans = min(ans, cnt);
    }

    cout << (ans == inf ? -1 : ans);
    return 0;
}