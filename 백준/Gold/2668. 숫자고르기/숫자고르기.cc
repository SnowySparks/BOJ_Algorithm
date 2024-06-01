#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
const int inf = 1e8;
int n;
int adj[101]; // 다음 노드
vector<int> ans;
vector<int> sub_ans;
int dfsn[101];
int dfsn_id = 0;
bool isscc[101];
stack<int> st;
int dfs(int x) {
    st.push(x);
    dfsn[x] = ++dfsn_id;
    int top_dfsn_num = dfsn[x];

    if ( dfsn[ adj[x] ] == 0 ) top_dfsn_num = min(top_dfsn_num, dfs(adj[x]));
    else if (!isscc[adj[x]]) top_dfsn_num = min(top_dfsn_num, dfsn[adj[x]]);

    if (top_dfsn_num == dfsn[x]) { 
        while (1)
        {
            int top = st.top(); st.pop();
            sub_ans.push_back(top);
            isscc[top] = true;
            if (top == x) {
                if (sub_ans.size() > 1) {
                    for (int &a : sub_ans) ans.push_back(a);
                }
                else {
                    if (adj[x] == x) ans.push_back(x);
                }
                sub_ans.clear();
                break;
            }
        }
        
    }
    return top_dfsn_num;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> adj[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (dfsn[i] == 0) dfs(i);
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int &a : ans) cout << a << '\n';
    return 0;
}