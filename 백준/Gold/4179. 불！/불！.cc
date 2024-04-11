#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
#define f(a, b, c) for(int a=b; a<c;++a)
int n, m;
int v[1000][1000]; //불 이동
bool vv[1000][1000];  // 사람 이동
string mp[1000];
int mv[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
const int inf = 1e8;
struct io
{
    int r, c, d;
};


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    cin >> n >> m;

    f(i, 0, n) f(j, 0, m) {
        v[i][j] = inf;
    }
    queue<io> q;
    int sr, sc; // 지훈이 위치
    f(i, 0, n) {
        cin >> mp[i];
        f(j, 0, m) {
            if (mp[i][j] == 'F') {
                v[i][j] = 0;
                q.push({i, j, 0});
                mp[i][j] ='.';
            }
            else if (mp[i][j] == 'J') {
                sr = i; sc = j;
                mp[i][j] ='.';
                vv[i][j] = true;
            }
        }
    }

    while (!q.empty())
    {
        int r = q.front().r, c = q.front().c, d = q.front().d; q.pop();
        for (auto &[dr, dc] : mv) {
            int nr = r +dr, nc = c + dc;
            if (nr < 0 || nr >= n || nc < 0 || nc >= m || v[nr][nc] != inf) continue;
            if (mp[nr][nc] == '#') continue;
            v[nr][nc] = v[r][c] + 1;
            q.push({nr, nc, d+1});
        }
    }
    int ans = inf;
    q.push({sr, sc, 0});

    while (!q.empty())
    {
        int r = q.front().r, c = q.front().c, d = q.front().d; q.pop();
        // cout << r <<' ' << c <<  ' ' << d << '\n';
    
        for (auto &[dr, dc] : mv) {
            int nr = r +dr, nc = c + dc;
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) {
                ans = min(ans, d+1);
                continue;
            }
            if (vv[nr][nc]) continue;
            if (v[nr][nc] <= d+1) continue;
            if (mp[nr][nc] == '#') continue;
            vv[nr][nc] = true;
            q.push({nr, nc, d+1}); 
        }
    }

    if (ans == inf) cout <<"IMPOSSIBLE";
    else cout << ans;

    return 0;

}

// 먼저 각 위치마다 불이 도달 할 수 있는 최단거리 구하고
// 사람(지훈) 이가 각각 갈 수 있는 위치가 불이 도달하기 전보다 갈 수 있는 경우에만 다음 자리로 이동