#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int nv = 810;
const int inf = 1e9;
int n, k;

int c[nv][nv], f[nv][nv]; // capacity, flow
int prv[nv];
vector<int> adj[nv];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;

    // n 노드 :  n_in = 2n-1, n_out = 2n
    int s = 2, e =3;

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
    while (1)
    {
        memset(prv, -1, sizeof(prv));
        prv[s] = s;
        queue<int> q; q.push(s);
        while (!q.empty())
        {   
            int loc = q.front(); q.pop();
            for (int &nxt : adj[loc] ) {
                if (prv[nxt] == -1 && c[loc][nxt] - f[loc][nxt] > 0) {
                    prv[nxt] = loc;
                    q.push(nxt);
                }
            }
        }

        if (prv[e] == -1) break;

        int min_flow = inf;
        for (int i = e; i != s ; i = prv[i]) {
            min_flow = min(min_flow, c[prv[i]][i] - f[prv[i]][i]);
        }
        for (int i = e; i != s ; i = prv[i]) {
            f[i][prv[i]]-=min_flow;
            f[prv[i]][i]+=min_flow;
        }
        ans += min_flow;       
    }
    cout << ans;
}

// 원리 : 각각 도시에 대해 in, out 2가지 노드로 분할하고
// 각각 도시에는 in->out 단 1의 용량만 가지고 
// 최대유량 시행