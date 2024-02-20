#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAX_V 10001
int v, e;
vector<int> gh[MAX_V];
int dfsn[MAX_V];
int cnt = 0;

vector<int> curVetex;

int dfs(int node, int pnode = -1) {
    //방문순서 갱신
    int res = dfsn[node] = ++cnt; //방문순서 등록
    //res의미 : DFS 트리상에서 트리, 역방향 간선으로 도달 가능한 최소의 dfsn
    
    int childcnt = 0; //DFS Spanning Tree상 자식갯수
    bool isCurVertex = false; //

    for (int child : gh[node]) {
        if (child == pnode) continue;
        if (dfsn[child]) { // BackEdge 존재한다는 의미로 현재 노드에서 가장 높은 (값은 작은) 값 갱신
            res = min(res, dfsn[child]);
        }
        else {
            //트리 간선 영억. 리프 노드가 실행 할 곳은 안ㄷ됨
            childcnt++;
            int prev = dfs(child, node); // 다음 자식에 대한 자식들이 갈 수 있는 가장 높은 위치(방문순서 작은) 값 가져오기
            //만약 해당 자식이 갈 수 있는 높은 곳이 높아봤자 현재 노드 ( 즉 자식들이 올라 갈 수 있는 위치가 현재 노드 방문순서보다 크거나 같을때)
            //인 경우 node는 무조건 단절점이 된다. 단 루트는 이것에 적용되지 않음
            if (pnode != -1 && prev >= dfsn[node]) isCurVertex = true;
            //만약 어떤 자식이 올라 갈 수 있는 위치가 더 높은(즉 더 먼저 방문했는) 것이 존재할 경우 현재 노드도 그 위치에 갈 수 있다는 것이니 갱신
            res = min(prev, res);
        }
    }
    //DFS Tree의 노드에 대한처리. 만약 루트 노드에 대해서 자식이 2개이상이면 무조건 루트 노드도 단절점임
    if (pnode == -1 && childcnt >=2) isCurVertex =true;
    if (isCurVertex) curVetex.push_back(node);// 단절점에 대한 값 추가
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
    cout << curVetex.size() <<'\n';
    sort(curVetex.begin(), curVetex.end());
    for (int &nd : curVetex) {
        cout << nd <<' ';
    }
    return 0;
}