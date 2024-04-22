#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#define f(a, b, c) for (int a = b; a <=c; ++a)
using namespace std;
const int inf = 1e9;
int n, m;
int c[205][205], f[205][205], w[205][205]; // w : cost

int dist[205], path[205]; // for spfa
bool v[205];

vector<int> adj[205];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int ans = 0;
    cin >> n >> m;
    int s = 0, e = n + m + 1;
    int tmp;
    // people -> sink
    f(i, m+1, m+n) {
        adj[i].push_back(e);
        adj[e].push_back(i);
        cin >> tmp;
        c[i][e] = tmp;
    }

    // source -> bookstore
    f(i, 1, m) {
        adj[s].push_back(i);
        adj[i].push_back(s);

        cin >> tmp;
        c[s][i] = tmp;
    }
    // bookstore -> people
    f(i, 1, m) {
        f(k, m+1, m+n) {
            adj[i].push_back(k);
            adj[k].push_back(i);

            c[i][k] = inf;
            cin >> tmp;

            w[i][k] = tmp;
            w[k][i] = -tmp;
        }
    }
    // mcmf
    while (1)
    {   
        queue<int> q;
        memset(path, -1, sizeof(path));
        memset(v, 0, sizeof(v));
        fill(dist, dist+e+2, inf);

        v[s] = true; path[s] = s; dist[s] = 0;
        q.push(s);

        while (!q.empty())
        {   
            int loc = q.front(); q.pop(); v[loc] = false;

            for (int &nxt : adj[loc]) {
                if (c[loc][nxt] - f[loc][nxt] > 0 && dist[nxt] > dist[loc] + w[loc][nxt]) {
                    dist[nxt] = dist[loc] + w[loc][nxt];
                    path[nxt] = loc;
                    if (!v[nxt]) {
                        v[nxt] = true;
                        q.push(nxt);
                    }
                }
            }
        }
        if (path[e] == -1) break;
        
        int min_allowflow = 2*inf;
        for (int i = e; i != s; i = path[i]) {
            min_allowflow = min(min_allowflow, c[path[i]][i]-f[path[i]][i]);
        }

        for (int i = e; i != s; i = path[i]) {
            ans += min_allowflow*w[path[i]][i];
            f[path[i]][i] += min_allowflow;
            f[i][path[i]] -= min_allowflow;
        }
        // cout << ans << '\n';

    }
    cout << ans;
    return 0;
}