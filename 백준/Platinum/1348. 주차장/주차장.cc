#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define f(a, b, c) for (int a = b; a < c; ++a)
using namespace std;
using pii = pair<int , int>;
int n, m;
const int inf = 1e9 + 7;
int mv[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

string s[50];//지도
vector<pii> car, park;//차 , 주차장
int vis[50][50]; //bfs시물레이션용, -1 : 방문없음

int dist[101][101];
int rassign[101];
bool v[101];

vector<int> adj[101];

// car시작점 기준 모든 정착지
void bfs(int st) {
    memset(vis, -1, sizeof(vis));
    vis[car[st].first][car[st].second] = 0;
    queue<pii> q;
    q.push(car[st]);

    while(!q.empty()) {
        int r= q.front().first, c = q.front().second; q.pop();

        for (auto &[dr, dc] : mv) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (s[nr][nc] == 'X') continue;
            if (vis[nr][nc] != -1) continue;

            vis[nr][nc] = vis[r][c] + 1;
            q.push({nr, nc});
        }
    }

    f(i, 0, park.size()) {
        auto [pr, pc] = park[i];
        if (vis[pr][pc] == -1) continue;
        dist[st][i] = vis[pr][pc];
        adj[st].push_back(i);
    }
}

bool dfs(int node, int limit_dist) {
    for (int nxt : adj[node]) {
        if (v[nxt] || dist[node][nxt] > limit_dist) continue;
        v[nxt] = true;
        if (rassign[nxt] == -1 || dfs(rassign[nxt], limit_dist)) {
            rassign[nxt] = node;
            return true;
        }
    }
    return false;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // 차, 주차 더미데이터
    cin >> n >> m;
    f(i, 0, n) {
        cin >> s[i];
        f(j, 0, m) {
            if (s[i][j] == 'C') {
                car.push_back({i, j});
            }
            else if (s[i][j] == 'P') {
                park.push_back({i, j});
            }
        }
    }

    // 절대 주차 다 하지 못함
    if (car.size() > park.size()) {
        cout << -1;
        return 0;
    }

    // 차가 없음
    if (car.empty()) {
        cout << 0;
        return 0;
    }



    f(i, 0, 101) {
        f(j, 0, 101) dist[i][j] = inf;
    }

    for (int i = 0; i < car.size(); ++i) bfs(i);


    // cout << '\n';
    // f(i, 0, car.size()) {
    //     f(j, 0, park.size()) {
    //         cout << i <<',' << j << ':' <<dist[i][j] <<'\n';
    //     }
    // }
    // cout << '\n';

    int l = 0, r = n*m;
    int ans = -1;
    while (l <= r)
    {
        int mid = (l + r)  >> 1;
        int cnt = 0;
        memset(rassign,-1,sizeof(rassign));

        for (int i = 0; i < car.size(); ++i) {
            memset(v, 0, sizeof(v));
            cnt += (dfs(i, mid) ? 1 : 0);
        }

        if (cnt == car.size()) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    cout << ans;

    return 0;
}