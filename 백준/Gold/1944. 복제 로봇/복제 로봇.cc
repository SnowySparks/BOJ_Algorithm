#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
#define f(a, b, c) for(int a=b; a<c; ++a)
#define pii pair<int, int>
int n, m; // 맵크기, 키 갯수
char mp[50][50]; // 맵 입력
pii pts[251]; // 키 위치 저장
int pts_num[251]; // 고유 키 번호 지정
int dist[251][251]; // 거리 저장
int v[251][251]; // 방문여부, -1 : 방문안함
int sr, sc; //시작위치

int parent[251]; // union-find

// 부모 찾기
int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}


// Union 연산
bool unite(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) return false;
    parent[max(pu, pv)] = min(pu, pv);
    return true;
}

int mv[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} }; // 이동방향

struct edge
{
    int u, v, w; // u, v : 노드번호, w : 가중치
    edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const edge& e) const { return w < e.w; }
    bool operator>(const edge& e) const { return w > e.w; }
};


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    memset(dist, -1, sizeof(dist));
    cin >> n >> m;
    f(i, 0, 251) parent[i] = i; // 부모 초기화
    int cnt = 0;
    queue<pii> q; // que
    vector<edge> edges; // 간선
    // 입력
    f(i, 0, n) f(j, 0, n) {
        cin >> mp[i][j];
        if (mp[i][j] == 'S' || mp[i][j] == 'K') {
            pts[cnt++] = {i, j};
        }
        if (mp[i][j] == 'S') {
            sr = i, sc = j;
        }
    }

    // bfs
    f(now_pts, 0, cnt) {

        // 초기화
        memset(v, -1, sizeof(v));
        v[pts[now_pts].first][pts[now_pts].second] = 0;
        q.push(pts[now_pts]);

        // bfs
        while (!q.empty()) {
            auto [cr, cc] = q.front(); q.pop();

            for (auto [dr, dc] : mv) {
                int nr = cr + dr, nc = cc + dc;
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue; //외벽
                if (v[nr][nc] != -1 || mp[nr][nc] == '1') continue; //방문했거나 벽임
                v[nr][nc] = v[cr][cc] + 1; // 방문처리
                q.push({nr, nc});
            }
        }

        // 거리 저장 (now_pts -> i)
        f(i, 0, cnt) {
            dist[now_pts][i] = v[pts[i].first][pts[i].second];
        }
    }

    // 간선 저장
    f(i, 0, cnt-1) {
        f(j, i+1, cnt) {
            if (dist[i][j] == -1) continue; //존재하지 않는 간선은 제거
            edges.push_back({i, j, dist[i][j]});
        }
    }

    // 간선 오름차순 가치
    sort(edges.begin(), edges.end());

    int ans = 0;
    int edge_cnt = 0; //edge 수, m개면 즉시 종료
    for (edge E : edges) {
        if (edge_cnt == m) break;
        int u = E.u, v = E.v, w = E.w;
        if (unite(u, v)) {
            ans += w;
            ++edge_cnt;
        }
    }
    cout << (edge_cnt == m ? ans : -1);

    return 0; 
}

// 문제풀이
// 각 노드 위치에서 원하는 대로 로봇 복제가 가능함. (단 시작점은 항상 고정 , 그러나 시작점부터도 복사가 가능)
// -> 즉 어떤 지점에서 다른 지점 가는데 한번만 거치도록 할 수 있다는 것
// 따라서 전체 노드로 가는 길의 총 거리 합이 가장 짧은 거리가 답이 됨 -> MST