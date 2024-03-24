#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using ll = long long;
const int inf = 1e4+ 1;
vector<pair<int ,int> > adj[inf];
ll dp[inf];
int sub_node_cnt[inf]; // 자기 자신 포함 루트 0 기준 하위 트리 노드 개수
ll ans = 0; //최종 답

void dfs(int node, int pnode, ll psum = 0) { //루트 0 기준으로 sub_node_cnt, 및 ans 구하기
    sub_node_cnt[node] = 1;
    ans += psum;
    for (auto &[nxt, cost] : adj[node]) {
        if (nxt == pnode) continue;
        dfs(nxt, node, psum + cost);
        sub_node_cnt[node] += sub_node_cnt[nxt];
    }
}

void solve(int node, int pnode, ll pre_sum, int before_weight) { //0번 - 
    ll res = pre_sum - (sub_node_cnt[node])*before_weight + (sub_node_cnt[0]-sub_node_cnt[node])*before_weight;
    ans = min(ans, res);
    for (auto &[nxt, cost] : adj[node]) {
        if (nxt == pnode) continue;
        solve(nxt, node, res, cost);
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    int fr, to, cost;
    while (1)
    {
        cin >> n;
        if (n == 0) break;
        for(int i = 0; i <= n; ++i) adj[i].clear();
        memset(dp, 0, sizeof(dp));
        memset(sub_node_cnt, 0, sizeof(sub_node_cnt));
        ans = 0;

        for (int i = 0; i < n-1; ++i) {
            cin >> fr >> to >> cost;
            adj[fr].push_back({to, cost});
            adj[to].push_back({fr, cost});
        }

        dfs(0, -1, 0);
        // cout << ans << '\n';
        // cout << sub_node_cnt[0] << '\n';
        // cout <<"--\n";
        ll tmp = ans;
        for (auto &[nxt, cost] : adj[0]) {
            solve(nxt, 0, tmp, cost);
        }
        cout << ans << '\n';
    }
    

    return 0;
}