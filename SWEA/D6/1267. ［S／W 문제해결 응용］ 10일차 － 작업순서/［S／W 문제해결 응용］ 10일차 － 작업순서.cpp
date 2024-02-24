#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int v, e;
int indegree[1001];
vector<int> gh[1001];
int order[1001];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T = 10;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> v >> e;
        for (int i = 1; i <= v; ++i) gh[i].clear();
        memset(indegree, 0, sizeof(indegree));
        for (int i = 1; i <= e; ++i) {
            int p, c; cin >> p >> c;
            gh[p].push_back(c);
            ++indegree[c];
        }

        queue<int> q;
        for (int i = 1; i <= v ; ++i) {
            if (!indegree[i]) q.push(i);
        }

        int idx = 1;
        while (!q.empty()) {
            int node = q.front(); q.pop();
            order[idx++] = node;
            for (int &child : gh[node]) {
                --indegree[child];
                if (!indegree[child]) q.push(child);
            }
        }
        cout << '#' << tc;
        for(int i = 1; i <= v; ++i) {
            cout <<' ' << order[i];
        }
        cout <<'\n';
    }
    return 0;
}