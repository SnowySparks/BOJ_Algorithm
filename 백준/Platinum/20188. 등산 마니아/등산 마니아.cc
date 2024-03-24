//원리 : 7812와 거의 유사한 원리. 간선을 기준으로 부모쪽, 자식쪽 그룹, 그리고 자식들끼리 선택 그 2가지만 보기
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using ll = long long;
const int inf = 3e5+1;

int n;
vector<int> tree[inf];
int sub_node[inf];

void dfs(int node, int pnode) {
    sub_node[node] = 1;
    for (int &nxt : tree[node]) {
        if (nxt == pnode) continue;
        dfs(nxt, node);
        sub_node[node] += sub_node[nxt];
    }
}

ll ans = 0;

void solve(int node, int pnode) {
    ll stcnt = sub_node[node]; //node 기준 sub_tree의 개수. (root : 1기준)
    ans += (stcnt)*(n - stcnt) + (stcnt)*(stcnt-1)/2;
    for (int &nxt : tree[node]) {
        if (nxt == pnode) continue;
        solve(nxt, node);
    }
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0; i < n-1; ++i) {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, -1);
    for (int &nxt: tree[1]) {
        solve(nxt, 1);
    }
    cout << ans;

    return 0;
}