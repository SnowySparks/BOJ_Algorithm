#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <algorithm>
#define NMAX 100002 
using namespace std;
int n, m;
vector<int> adj[NMAX];
// scc전용 변수들
int sccid_cnt;
int seq_cnt;
int sccid[NMAX];
int seq[NMAX];
int scc_indegree[NMAX];
stack<int> st;

void reset() {
    sccid_cnt = 0;
    seq_cnt = 0;
    memset(sccid, 0 , sizeof(sccid));
    memset(seq, 0 , sizeof(seq));
    memset(scc_indegree, 0 , sizeof(scc_indegree));
    for (int i = 0; i < NMAX ;++i) adj[i].clear();
    // cout << sccid_cnt <<' ' << seq_cnt  << '\n';
}

int scc(int node) {
    st.push(node);
    seq[node] = ++seq_cnt;
    int min_vis = seq[node];
    for (int &child : adj[node] ) {
        if (!seq[child]) min_vis = min(min_vis, scc(child));
        else if (!sccid[child]) min_vis = min(min_vis, seq[child]);
    }
    if (min_vis == seq[node]) {
        ++sccid_cnt;
        while (1)
        {
            int tmp = st.top(); st.pop();
            sccid[tmp] = sccid_cnt;
            if (tmp == node) break;
        }
    }
    return min_vis;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int a, b;
    int T; cin >> T;
    for (int tc = 0; tc < T; ++tc) {
        cin >> n >> m;
        reset();
        while (m--)
        {
            cin >> a >> b;
            adj[a].push_back(b);
        }

        for (int i = 0; i < n; ++i) {
            if (!seq[i]) {scc(i);}
        }
        int scc_zero_indegree = 0, scc_zero_indegree_loc = -1;
        for (int i =0; i <n; ++i) {
            for (int &child : adj[i]) {
                if (sccid[i] != sccid[child]) scc_indegree[sccid[child]]++;
            }
        }
        for (int i = 1; i <= sccid_cnt; ++i) {
            if (!scc_indegree[i]) {
                scc_zero_indegree++;
                scc_zero_indegree_loc = i;
            }
        }

        if (scc_zero_indegree > 1) cout << "Confused\n";
        else {
            for (int i = 0; i < n; ++i) {
                if (sccid[i] == scc_zero_indegree_loc) cout << i << '\n';
            }
        }
        cout <<"\n";
    }
    return 0;
}

// SCC 간은 결국 위상 정렬이 되므로
// indegree가 0개인 SCC 그룹이 1개인 경우에 한해서 그 SCC그룹을 출력하고
// 그 외는 전부 Confused임