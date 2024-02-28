#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
const int inf = 2e9;
bool v[20][20][1<<10];
int num[20][20];
string inp[20];

int mv[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct info {
    int r, c, move, state;
};

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int total, sr, sc;//쓰레기 갯수, 시작점
    int R, C; //
    queue<info> q;
    while (true)
    {

        cin >> C >> R;
        if (R == 0 && C == 0) break;
        memset(v, 0, sizeof(v));
        memset(num, -1, sizeof(num));
        total = 0;
        for (int r = 0 ; r < R ; ++r) {
            cin >> inp[r];
            for (int c = 0; c < C; ++c) {
                if (inp[r][c] == 'o') {
                    sr = r; sc = c;
                    v[sr][sc][0] = true;
                    inp[r][c] = '.';
                }
                else if (inp[r][c] == '*') {
                    num[r][c] = total++;
                }
            }
        }
        int ans = inf;
        q.push({sr, sc, 0, 0});

        while (!q.empty()) {
            info p = q.front();
            q.pop();
            // cout << p.r << ' ' << p.c <<' ' << p.state <<'\n';
            if (p.state == ((1<<total)-1)) {
                ans = min(ans, p.move);
            }

            for (auto &[dr, dc] : mv) {
                int nr = p.r + dr, nc = p.c + dc;
                if (nr < 0 || nr >= R || nc < 0 || nc >= C || inp[nr][nc] =='x') continue;
                if (inp[nr][nc] == '.' && !v[nr][nc][p.state]) {
                    v[nr][nc][p.state] = true;
                    q.push({nr, nc, p.move + 1, p.state});
                }
                else if (inp[nr][nc] == '*') {
                    int new_state = p.state | (1 << num[nr][nc]);
                    if (!v[nr][nc][new_state]) {
                        q.push({nr, nc, p.move + 1, new_state});
                        v[nr][nc][new_state] = true;
                    }
                }
            }
        }

        cout << (ans == inf ? -1 : ans) <<'\n';
    }
    
    return 0;
}