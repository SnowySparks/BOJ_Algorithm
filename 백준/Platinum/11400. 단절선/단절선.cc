#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAX_V 100001
int v, e;
vector<int> gh[MAX_V];
int dfsn[MAX_V];
int cnt = 0;
int ans = 0;
vector<pair<int ,int> > cutEdge;

int dfs(int node, int pnode = -1) {
    //방문순서 갱신
    int res = dfsn[node] = ++cnt; //방문순서 등록
    //res의미 : DFS 트리상에서 트리, 역방향 간선으로 도달 가능한 최소의 dfsn

    for (int child : gh[node]) {
        if (child == pnode) continue;
        if (dfsn[child]) { // BackEdge 존재한다는 의미로 현재 노드에서 가장 높은 (값은 작은) 값 갱신
            res = min(res, dfsn[child]);
        }
        else {
            //트리 간선 영억. 리프 노드가 실행 할 곳은 안됨
            int prev = dfs(child, node); // 다음 자식에 대한 자식들이 갈 수 있는 가장 높은 위치(방문순서 작은) 값 가져오기

            //해당 node - child 노드를 통해서 갈 수 있는 위치가 
            if (prev > dfsn[node]) {
                cutEdge.push_back({min(node, child), max(node, child)});
            }
            //만약 어떤 자식이 올라 갈 수 있는 위치가 더 높은(즉 더 먼저 방문했는) 것이 존재할 경우 현재 노드도 그 위치에 갈 수 있다는 것이니 갱신
            res = min(prev, res);
        }
    }
    //DFS Tree의 노드에 대한처리. 만약 루트 노드에 대해서 자식이 2개이상이면 무조건 루트 노드도 단절점임
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> v >> e;
    for (int i = 0; i < e; ++i) {
        int a, b; cin >> a >> b;
        gh[a].push_back(b);
        gh[b].push_back(a);
    }
    for (int i = 1; i <= v; ++i) {
        if (dfsn[i] == 0) dfs(i);
    }
    cout << cutEdge.size() <<'\n';
    sort(cutEdge.begin(), cutEdge.end());
    for (auto &nd : cutEdge) {
        cout << nd.first <<' ' << nd.second <<'\n';
    }
    return 0;
}