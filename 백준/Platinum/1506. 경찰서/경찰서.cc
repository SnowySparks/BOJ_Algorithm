#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#define f(a, b, c) for(int a=b;a<c;++a)
using namespace std;
const int inf =1e9+7;
int n;
int cost[101];
string inp;
vector<int> adj[101];

int dfsn[101], dfsn_cnt = 0;
bool isscc[101];
int ans = 0;
stack<int> st;

int scc(int node) {
    st.push(node);
    int parent = dfsn[node] = ++dfsn_cnt;
    for (int &nxt : adj[node]) {
        if (!dfsn[nxt]) parent = min(parent, scc(nxt));
        else if (!isscc[nxt]) parent = min(parent, dfsn[nxt]);
    }

    if (parent == dfsn[node]) {
        int check_ans = inf;
        while (true)
        {
            int scc_node = st.top(); st.pop();
            isscc[scc_node] = true;
            check_ans = min(check_ans, cost[scc_node]);
            if (scc_node == node) break;
        }
        ans += check_ans;
    }
    return parent;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    f(i, 1, n+1) cin >> cost[i];
    f(i, 1, n+1) {
        cin >> inp;
        f(j, 0, n) {
            if (inp[j] == '1') {
                adj[i].push_back(j+1);
            }
        }
    }
    f(i, 1, n+1) if (!dfsn[i]) scc(i);
    cout << ans;

}