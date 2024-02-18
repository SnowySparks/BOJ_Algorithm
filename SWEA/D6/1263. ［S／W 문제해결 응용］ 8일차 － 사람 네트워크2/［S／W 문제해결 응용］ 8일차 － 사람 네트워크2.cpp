#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 10000000
#define MAX_VAL 1000
#define f(a,b,c) for (int a=b;a<c;++a)
vector<int> adj[MAX_VAL+1];
int dist[MAX_VAL+1]; 
int n;

void adj_reset(int n) {
    f(i, 1, n+1) {
        adj[i].clear();
    }
}

int bfs(int x) {//x : 시작노드
    memset(dist, -1, sizeof(dist));
    dist[x] = 0;
    queue<int> q;
    q.push(x);

    while (!q.empty()) {
        int loc = q.front(); 
        q.pop();

        for (int &a : adj[loc]) {
            if (dist[a] != -1) continue;
            dist[a] = dist[loc] + 1;
            q.push(a);
        }
    }

    int res = 0;
    f(i, 1, n+1) res+=dist[i];
    return res;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    int tmp;
    for (int tc = 1; tc <=T;++tc) {
        int ans = INF;
        cin >> n;
        adj_reset(n);
        f(r, 1, n+1) {
            f(c, 1, n+1) {
                cin >> tmp;
                if (tmp) adj[r].push_back(c);
            }
        }
        f(i, 1, n+1) {
            ans = min(ans, bfs(i));
        }
        cout << '#' <<tc <<' ' << ans << '\n';
    }
    return 0;
}