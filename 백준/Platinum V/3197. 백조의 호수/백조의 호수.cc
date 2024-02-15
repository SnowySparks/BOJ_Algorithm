#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
int R, C;
string dt[1500];
int gh[1500][1500];
int dr[] {-1, 1, 0, 0};
int dc[] {0, 0, 1, -1};

vector<int> p;
int parent(int a) {
    if (p[a] == a) return a;
    return p[a] = parent(p[a]);
}

int _union(int a, int b) {
    a = parent(a);
    b = parent(b);
    if (a == b) return false;
    p[max(a,b)] = min(a, b);
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    p.push_back(0);
    cin >> R >> C;
    int fd = 0;
    pair<int ,int > a[2];
    for (int i = 0 ; i < R; ++i) {
        cin >> dt[i];
        if (fd < 2) {
            for (int j = 0 ; j < C ; ++j) {
                if (dt[i][j]=='L') {
                    dt[i][j] = '.';
                    a[fd].first = i;
                    a[fd].second = j;
                    ++fd;
                }
            }
        }
    }
    int cnt = 0;
    queue<pair<int ,int> > tmp; // 시물레이션용, bfs 영역표시용
    deque<pair<int ,int> > q;
    //영역 구분
    for (int i = 0 ; i < R; ++i) {
        for (int j = 0 ; j < C ; ++j) {
            if (dt[i][j] =='.' && gh[i][j] == 0) {
                ++cnt;
                p.push_back(cnt);
                gh[i][j] = cnt;
                tmp.push({i, j});
                q.push_back({i, j});
                while(!tmp.empty()) {
                    int r = tmp.front().first, c = tmp.front().second; tmp.pop();
                    for (int d = 0; d < 4; ++d) {
                        int nr = r + dr[d], nc = c + dc[d];
                        if (nr < 0 || nc < 0 || nr >= R || nc >= C || gh[nr][nc] || dt[nr][nc]=='X') continue;
                        gh[nr][nc] = cnt;
                        tmp.push({nr, nc});
                        q.push_back({nr, nc});
                    }
                }
            }
        }
    }
    int t = 0;
    //simulation
    while (!q.empty()) {
        //먼저 해당 물에 대해서 주변 물 탐색
        for (auto [r, c] : q) {
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr < 0 || nc < 0 || nr >= R || nc >= C || gh[nr][nc] == 0) continue;
                _union(gh[r][c], gh[nr][nc]);
            }
        }

        //만약 두 백조가 같은 곳에 있으면 종료
        if (parent(gh[a[0].first][a[0].second]) == parent(gh[a[1].first][a[1].second])) break;

        //아닌 경우 - 녹이기.
        ++t;
        int query = (int) q.size();
        while (query--) {
            int r = q.front().first, c = q.front().second; q.pop_front();
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr < 0 || nc < 0 || nr >= R || nc >= C || gh[nr][nc]) continue;
                gh[nr][nc] = gh[r][c];
                q.push_back({nr, nc});
            }
        }
    }

    cout << t;
    return 0;

}