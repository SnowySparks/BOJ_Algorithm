#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7f7f7f7f;
int n;
string inp[1000];
int dp[1000][1000];

int mv[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    queue<pair<int, int> > q;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> inp[i];
            fill(dp[i], dp[i]+n, inf);
        }

        dp[0][0] = 0;
        q.push({0, 0});

        while (!q.empty())
        {
            int r = q.front().first, c = q.front().second; q.pop();

            for (auto &[dr, dc] : mv) {
                int nr = r + dr , nc = c + dc;
                if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
                if (dp[nr][nc] > dp[r][c] + (inp[nr][nc] - '0')) {
                    dp[nr][nc] = dp[r][c] + (inp[nr][nc] - '0');
                    q.push({nr, nc});
                }
            }
        }
        cout << '#' << tc <<' ' << dp[n-1][n-1] <<'\n';
    }
    return 0;
}