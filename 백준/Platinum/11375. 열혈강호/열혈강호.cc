#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#define f(a, b, c) for(int a= b; a<c;++a)
using namespace std;

vector<int> adj[1001];
int right_assign[1001]; // Right i 노드는 LEft어떤 노드랑 매칭중인가?
bool v[1001]; // DFS 진행중, right i 노드가 고려된 적이 있는가? -> 매 첫 호출때마다 초기화

bool dfs(int left_node) {
    // cout << left_node <<'\n';
    for (int &right_node : adj[left_node]) { // 현재 왼쪽 노드랑 연결된 오른쪽 노드 전부 탐색
        if (v[right_node]) continue; //만약 한번이라도 해당 오른쪽 노드가 탐색 시도 한 기록 있음 종료
        v[right_node] = true; //지금 현재 오른쪽 노드를 탐색 시도 기록 남기기
        if (right_assign[right_node] == 0 || dfs(right_assign[right_node])) {
            //현재 해당 오른쪽 노드가 매칭이 안되어있거나, 이미 그거랑 연결된 왼쪽 노드가 또 다른 오른쪽 노드랑 매칭이 될 경우,
            //그것도 처리
            right_assign[right_node] = left_node;
            return true;
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int n, m, cnt, tmp;
    cin >> n >> m;
    f(i, 1, n+1) {
        cin >> cnt;
        f(k, 0, cnt) {
            cin >> tmp;
            adj[i].push_back(tmp);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        memset(v, 0, sizeof(v));
        if (dfs(i)) ++ans;
    }
    cout << ans;
    return 0;
}