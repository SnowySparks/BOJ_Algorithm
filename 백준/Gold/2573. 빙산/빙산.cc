#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <deque>
#include <queue>
using namespace std;
#define f(a,b,c) for(int a=b;a<c;a++) 
using pii = pair<int,int>;

int n, m; // 행 크기, 열 크기
int gh[300][300];
int temp[300][300];
int mv[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool v[300][300];

void bfs(int r, int c) {
    v[r][c] = true;
    queue<pair<int, int> > q;
    q.push({r, c});
    while (!q.empty())
    {
        int cr = q.front().first, cc = q.front().second; q.pop();
        for (auto &[dr, dc] : mv) {
            int nr = cr + dr, nc = cc + dc;
            if (nr < 0 || nr >= n || nc < 0 || nc >= m || v[nr][nc] || gh[nr][nc] == 0) continue;
            v[nr][nc] = true;
            q.push({nr,nc});
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    cin >> n >> m;
    deque<pair<int, int> > dq;
    f(i,0,n) f(k,0,m) {
        cin >> gh[i][k];
        if (gh[i][k]) dq.push_back({i, k});
    }

    int year = 0;
    int cnt = 0;
    while (!dq.empty())
    {
        // 1. 섬 분리 여부 확인
        cnt = 0;
        memset(v, 0, sizeof(v));
        for (auto &[r, c] : dq) {
            if (!v[r][c]) {
                ++cnt;
                bfs(r, c);
            }
        }

        // 섬 분리 확인 -< 종료
        if (cnt> 1) break;

        // 안되면 분리작업 시작
        ++year;


        int query = dq.size();
        for (int i = 0; i < query; ++i) {
            int zero_cnt = 0;
            int r = dq.front().first, c = dq.front().second;
            dq.pop_front();

            for (auto &[dr, dc] : mv) {
                int nr = r + dr, nc = c + dc;
                if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                if (gh[nr][nc] == 0) zero_cnt++;
            }

            if (gh[r][c] - zero_cnt > 0) {
                temp[r][c] = gh[r][c] - zero_cnt;
                dq.push_back({r, c});
            }
        }

        if (dq.empty()) {
            year = 0;
            break;
        }

        memset(gh, 0, sizeof(gh));
        for (auto &[r, c] : dq) {
            gh[r][c] = temp[r][c];
        }
        memset(temp,0,sizeof(temp));
    }
    cout << year;
    return 0;
}