#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;
const int inf = 1e5+1;
int V, E;
vector<int> adj[inf];
int node_id[inf]; //방문 순서 저장용. 값이 작을수록 높은 위치에 있다고 봄
int id = 0;
bool finish[inf]; //SCC로 처리된 노드 표시
vector<vector<int> > scc_list;
stack<int> st;
//SCC - Strongly Connected Component (강한 연결 요소)
//유향그래프에서 SCC 집단 : 해당 집단 내 어느 두 종점을 잡으면 어떠한 방법으로든 갈 수 있음
//해당 알고리즘에서 SCC는 maximum group을 구함. 따라서 SCC 그룹 내에선 어떠한 두 종점을 고르든 이동이 가능
//하지만 SCC집단 끼리는 사이클도 발생하지 않으며, SCC집단들로 위상정렬(Topology sort)가 가능하다
//효율적은 방식을 위해 타잔 알고리즘 O(V + E) 사용하며, dfs + stack 방식을 이용함


// 타잔 알고리즘의 구체적인 방법
// 1. 방문하지 않은 노드에 대해선 id값을 (보통 x번째 접근) 갱신해서 저장 -> 해당 노드는 SCC탐색 여부 불분명하지만 함수를 거친 상태( SCC함수 초기)
// 2. 방문할 때마다 임의의 stack에 방문 정점을 저장한다. (즉 1번시행 시작할 때 동시에)
//    그리고 방문하지 않는 노드들의 자식들에 대해서 재귀함수를 시행함
//    해당 노드의 자식 노드가 이미 방문한 노드했지만 아직 scc판단이 안된 경우, 해당 child노드는 사실 부모노드임
// 3. 해당 노드의 DFS가 끝난 경우에는, 자신의 id값이 스택에서 나올 때까지 스택에 있는 노드들을 pop하고 scc 배열에 추가함.

int SCC(int node) { //->리턴 값 : 자기 자신의 최종 부모노드
    st.push(node); // 2번
    node_id[node] = ++id; // 1번
    int parent =  node_id[node]; //방문 순서로서의 부모값. 처음은 자기자신
    for (int child : adj[node]) {
        //방문하지 않은 노드 
        if (node_id[child] == 0) parent = min(parent, SCC(child)); //2번 -> 방문하지 않은 노드들의 재귀적인 접근

        //방문했지만 아직 scc인지 판단 안된 노드
        else if (!finish[child]) parent = min(parent, node_id[child]); //이미 방문한 노드 -> 해당 자식이 사실은 부모임
    }
    if (parent == node_id[node]) {// 자신과 자신의 자식 정점들이 갈 수 있는 가장 높은 정점이 자신일 경우 SCC 추출
        vector<int> scc_sublist;
        while(true) {
            int t = st.top();
            st.pop();
            scc_sublist.push_back(t);
            finish[t] = true;
            if (t == node) break; 
        }
        sort(scc_sublist.begin(), scc_sublist.end());
        scc_list.push_back(scc_sublist);
    }
    return parent;//방문 순서로서의 최종 최상위 부모값.
}



int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    //input
    cin >> V >> E;
    for (int i = 0 ; i < E ; ++i) {
        int fr, to; cin >> fr >> to;
        adj[fr].push_back(to);
    }

    //연결이 안된 그래프 꼴 대비
    for (int i = 1 ; i <= V; ++i) {
        if (node_id[i] == 0) SCC(i);
    }
    sort(scc_list.begin(), scc_list.end());
    cout <<(int) scc_list.size() <<'\n';
    for (vector<int> &slist : scc_list) {
        for (int a : slist) {
            cout << a <<' ';
        }
        cout << -1 <<'\n';
    }
    return 0;
}