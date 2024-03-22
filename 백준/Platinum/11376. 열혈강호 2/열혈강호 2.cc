#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#define f(a, b, c) for(int a= b; a<c;++a)
using namespace std;
const int mv = 2e3+3;
vector<int> adj[mv];
int right_assign[mv]; 
bool v[mv]; // 

bool dfs(int left_node) {
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
            adj[2*i-1].push_back(tmp);
            adj[2*i].push_back(tmp);
        }
    }

    int ans = 0;
    
    for (int i = 1; i <= 2*n; ++i) {
        memset(v, 0, sizeof(v));
        if(dfs(i)) ++ans;
    }
    cout << ans;
    return 0;
}

// 단순하게 왼쪽 노드를 2배로 늘리고, (2*i, 2*i +1) 노드들은 전부 i 노드라고 생각하고
// 해당 노드들와 연결되는 오른쪽노드 상태는 같음