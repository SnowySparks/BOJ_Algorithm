#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define f(a, b, c) for(int a = b; a < c; ++a)

int n; // size 
int arr[100][100]; // 0 : empty , 1 : blocked

// 이분매칭 전용 --
vector<int> adj[10000];

int assign[10000];
bool v[10000];

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
// ---
// 탐색 전용

int mv[2][2] = {{1, 1}, {1, -1}};
int diag_assign[2][100][100]; //diag_assign : 대각선 방향에 때라 배정되는 값

int left_up_cnt = 0;
int right_up_cnt = 0;



int main(void) {
    // setting
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    memset(diag_assign, -1, sizeof(diag_assign));
    memset(assign, -1, sizeof(assign));

    // input
    cin >> n;
    int r, c;
    int m; cin >> m;
    while (m--)
    {
        cin >> r >> c;
        --r; --c;
        arr[r][c] = 1;
    }

    // 방향 부여 탐색 - 우하향 방향
    f(i, 0, n) f(j, 0, n) {
        if (arr[i][j]) continue;
        if (diag_assign[0][i][j] == -1) {
            diag_assign[0][i][j] = left_up_cnt;

            int r = i, c = j;
            while (1)
            {
                r++; c++;
                if (r < 0 || r >= n || c < 0 || c >= n || arr[r][c] || diag_assign[0][r][c] >= 0) break;
                diag_assign[0][r][c] = left_up_cnt;
            }
            left_up_cnt++;
        }
    }

    // 방향 부여 탐색 - 우상향
    for (int i = 0; i < n; ++i) {
        for (int j = n-1; j >= 0; --j) {
            if (arr[i][j]) continue;

            if (diag_assign[1][i][j] == -1) {
                diag_assign[1][i][j] = right_up_cnt;

                int r = i, c = j;
                while (1)
                {
                    r++; c--;
                    if (r < 0 || r >= n || c < 0 || c >= n || arr[r][c] || diag_assign[1][r][c] >= 0) break;
                    diag_assign[1][r][c] = right_up_cnt;
                }
                right_up_cnt++;
            }
        }
    }

    // 대각선 번호 부여 확인용
    // f(i, 0, n) {
    //     f(j, 0, n) {
    //         cout << diag_assign[0][i][j] <<'/' << diag_assign[1][i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    f(i, 0, n) {
        f(j, 0, n) {
            if (arr[i][j]) continue;
            adj[ diag_assign[0][i][j]].push_back(diag_assign[1][i][j]);
        }
    }

    // 이분매칭
    int ans = 0;
    f(i, 0, left_up_cnt) {
        memset(v, 0, sizeof(v));
        if (dfs(i)) ans++;
    }
    cout << ans;
    return 0;
}