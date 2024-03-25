#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, k;
vector<int> adj[501];
bool v[501];
int assign[501];

bool dfs(int x) {
    for (int &nxt : adj[x]) {
        if (v[nxt]) continue;
        v[nxt] = true;

        if ( !assign[nxt] || dfs(assign[nxt]) ) {
            assign[nxt] = x;
            return true;
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;

    for (int i = 0; i < k; ++i) {
        // 행 열 입력
        int r, c; cin >> r >> c;

        // 어떤 행을 선택할 때 영향 미치는 열 연결하기
        adj[r].push_back(c);
    }

    // 이분 매칭 , 이 결과 == Mininum Vertex Cover
    int ans = 0;
    for (int i= 1;i <=n; ++i) {
        memset(v, 0, sizeof(v));
        ans += dfs(i);
    }

    cout << ans;
    return 0;
}