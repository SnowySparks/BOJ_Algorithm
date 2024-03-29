#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int nv = 810;
const int inf = 1e9;
int n, k;

int s = 2, e = 3;
int lv[nv], work[nv]; //레벨 (방문 걸이), 각 노드별 현 탐색 위치
int c[nv][nv], f[nv][nv]; // capacity, flow
vector<int> adj[nv];


// 디닉 알고리즘 응용 -bfs
bool bfs() {
    memset(lv, -1, sizeof(lv));
    lv[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        int loc = q.front(); q.pop();
        for (int &nxt : adj[loc]) {
            if (lv[nxt] == -1 && c[loc][nxt] - f[loc][nxt] > 0) {
                lv[nxt] = lv[loc]+1;
                q.push(nxt);
            }
        }
    }
    return lv[e]!=-1;
}

// 디닉 알고리즘 - dfs : 잔여 용량 찾기
int dfs(int now, int dest, int flow) {
    if (now == dest) return flow;
    for (int &i = work[now]; i < (int)adj[now].size(); ++i) {
        int nxt = adj[now][i];
        if (lv[nxt] == lv[now]+1 && c[now][nxt] - f[now][nxt] > 0) {
            int df = dfs(nxt, dest, min(flow, c[now][nxt] - f[now][nxt]));
            if (df > 0) {
                f[now][nxt] += df;
                f[nxt][now] -= df;
                return df;
            }
        }
    }
    return 0;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;

    // n 노드 :  n_in = 2n-1, n_out = 2n

    for (int i = 3; i <= n; ++i) {
        c[i*2-1][i*2] = 1;
        adj[i*2-1].push_back(i*2);
        adj[i*2].push_back(i*2-1);
    }
    int fr, to;
    while (k--)
    {
        cin >> fr >> to;
        int fr_in = fr*2-1, fr_out = fr*2, to_in = to*2-1, to_out=to*2;
        c[fr_out][to_in] = inf;
        c[to_out][fr_in] = inf;
        // 정방향. 역방향 전부 넣기
        adj[fr_out].push_back(to_in);
        adj[to_in].push_back(fr_out);
        adj[to_out].push_back(fr_in);
        adj[fr_in].push_back(to_out);

    }
    int ans = 0;
    while (bfs())
    {   
        memset(work, 0, sizeof(work));
        int flow = dfs(s,e,inf);
        if (flow) ans += flow;
        else break;
    }
    
    
    cout << ans;
    return 0;
}

// 원리 : 각각 도시에 대해 in, out 2가지 노드로 분할하고
// 각각 도시에는 in->out 단 1의 용량만 가지고 
// 최대유량 시행