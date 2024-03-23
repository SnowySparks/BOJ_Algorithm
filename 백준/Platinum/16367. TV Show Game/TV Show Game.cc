#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
#define R 1
#define B -1
const int max_k = 5e3+2;
int k, n; //lamp수, 사람 수

int to_logic(int x) {
    if (x > 0) return 2*x -1;
    return (-x)*2;
}

vector<int> logic_adj[2*max_k];

int dfsn_cnt = 0;
int scc_idcnt = 0;
int dfsn[2*max_k];
int sccid[2*max_k];
stack<int> st;

int scc(int node) {
    int res = dfsn[node] = ++dfsn_cnt;
    st.push(node);

    for (int &nxt : logic_adj[node]) {
        if (!dfsn[nxt]) res = min(res, scc(nxt));
        else if (!sccid[nxt]) res = min(res, dfsn[nxt]);
    }
    if (res == dfsn[node]) {
        scc_idcnt++;
        while (1)
        {
            int tp = st.top(); st.pop();
            sccid[tp] = scc_idcnt;
            if (tp == node) break;
        } 
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    cin >> k >> n;
    // ( A + B) * (B + C) * (C + A) 논리관계이용
    int a, b, c; char ac, bc, cc;
    for (int i = 1; i <= n; ++i) {
        cin >> a >> ac >> b >> bc >> c >> cc;
        if (ac == 'B') a=-a;
        if (bc == 'B') b=-b;
        if (cc == 'B') c=-c;

        //a-b관계
        logic_adj[to_logic(-a)].push_back(to_logic(b));
        logic_adj[to_logic(-b)].push_back(to_logic(a));

        //a-c관계
        logic_adj[to_logic(-a)].push_back(to_logic(c));
        logic_adj[to_logic(-c)].push_back(to_logic(a));

        //b-c관계
        logic_adj[to_logic(-b)].push_back(to_logic(c));
        logic_adj[to_logic(-c)].push_back(to_logic(b));

    }
    for (int i = 1; i <= 2*k; ++i) if (!dfsn[i]) scc(i);
    string ans = "";

    for (int i = 1; i <= k; ++i)  {
        if (sccid[to_logic(i)] == sccid[to_logic(-i)]) {
            ans ="-1";
            break;
        }
        ans.push_back((sccid[to_logic(i)] < sccid[to_logic(-i)] ? 'R' : 'B'));
    }
    cout << ans;
    return 0;
}