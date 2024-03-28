#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int inf = 1e9;
int n, m, k;
int capacity[2010][2010];
int flow[2010][2010];
int prv[2010];

// 1~ n : 사람, (n+1) ~ (n+m) : 일 , 
// source : 2001, 
 
vector<int> adj[2010]; 

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    int ans = 0;
    // source 노드번호 : 2001, sink 노드번호 2002, 특수 K노드 : 2003
    int s = 2001, e = 2002, t = 2003;

    int cnt, work;
    //input
    for (int i = 1; i <= n; ++i) {
        // source -> 사람
        adj[s].push_back(i);
        adj[i].push_back(s);
        capacity[s][i] = 1;

        // 특수 노드 -> 사람
        adj[t].push_back(i);
        adj[i].push_back(t);
        capacity[t][i] = k;

        cin >> cnt;

    // 사람 -> 일

        for (int k = 1; k <= cnt; ++k) {
            cin >> work;
            //일 보정, 일 노드 + n을 실질적 노드로 처리

            // 간선연결
            adj[i].push_back(work+n);
            adj[work+n].push_back(i);

            // 용량 설정
            capacity[i][work+n] = 1;
        }
    }

// 일 -> sink
    for (int i = n+1; i <= n+m; ++i) {
        adj[i].push_back(e);
        adj[e].push_back(i);
        capacity[i][e] = 1;
    }

// source -> 특수 노드
    adj[s].push_back(t);
    adj[t].push_back(s);
    capacity[s][t] = k;


    // 최대 유량 구하기
    while (1)
    {
        memset(prv, -1, sizeof(prv));
        prv[s] = s;
        queue<int> q;
        q.push(s);

        while (!q.empty() && prv[e] == -1)
        {
            int loc = q.front(); q.pop();
            for (int nxt : adj[loc]) {
                if (prv[nxt] == -1 && capacity[loc][nxt] - flow[loc][nxt] > 0) {
                    prv[nxt] = loc;
                    if (nxt == e) break;
                    q.push(nxt);
                }
            }
        }

        if (prv[e] == -1) break;

        int f = inf;
        for (int i = e; i !=s ; i = prv[i]) {
            f = min(f, capacity[prv[i]][i] - flow[prv[i]][i]); 
        }
        for (int i = e; i !=s ; i = prv[i]) {
            flow[prv[i]][i] += f;
            flow[i][prv[i]] -= f;
        }

        ans += f;
    }
    cout << ans;
    return 0;
}