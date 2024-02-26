#include <iostream>
#include <cstring>
#define f(a, b, c) for (int a=b;a<c;++a)
using namespace std;
int n;
pair<int, int> mv[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int dp[1000][1000];
int arr[1000][1000];

int dfs(int r, int c) {
    int &res = dp[r][c];
    if (res != -1) return res;
    res = 1;
    for (auto &[dr, dc] : mv) {
        int nr = r + dr, nc = c + dc;
        if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
        if (arr[nr][nc] == arr[r][c] + 1) res = max(res, dfs(nr, nc) + 1);
    }
    return res;
}
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> n;
        f(i, 0, n) f(j, 0, n) cin >> arr[i][j];
        memset(dp, -1, sizeof(dp));
        int ans = -1, ans_room  = -1;
        f(r, 0, n) {
            f(c, 0, n) {
                if (dp[r][c] == -1) {
                    int res = dfs(r, c);
                    if (res > ans) {
                        ans = res;
                        ans_room = arr[r][c];
                    }
                    else if (res == ans) {
                        ans_room = min(ans_room, arr[r][c]);
                    }
                }
            }
        }
        cout << '#' << tc << ' ' << ans_room <<' ' << ans <<'\n';
    }
    return 0;
}