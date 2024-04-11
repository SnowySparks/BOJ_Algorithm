#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define f(a, b, c) for(int a = b; a < c; ++a)

int n;
int arr[10][10];

vector<int> adj[100];

int assign[100];
bool v[100];

bool dfs(int x) {
    for (int &nxt : adj[x]) {
        if (v[nxt]) continue;
        v[nxt] = true;
        if (assign[nxt] == -1 || dfs(assign[nxt]) ) {
            assign[nxt] = x;
            return true;
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // input
    cin >> n;
    f(i, 0, n) f(j, 0, n) cin >> arr[i][j];
    

    // 관계 그래프 연결 (우상향, 우하향 방향간)
    // (우상향 방향) -> (우하향 방향) 관계로 그리기

    f(i, 0, n) f(j, 0, n) {
        if (!arr[i][j]) continue;
        adj[i+j].push_back((n-1) - (i-j));
    }

    int max_bimatching = 0;
    memset(assign, -1, sizeof(assign));

    f(i, 0, 2*n-1) {
        memset(v, 0, sizeof(v));
        if (dfs(i)) max_bimatching++;
    }

// 최대 매칭이 답이 됨
    cout << max_bimatching;
    return 0;
}