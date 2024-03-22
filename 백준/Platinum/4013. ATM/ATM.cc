#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;
const int inf = 5e5+1;

int n, m, s, p; // 노드수 , 에지수 , 시작점, 도착점수
vector<vector<int> > adj; //인접그래프
vector< vector<int> > scc_adj; //scc그룹 간 인접그래프
vector<int> cash; //해당 인덱스 위치에서 뽑을 수 잇는 금액양

vector<int> restaurant; //도착지점

int scc_cnt = 0; //scc_id 등록용 변수.
int v_cnt = 0;// DFS spaning Tree
vector<int> visit_order; // DFS Tree 방문순서
vector<int> sccid; //sccid; 각 노드에서의 scc소속위치
int scc_cash[inf]; //scc id간 얻을 수 있는 캐시 총양
vector<int> dp; //scc 위상정렬상 얻을 수 있는 최대양
stack<int> st; //scc 함수용
bool v[inf]; //방문확인

int scc(int node) {
    int res = visit_order[node] = ++v_cnt;
    st.push(node);

    for (int next : adj[node]) {
        if (!visit_order[next]) {
            res = min(res, scc(next));
        }
        else if (!sccid[next]) {
            res = min(res, visit_order[next]);
        }
    }

    if (res == visit_order[node]) {
        scc_cnt++;
        int scc_prefix_cash = 0;
        while (1)
        {
            int scc_node = st.top(); st.pop();
            scc_prefix_cash += cash[scc_node];
            sccid[scc_node] = scc_cnt;
            if (scc_node == node) break;
        }
        scc_cash[scc_cnt] = scc_prefix_cash;
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    //setting
    
    //input -----

    //인접 그래프 입력
    cin >> n >> m;

    //vector 사이즈 할당
    adj.resize(n+1);
    visit_order.resize(n+1);
    sccid.resize(n+1);
    cash.resize(n+1);

    for (int i =0 ; i < m; ++i) {
        int a, b; cin >>a >> b;
        adj[a].push_back(b);
    }

    //ATM 보유 캐시 입력
    for (int i = 1; i <= n; ++i) cin >> cash[i];

    cin >> s >> p; //시작점 노드번호. 도착점갯수 
    restaurant.resize(p);
    //도착점
    for (int i = 0; i < p; ++i) cin >> restaurant[i];

    for (int i = 1 ; i <= n; ++i) {
        if (!visit_order[i]) scc(i);
    }
    dp.resize(scc_cnt+1);

    //scc그룹 간 인접그래프 만들기
    scc_adj.resize(scc_cnt+1);

    for (int i = 1; i <= n ; ++i) {
        if (visit_order[i] == 0) continue;
        for (int &next : adj[i]) {
            if (sccid[i] == sccid[next]) continue;
            if (sccid[next] == 0) continue;
            scc_adj[sccid[i]].push_back(sccid[next]);
        }
    }
    queue<int> q;
    //scc 위상정렬. 시작점 : s
    q.push(sccid[s]);
    dp[sccid[s]] = scc_cash[sccid[s]];
    while (!q.empty())
    {   
        int scc_now = q.front(); q.pop();
        for (int &next_scc : scc_adj[scc_now]) {
            int res = dp[scc_now] + scc_cash[next_scc];
            if (res > dp[next_scc]) {
                dp[next_scc] = res;
                q.push(next_scc);
            }
        }
    }
    
    int ans = 0;
    for (int &res_node : restaurant) {
        ans = max(ans, dp[sccid[res_node]]);
    }
    cout << ans;

    return 0;
}