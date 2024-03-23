#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
const int inf = 1e3+10;
int n, m;

int to_logic(int x) {
    if (x > 0) return 2*x-1;
    else return (-x)*2;
}

int to_node(int x) {
    if (x%2) return (x+1)>>1;
    return -(x>>1);
}

int scc_cnt = 0;
int scc_idcnt = 0;
vector<int> logic_adj[2*inf];
int sccid[2*inf];
int dfsn[2*inf];
stack<int> st;
bool v[2*inf];

void clear() {
    memset(sccid, 0, sizeof(sccid));
    memset(dfsn, 0, sizeof(dfsn));
    memset(v, 0, sizeof(v));
    scc_cnt = 0;
    scc_idcnt =0;
    for (int i = 1; i <= 2*n ; ++i) logic_adj[i].clear();
}



int scc(int node) {
    st.push(node);
    int res = dfsn[node] = ++scc_idcnt;

    for (int nxt : logic_adj[node]) {
        if (!dfsn[nxt]) res = min(res, scc(nxt));
        else if (!sccid[nxt]) res = min(res, dfsn[nxt]);
    }

    if (res == dfsn[node]) {
        scc_cnt++;
        while (1)
        {
            int nd = st.top(); st.pop();
            sccid[nd] = scc_cnt;
            if (nd == node) break;
        }
    }
    return res;
}

bool ispossible() {
    for (int i =1; i <= n; ++i) {
        if (sccid[to_logic(i)] == sccid[to_logic(-i)]) return false;
    }
    return true;
}

bool cango() { // 1번 노드는 진출 할 수 있는가? 무조건 1은 True여야지 함... 만약 1 -> -1 꼴이 있으면 ... 안됨
    queue<int> q;
    q.push(1); v[1] = 1;

    while (!q.empty())
    {   
        int loc = q.front(); q.pop();
        for (int &nxt : logic_adj[loc]) {
            if (!v[nxt]) {
                v[nxt] = 1;
                q.push(nxt);
            }
        }
    }

    if (v[2]) return false;
    return true;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int a, b;
    while (cin >> n >> m)
    {
        clear();
        for (int i = 1; i <= m; ++i) {
            cin >> a >> b;
            logic_adj[to_logic(-a)].push_back(to_logic(b));
            logic_adj[to_logic(-b)].push_back(to_logic(a));
        }

        for (int i =1 ; i <= 2*n ; ++i) {
            if (!dfsn[i]) scc(i);
        }
        if (!ispossible()) {
            cout <<"no\n";
            continue;
        }
        if (!cango()) {
            cout << "no\n";
        }
        else {
            cout <<"yes\n";
        }
         
    }
    

    return 0;
}