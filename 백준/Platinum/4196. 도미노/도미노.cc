#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
const int inf = 1e5+1;
bool isdone[inf];
int node_visit_order[inf];
int N, M;
vector<int> adj[inf];
stack<int> st;
int id = 0;
int ans = 0;
//vector<vector<int> > scc_list;
int scc_indegree[inf]; //idx = SCC그룹번호, 해당 그룹번호에서 indegree 정도
int scc_id[inf]; //해당 노드가 어느 SCC그룹에 있는지 기록
int scc_cnt; //scc그룹 총 수
//scc그룹 간의 위상정렬이 가능.
//타잔 알고리즘은. 위상정렬의 역순으로 scc_sublist가 담겨짐

//reset
void reset(int node) {
    for (int i = 0; i <= node; ++i) adj[i].clear();
    memset(node_visit_order,0,sizeof(node_visit_order));
    memset(scc_indegree,0,sizeof(scc_indegree));
    fill(isdone, isdone + node+1, false);
    id = 0;
    ans = 0;
    scc_cnt = 0;
}

int SCC(int node) { //->리턴 값 : 자기 자신의 최종 부모노드
    st.push(node); 
    node_visit_order[node] = ++id; // 1번
    int parent =  node_visit_order[node]; 
    for (int child : adj[node]) {
        //방문하지 않은 노드 
        if (node_visit_order[child] == 0) parent = min(parent, SCC(child)); 

        //방문했지만 아직 scc인지 판단 안된 노드
        else if (!isdone[child]) parent = min(parent, node_visit_order[child]); //이미 방문한 노드 -> 해당 자식이 사실은 부모임
    }
    if (parent == node_visit_order[node]) {
        scc_cnt++;
        while(true) {
            int t = st.top();
            st.pop();
            isdone[t] = true;
            scc_id[t] = scc_cnt;
            if (t == node) break; 
        }
    }
    return parent;//방문 순서로서의 최종 최상위 부모값.
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    //freopen("test_input.txt","r",stdin);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> N >> M;
        reset(N);

        //input
        for (int i = 0; i < M; ++i) {
            int fr, to;
            cin >> fr >> to;
            adj[fr].push_back(to);
        }

        //simulation
        for (int i = 1; i <= N ; ++i) {
            if (!isdone[i]) SCC(i);
        }

        //topological sort
        for (int i = 1; i <= N; ++i) {
            for (int nxt : adj[i]) {
                if (scc_id[i] == scc_id[nxt]) continue;
                scc_indegree[ scc_id[nxt] ]++;
            }
        }
        for (int i = 1; i <= scc_cnt ; ++i) {
            if (!scc_indegree[i]) ++ans;
        }
        cout << ans <<'\n';
    }
    return 0;
}